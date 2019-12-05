#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day4.cpp"

TEST_CASE("We should be able to query the digits of a number") {
    auto digits = get_digits_of_number(12345);
    REQUIRE(digits[0] == 1);
    REQUIRE(digits[1] == 2);
    REQUIRE(digits[2] == 3);
    REQUIRE(digits[3] == 4);
    REQUIRE(digits[4] == 5);

    digits = get_digits_of_number(2468013579);
    REQUIRE(digits[0] == 2);
    REQUIRE(digits[1] == 4);
    REQUIRE(digits[2] == 6);
    REQUIRE(digits[3] == 8);
    REQUIRE(digits[4] == 0);
    REQUIRE(digits[5] == 1);
    REQUIRE(digits[6] == 3);
    REQUIRE(digits[7] == 5);
    REQUIRE(digits[8] == 7);
    REQUIRE(digits[9] == 9);
}
