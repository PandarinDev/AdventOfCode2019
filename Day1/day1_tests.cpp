#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day1.cpp"

TEST_CASE("Required fuel for mass calculation should be correct") {
    REQUIRE(calculate_required_fuel_for_mass(12) == 2);
    REQUIRE(calculate_required_fuel_for_mass(14) == 2);
    REQUIRE(calculate_required_fuel_for_mass(1969) == 654);
    REQUIRE(calculate_required_fuel_for_mass(100756) == 33583);
}