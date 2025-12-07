// Просто подключаем заголовок - CMake уже позаботился о путях
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <string>

TEST_CASE("Basic Catch2 test", "[catch2]") {
    REQUIRE(1 + 1 == 2);
    REQUIRE_FALSE(1 + 1 == 3);
}

TEST_CASE("Vector test", "[catch2]") {
    std::vector<int> v{1, 2, 3};
    
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("String test", "[catch2]") {
    std::string s = "test";
    
    REQUIRE(s.length() == 4);
    REQUIRE(s == "test");
}