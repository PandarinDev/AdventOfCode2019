#include <cmath>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <functional>
#include <unordered_set>

enum class Direction {
    UP = 'U',
    RIGHT = 'R',
    DOWN = 'D',
    LEFT = 'L'
};

struct Coordinate {
    
    std::int64_t x;
    std::int64_t y;
    
    Coordinate(std::int64_t x, std::int64_t y) : x(x), y(y) {}

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }

};

struct Movement {

    static Movement from_string(const std::string& str) {
        if (str.size() < 2) {
            throw std::runtime_error("Supplied movement string is invalid.");
        }
        Direction direction = static_cast<Direction>(str[0]);
        std::size_t steps = std::stoull(str.substr(1));
        return Movement(direction, steps);
    }

    Direction direction;
    std::size_t steps;

    Movement(Direction direction, std::size_t steps) :
        direction(direction), steps(steps) {}

    bool operator==(const Movement& other) const {
        return direction == other.direction && steps == other.steps;
    }

    std::vector<Coordinate> move(Coordinate current) const {
        std::function<Coordinate(const Coordinate&)> stepping_function;
        switch (direction) {
        case Direction::UP: stepping_function = [](const auto& current) { return Coordinate(current.x, current.y + 1); };
        case Direction::RIGHT: stepping_function = [](const auto& current) { return Coordinate(current.x + 1, current.y); };
        case Direction::DOWN: stepping_function = [](const auto& current) { return Coordinate(current.x, current.y - 1); };
        case Direction::LEFT: stepping_function = [](const auto& current) { return Coordinate(current.x - 1, current.y); };
        default: throw std::runtime_error("Unhandled direction value.");
        }

        std::vector<Coordinate> coordinates;
        for (std::size_t i = 0; i < steps; ++i) {
            current = stepping_function(current);
            coordinates.emplace_back(current);
        }
        return coordinates;
    }

};

namespace std {

    template<>
    struct hash<Coordinate> {

        // This is a simple hash-combine for the two integer values present in coordinate.
        // The exact implementation was taken over from Boost's hash_combine.
        std::size_t operator()(const Coordinate& coordinate) const {
            auto seed = hash<std::int64_t>{}(coordinate.x);
            return hash<std::int64_t>{}(coordinate.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

    };

}

std::size_t manhattan_distance(const Coordinate& c0, const Coordinate& c1) {
    return std::abs(c0.x - c1.x) + std::abs(c0.y - c1.y);
}

struct Grid {

    std::unordered_set<Coordinate> wire1_path;
    std::unordered_set<Coordinate> wire2_path;

    template<typename T>
    Grid(T&& wire1_path, T&& wire2_path) :
        wire1_path(std::forward<T>(wire1_path)),
        wire2_path(std::forward<T>(wire2_path)) {}

    bool is_wire1_on(const Coordinate& coord) const {
        return wire1_path.find(coord) != wire1_path.end();
    }

    bool is_wire2_on(const Coordinate& coord) const {
        return wire2_path.find(coord) != wire2_path.end();
    }

    std::unordered_set<Coordinate> get_all_intersections() const {
        std::unordered_set<Coordinate> intersections;
        for (const auto& coord : wire1_path) {
            if (is_wire2_on(coord)) {
                intersections.emplace(coord);
            }
        }

        return intersections;
    }

    static Grid from_movements(
        const std::vector<Movement>& wire1_movements,
        const std::vector<Movement>& wire2_movements) {
        static const Coordinate origin(0, 0);
        
        Coordinate current_coords = origin;
        std::unordered_set<Coordinate> wire1_path;
        std::unordered_set<Coordinate> wire2_path;
        
        // Walk the path of wire#1
        for (const auto& movement : wire1_movements) {
            auto coordinates = movement.move(current_coords);
            for (const auto& coordinate : coordinates) {
                wire1_path.emplace(coordinate);
            }
            current_coords = coordinates.at(coordinates.size() - 1);
        }

        // Walk the path of wire#2
        current_coords = origin;
        for (const auto& movement : wire2_movements) {
            auto coordinates = movement.move(current_coords);
            for (const auto& coordinate : coordinates) {
                wire2_path.emplace(coordinate);
            }
            current_coords = coordinates.at(coordinates.size() - 1);
        }

        return Grid(std::move(wire1_path), std::move(wire2_path));
    }

};