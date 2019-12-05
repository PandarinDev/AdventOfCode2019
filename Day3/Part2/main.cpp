#include "../day3.cpp"

#include <fstream>
#include <filesystem>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>

std::vector<Movement> wire_movements_from_string(const std::string& str) {
    std::stringstream input_stream(str);
    std::string entry;
    std::vector<Movement> movements;
    while (std::getline(input_stream, entry, ',')) {
        movements.emplace_back(Movement::from_string(entry));
    }

    return movements;
}

int main(int argc, char** argv) {
    auto exe_path = std::filesystem::weakly_canonical(argv[0]);
    auto input_path = exe_path.parent_path().append("input.txt");
    auto file_handle = std::ifstream(input_path.c_str());
    if (!file_handle) {
        std::cerr << "Couldn't open 'input.txt' for inputs." << std::endl;
        return 1;
    }

    std::string wire1_movements_str;
    std::string wire2_movements_str;
    if (!std::getline(file_handle, wire1_movements_str) ||
        !std::getline(file_handle, wire2_movements_str)) {
        std::cerr << "Failed to read input." << std::endl;
        return 1;
    }
    
    auto wire1_movements = wire_movements_from_string(wire1_movements_str);
    auto wire2_movements = wire_movements_from_string(wire2_movements_str);
    auto grid = Grid::from_movements(wire1_movements, wire2_movements);
    auto intersections = grid.get_intersections();
    if (intersections.empty()) {
        std::cerr << "No intersections found." << std::endl;
        return 1;
    }

    Coordinate origin(0, 0);
    std::size_t min_steps_to_intersection = std::numeric_limits<std::size_t>::max();
    for (const auto& intersection : intersections) {
        auto wire1_steps = grid.wire1_steps_to.at(intersection);
        auto wire2_steps = grid.wire2_steps_to.at(intersection);
        auto total_steps = wire1_steps + wire2_steps;
        if (total_steps < min_steps_to_intersection) {
            min_steps_to_intersection = total_steps;
        }
    }

    std::cout << min_steps_to_intersection << std::endl;
    return 0;
}