#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "day3.cpp"

TEST_CASE("Manhattan distance should be correct") {
    REQUIRE(manhattan_distance(Coordinate(0, 0), Coordinate(3, 3)) == 6);
    REQUIRE(manhattan_distance(Coordinate(6, 4), Coordinate(2, 5)) == 5);
}

TEST_CASE("Movement from string should return the expeced values") {
    REQUIRE(Movement::from_string("U1") == Movement(Direction::UP, 1));
    REQUIRE(Movement::from_string("R8") == Movement(Direction::RIGHT, 8));
    REQUIRE(Movement::from_string("D2") == Movement(Direction::DOWN, 2));
    REQUIRE(Movement::from_string("L42") == Movement(Direction::LEFT, 42));
}

TEST_CASE("Movements should move correctly") {
    Coordinate origin(0, 0);
    REQUIRE(Movement(Direction::UP, 3).move(origin) == Coordinate(0, 3));
    REQUIRE(Movement(Direction::RIGHT, 2).move(origin) == Coordinate(2, 0));
    REQUIRE(Movement(Direction::DOWN, 5).move(origin) == Coordinate(0, -5));
    REQUIRE(Movement(Direction::LEFT, 7).move(origin) == Coordinate(-7, 0));
}

TEST_CASE("Grid from movements should be correct") {
    std::vector<Movement> wire1_movements = {
        Movement::from_string("R1"),
        Movement::from_string("U2"),
        Movement::from_string("L3")
    };
    std::vector<Movement> wire2_movements = {
        Movement::from_string("L3"),
        Movement::from_string("D2"),
        Movement::from_string("U1")
    };
    Grid grid = Grid::from_movements(wire1_movements, wire2_movements);

    // Test for wire1
    REQUIRE(grid.is_wire1_on(Coordinate(1, 0))); // Right 1
    REQUIRE(grid.is_wire1_on(Coordinate(1, 1))); // Up 2
    REQUIRE(grid.is_wire1_on(Coordinate(1, 2)));
    REQUIRE(grid.is_wire1_on(Coordinate(0, 2))); // Left 3
    REQUIRE(grid.is_wire1_on(Coordinate(-1, 2)));
    REQUIRE(grid.is_wire1_on(Coordinate(-2, 2)));

    // Test for wire2
    REQUIRE(grid.is_wire2_on(Coordinate(-1, 0)));  // Left 3
    REQUIRE(grid.is_wire2_on(Coordinate(-2, 0)));
    REQUIRE(grid.is_wire2_on(Coordinate(-3, 0)));
    REQUIRE(grid.is_wire2_on(Coordinate(-3, -1))); // Down 2
    REQUIRE(grid.is_wire2_on(Coordinate(-3, -2)));
    REQUIRE(grid.is_wire2_on(Coordinate(-3, -1))); // Up 1
}