cmake_minimum_required(VERSION 3.16)
project(CrossPlatformTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Boost
find_package(Boost 1.71 QUIET)
if(Boost_FOUND)
    message(STATUS "Boost found via find_package: ${Boost_VERSION}")
    set(HAVE_BOOST TRUE)
    set(BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
else()
    message(STATUS "Boost not found via find_package, trying fallback...")
    # Проверяем наличие заголовков Boost в стандартных путях
    find_path(BOOST_INCLUDE_DIR boost/version.hpp
        PATHS
        /usr/local/include
        /opt/homebrew/include
        /usr/include
        $ENV{HOME}/.local/include
    )
    
    if(BOOST_INCLUDE_DIR)
        set(HAVE_BOOST TRUE)
        set(BOOST_INCLUDE_DIRS ${BOOST_INCLUDE_DIR})
        message(STATUS "Boost headers found at: ${BOOST_INCLUDE_DIR}")
    else()
        message(WARNING "Boost headers not found")
        set(HAVE_BOOST FALSE)
    endif()
endif()

# Ищем GTest
find_package(GTest QUIET)
if(GTest_FOUND)
    message(STATUS "GoogleTest found via find_package")
    set(HAVE_GTEST TRUE)
else()
    message(STATUS "GoogleTest not found via find_package, trying fallback...")
    # Проверяем наличие GTest в стандартных путях
    find_path(GTEST_INCLUDE_DIR gtest/gtest.h
        PATHS
        /usr/local/include
        /opt/homebrew/include
        /usr/include
        $ENV{HOME}/.local/include
    )
    
    if(GTEST_INCLUDE_DIR)
        set(HAVE_GTEST TRUE)
        set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIR})
        message(STATUS "GoogleTest headers found at: ${GTEST_INCLUDE_DIR}")
    else()
        message(WARNING "GoogleTest headers not found")
        set(HAVE_GTEST FALSE)
    endif()
endif()

# Ищем Catch2
find_package(Catch2 QUIET)
if(Catch2_FOUND)
    message(STATUS "Catch2 found via find_package")
    set(HAVE_CATCH2 TRUE)
else()
    message(STATUS "Catch2 not found via find_package, trying fallback...")
    # Проверяем наличие Catch2 в стандартных путях
    find_path(CATCH2_INCLUDE_DIR catch2/catch_test_macros.hpp
        PATHS
        /usr/local/include
        /opt/homebrew/include
        /usr/include
        $ENV{HOME}/.local/include
    )
    
    if(CATCH2_INCLUDE_DIR)
        set(HAVE_CATCH2 TRUE)
        set(CATCH2_INCLUDE_DIRS ${CATCH2_INCLUDE_DIR})
        message(STATUS "Catch2 headers found at: ${CATCH2_INCLUDE_DIR}")
    else()
        message(WARNING "Catch2 headers not found")
        set(HAVE_CATCH2 FALSE)
    endif()
endif()

# Основная программа
add_executable(main_app src/main.cpp)

# Добавляем определения препроцессора и include директории
if(HAVE_BOOST)
    target_compile_definitions(main_app PRIVATE HAS_BOOST)
    target_include_directories(main_app PRIVATE ${BOOST_INCLUDE_DIRS})
    message(STATUS "Boost will be used in main_app")
endif()

# Включаем тестирование если есть хотя бы один фреймворк тестирования
if(HAVE_GTEST OR HAVE_CATCH2)
    enable_testing()
endif()

# Тесты GoogleTest
if(HAVE_GTEST)
    add_executable(gtest_test tests/gtest_test.cpp)
    
    # Для GoogleTest, найденного через find_package
    if(GTest_FOUND)
        target_link_libraries(gtest_test GTest::gtest GTest::gtest_main)
        message(STATUS "Using GTest imported targets")
    else()
        # Добавляем include директории для ручного поиска
        target_include_directories(gtest_test PRIVATE ${GTEST_INCLUDE_DIRS})
        
        # Ищем библиотеки
        find_library(GTEST_LIB 
            NAMES gtest libgtest
            PATHS
            /usr/local/lib
            /opt/homebrew/lib
            /usr/lib
            /usr/lib/x86_64-linux-gnu
        )
        
        find_library(GTEST_MAIN_LIB 
            NAMES gtest_main libgtest_main
            PATHS
            /usr/local/lib
            /opt/homebrew/lib
            /usr/lib
            /usr/lib/x86_64-linux-gnu
        )
        
        if(GTEST_LIB AND GTEST_MAIN_LIB)
            target_link_libraries(gtest_test ${GTEST_LIB} ${GTEST_MAIN_LIB})
            message(STATUS "Linked gtest_test with: ${GTEST_LIB} ${GTEST_MAIN_LIB}")
        elseif(GTEST_LIB)
            target_link_libraries(gtest_test ${GTEST_LIB})
            message(STATUS "Linked gtest_test with: ${GTEST_LIB} only")
        else()
            message(STATUS "No GoogleTest libraries found, using headers only")
        endif()
    endif()
    
    add_test(NAME GoogleTest COMMAND gtest_test)
    message(STATUS "GoogleTest executable will be built")
endif()

# Тесты Catch2
if(HAVE_CATCH2)
    add_executable(catch2_test tests/catch2_test.cpp)
    
    # Для Catch2, найденного через find_package
    if(Catch2_FOUND)
        target_link_libraries(catch2_test Catch2::Catch2WithMain)
        message(STATUS "Using Catch2 imported targets")
    else()
        # Добавляем include директории для ручного поиска
        target_include_directories(catch2_test PRIVATE ${CATCH2_INCLUDE_DIRS})
        message(STATUS "Using Catch2 headers only")
    endif()
    
    add_test(NAME Catch2 COMMAND catch2_test)
    message(STATUS "Catch2 executable will be built")
endif()

# Устанавливаем свойства CTest только если тесты существуют
if(TARGET gtest_test)
    set_property(TEST GoogleTest PROPERTY TIMEOUT 10)
endif()

if(TARGET catch2_test)
    set_property(TEST Catch2 PROPERTY TIMEOUT 10)
endif()

# Выводим итоговую информацию
message(STATUS "")
message(STATUS "=== Summary ===")
message(STATUS "Boost: ${HAVE_BOOST}")
message(STATUS "GoogleTest: ${HAVE_GTEST}")
message(STATUS "Catch2: ${HAVE_CATCH2}")
message(STATUS "===============")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)