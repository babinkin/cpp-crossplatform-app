cmake_minimum_required(VERSION 3.14)
project(BoostTestProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Boost (только заголовочные файлы)
find_package(Boost 1.70.0 QUIET)
find_package(GTest REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
else()
    # Альтернативный способ поиска Boost на Mac с Homebrew
    execute_process(
        COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/find_boost_mac.sh
        OUTPUT_VARIABLE BOOST_INCLUDE_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(BOOST_INCLUDE_PATH)
        message(STATUS "Boost found via script: ${BOOST_INCLUDE_PATH}")
        set(Boost_INCLUDE_DIRS ${BOOST_INCLUDE_PATH})
        set(Boost_FOUND TRUE)
    else()
        # Стандартные пути поиска
        set(POSSIBLE_BOOST_PATHS
            "/usr/local/include"
            "/opt/local/include" 
            "/usr/include"
        )
        
        find_path(Boost_INCLUDE_DIRS 
            NAMES boost/version.hpp
            PATHS ${POSSIBLE_BOOST_PATHS}
        )
        
        if(Boost_INCLUDE_DIRS)
            message(STATUS "Boost found in standard path: ${Boost_INCLUDE_DIRS}")
            set(Boost_FOUND TRUE)
        else()
            message(FATAL_ERROR "Boost not found! Please install Boost.")
        endif()
    endif()
endif()

# Создаем исполняемый файл
add_executable(boost_test src/main.cpp)

# Добавляем include директории Boost
target_include_directories(boost_test PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(boost_test GTest::gtest GTest::gtest_main)
target_link_libraries(boost_test pthread)

# Для отладки - выводим информацию о компиляции
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")