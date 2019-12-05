#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day4_part1.cpp"

TEST_CASE("Check if a number matches the criteria for task part#1") {
    REQUIRE(number_matches_criteria(111111));
    REQUIRE(!number_matches_criteria(223450));
    REQUIRE(!number_matches_criteria(123789));
}