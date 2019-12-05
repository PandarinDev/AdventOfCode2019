#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day4_part2.cpp"

TEST_CASE("Check if a number matches the criteria for task part#2") {
    REQUIRE(number_matches_criteria(112233));
    REQUIRE(!number_matches_criteria(123444));
    REQUIRE(number_matches_criteria(111122));
}