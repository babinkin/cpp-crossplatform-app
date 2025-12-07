#include <iostream>
#include <vector>
#include <string>

// Проверка Boost
#ifdef HAS_BOOST
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>
#endif

int main() {
    std::cout << "Cross-platform test application\n";
    std::cout << "===============================\n\n";
    
    // Проверка компилятора
    #ifdef __clang__
    std::cout << "Compiler: Clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << "\n";
    #elif defined(__GNUC__)
    std::cout << "Compiler: GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
    #else
    std::cout << "Compiler: Unknown\n";
    #endif
    
    std::cout << "C++ standard: " << __cplusplus << "\n\n";
    
    // Проверка Boost
    #ifdef HAS_BOOST
    std::cout << "Boost version: " 
              << BOOST_VERSION / 100000 << "."  // major
              << BOOST_VERSION / 100 % 1000 << "."  // minor
              << BOOST_VERSION % 100 << "\n";  // patch
    
    // Простой пример использования Boost
    std::string text = "Hello Boost World";
    std::cout << "Original: " << text << "\n";
    boost::algorithm::to_upper(text);
    std::cout << "Upper case (Boost): " << text << "\n\n";
    #else
    std::cout << "Boost not available or not included\n\n";
    #endif
    
    // Простой пример без Boost для демонстрации
    std::cout << "Simple C++17 example:\n";
    std::vector<int> numbers{1, 2, 3, 4, 5};
    int sum = 0;
    for (auto n : numbers) {
        sum += n;
    }
    std::cout << "Sum of numbers: " << sum << "\n\n";
    
    std::cout << "Application finished successfully!\n";
    return 0;
}