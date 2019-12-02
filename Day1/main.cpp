#include "day1.cpp"

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    auto exe_path = std::filesystem::weakly_canonical(argv[0]);
    auto input_path = exe_path.parent_path().append("input.txt");
    auto file_handle = std::ifstream(input_path.c_str());
    if (!file_handle) {
        std::cerr << "Couldn't open 'input.txt' for inputs." << std::endl;
        return 1;
    }

    std::string line;
    std::size_t total_required_fuel = 0;
    while (std::getline(file_handle, line)) {
        if (line.empty()) {
            continue;
        }
        std::size_t mass = std::stoull(line);
        total_required_fuel += calculate_required_fuel_for_mass(mass);
    }

    std::cout << total_required_fuel << std::endl;
    return 0;
}