#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day2.cpp"

TEST_CASE("Executor should be able to run add operations") {
    std::vector<std::size_t> values = { 1, 0, 0, 0, 99 };
    Executor executor(std::move(values));
    executor.run_program();
    
    REQUIRE(executor.values[0] == 2);
}

TEST_CASE("Executor should be able to run multiply operations (first)") {
    std::vector<std::size_t> values = { 2, 3, 0, 3, 99 };
    Executor executor(std::move(values));
    executor.run_program();

    REQUIRE(executor.values[3] == 6);
}

TEST_CASE("Executor should be able to run multiply operations (second)") {
    std::vector<std::size_t> values = { 2, 4, 4, 5, 99, 0 };
    Executor executor(std::move(values));
    executor.run_program();

    REQUIRE(executor.values[5] == 9801);
}

TEST_CASE("Executor should be able to run complex operations") {
    std::vector<std::size_t> values = { 1,1,1,4,99,5,6,0,99 };
    Executor executor(std::move(values));
    executor.run_program();

    REQUIRE(executor.values[0] == 30);
    REQUIRE(executor.values[4] == 2);
}