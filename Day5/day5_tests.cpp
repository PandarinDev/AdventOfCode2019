#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day5.cpp"

TEST_CASE("String left pad should work correctly") {
    REQUIRE(string_left_pad("foo", 5, 'x') == "xxfoo");
    REQUIRE(string_left_pad("bar", 1, 'y') == "bar");
}

TEST_CASE("String splitting should work correctly") {
    auto entries = split("foo,bar,baz", ',');
    REQUIRE(entries.size() == 3);
    REQUIRE(entries[0] == "foo");
    REQUIRE(entries[1] == "bar");
    REQUIRE(entries[2] == "baz");
}

TEST_CASE("Operation parsing in executor should be correct") {
    auto input_supplier = []() { return 1; };
    auto output_consumer = [](const auto& o0, const auto& o1) {};
    std::vector<std::size_t> values {
        // ADD: Add position 4 to value 6 and store at position 2
        1001, 4, 6, 2,
        // MULTIPLY: Multiply value 2 with value 4 and store at position 0
        1102, 2, 4, 0,
        // SAVE_INPUT: Save the next input value to position 1
        3, 1,
        // OUTPUT_VALUE: Output the value at position 5
        4, 5,
        // HALT
        99
    };
    Executor executor(std::move(values), input_supplier, output_consumer);
    
    auto operation = executor.get_next_operation();
    REQUIRE(operation.has_value());
    REQUIRE(operation->opcode == Opcode::ADD);
    REQUIRE(operation->parameters.size() == 3);
    REQUIRE(operation->parameters[0].value == 4);
    REQUIRE(operation->parameters[0].mode == ParameterMode::POSITION_MODE);
    REQUIRE(operation->parameters[1].value == 6);
    REQUIRE(operation->parameters[1].mode == ParameterMode::IMMEDIATE_MODE);
    REQUIRE(operation->parameters[2].value == 2);
    REQUIRE(operation->parameters[2].mode == ParameterMode::POSITION_MODE);

    operation = executor.get_next_operation();
    REQUIRE(operation.has_value());
    REQUIRE(operation->opcode == Opcode::MULTIPLY);
    REQUIRE(operation->parameters.size() == 3);
    REQUIRE(operation->parameters[0].value == 2);
    REQUIRE(operation->parameters[0].mode == ParameterMode::IMMEDIATE_MODE);
    REQUIRE(operation->parameters[1].value == 4);
    REQUIRE(operation->parameters[1].mode == ParameterMode::IMMEDIATE_MODE);
    REQUIRE(operation->parameters[2].value == 0);
    REQUIRE(operation->parameters[2].mode == ParameterMode::POSITION_MODE);

    operation = executor.get_next_operation();
    REQUIRE(operation.has_value());
    REQUIRE(operation->opcode == Opcode::SAVE_INPUT);
    REQUIRE(operation->parameters.size() == 1);
    REQUIRE(operation->parameters[0].value == 1);
    REQUIRE(operation->parameters[0].mode == ParameterMode::POSITION_MODE);

    operation = executor.get_next_operation();
    REQUIRE(operation.has_value());
    REQUIRE(operation->opcode == Opcode::OUTPUT_VALUE);
    REQUIRE(operation->parameters.size() == 1);
    REQUIRE(operation->parameters[0].value == 5);
    REQUIRE(operation->parameters[0].mode == ParameterMode::POSITION_MODE);

    operation = executor.get_next_operation();
    REQUIRE(operation.has_value());
    REQUIRE(operation->opcode == Opcode::HALT);
    REQUIRE(operation->parameters.empty());
}