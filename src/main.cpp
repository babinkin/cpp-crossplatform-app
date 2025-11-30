#include <iostream>
#include <vector>
#include <string>

// Header-only компоненты Boost
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/optional.hpp>
#include <boost/any.hpp>

int main() {
    std::cout << "=== Boost Test Project ===" << std::endl;
    
    // 1. Проверка версии Boost
    std::cout << "Boost version: " 
              << BOOST_VERSION / 100000     << "."  // major version
              << BOOST_VERSION / 100 % 1000 << "."  // minor version
              << BOOST_VERSION % 100                // patch level
              << std::endl;
    
    // 2. Тест boost::algorithm
    std::string test_string = "Hello Boost World";
    std::cout << "Original string: " << test_string << std::endl;
    
    boost::to_upper(test_string);
    std::cout << "Uppercase: " << test_string << std::endl;
    
    boost::to_lower(test_string);
    std::cout << "Lowercase: " << test_string << std::endl;
    
    // 3. Тест boost::lexical_cast
    try {
        std::string number_str = "12345";
        int number = boost::lexical_cast<int>(number_str);
        std::cout << "String '" << number_str << "' converted to int: " << number << std::endl;
        
        std::string back_to_str = boost::lexical_cast<std::string>(number);
        std::cout << "Int " << number << " converted back to string: '" << back_to_str << "'" << std::endl;
    } catch (const boost::bad_lexical_cast& e) {
        std::cout << "Lexical cast error: " << e.what() << std::endl;
    }
    
    // 4. Тест boost::format
    boost::format fmt("Format test: %1% + %2% = %3%");
    fmt % 5 % 3 % (5+3);
    std::cout << fmt.str() << std::endl;
    
    // 5. Тест boost::optional
    boost::optional<int> maybe_number;
    std::cout << "Optional is initialized: " << (maybe_number ? "true" : "false") << std::endl;
    
    maybe_number = 42;
    std::cout << "Optional value: " << *maybe_number << std::endl;
    
    // 6. Тест boost::any
    boost::any anything = 3.14159;
    std::cout << "Any contains double: " << boost::any_cast<double>(anything) << std::endl;
    
    anything = std::string("Boost any works!");
    std::cout << "Any contains string: " << boost::any_cast<std::string>(anything) << std::endl;
    
    std::cout << "=== All tests completed successfully! ===" << std::endl;
    return 0;
}