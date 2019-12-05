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
    auto coordinates_up = Movement(Direction::UP, 3).move(origin);
    REQUIRE(coordinates_up[0] == Coordinate(0, 1));
    REQUIRE(coordinates_up[1] == Coordinate(0, 2));
    REQUIRE(coordinates_up[2] == Coordinate(0, 3));
    
    auto coordinates_right = Movement(Direction::RIGHT, 2).move(origin);
    REQUIRE(coordinates_right[0] == Coordinate(1, 0));
    REQUIRE(coordinates_right[1] == Coordinate(2, 0));
    
    auto coordinates_down = Movement(Direction::DOWN, 5).move(origin);
    REQUIRE(coordinates_down[0] == Coordinate(0, -1));
    REQUIRE(coordinates_down[1] == Coordinate(0, -2));
    REQUIRE(coordinates_down[2] == Coordinate(0, -3));
    REQUIRE(coordinates_down[3] == Coordinate(0, -4));
    REQUIRE(coordinates_down[4] == Coordinate(0, -5));
    
    auto coordinates_left = Movement(Direction::LEFT, 7).move(origin);
    REQUIRE(coordinates_left[0] == Coordinate(-1, 0));
    REQUIRE(coordinates_left[1] == Coordinate(-2, 0));
    REQUIRE(coordinates_left[2] == Coordinate(-3, 0));
    REQUIRE(coordinates_left[3] == Coordinate(-4, 0));
    REQUIRE(coordinates_left[4] == Coordinate(-5, 0));
    REQUIRE(coordinates_left[5] == Coordinate(-6, 0));
    REQUIRE(coordinates_left[6] == Coordinate(-7, 0));
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

TEST_CASE("Intersection calculations should be correct") {
    std::vector<Movement> wire1_movements = {
        Movement::from_string("R8"),
        Movement::from_string("U5"),
        Movement::from_string("L5"),
        Movement::from_string("D3")
    };
    std::vector<Movement> wire2_movements = {
        Movement::from_string("U7"),
        Movement::from_string("R6"),
        Movement::from_string("D4"),
        Movement::from_string("L4")
    };

    auto grid = Grid::from_movements(wire1_movements, wire2_movements);
    auto intersections = grid.get_intersections();
    REQUIRE(intersections.size() == 2);
    REQUIRE(intersections.find(Coordinate(3, 3)) != intersections.end());
    REQUIRE(intersections.find(Coordinate(6, 5)) != intersections.end());
}