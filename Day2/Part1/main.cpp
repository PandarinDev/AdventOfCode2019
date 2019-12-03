#include "../day2.cpp"

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

    // Read the entire input into memory
    std::string line;
    if (!std::getline(file_handle, line)) {
        std::cerr << "Failed to read input file." << std::endl;
        return 1;
    }

    // Parse the input
    auto values_str = split(line, ',');
    std::vector<std::size_t> values(values_str.size());
    for (std::size_t i = 0; i < values_str.size(); ++i) {
        values[i] = std::stoull(values_str[i]);
    }

    // Execute the input
    Executor executor(std::move(values));
    executor.initialize(12, 2);
    executor.run_program();

    std::cout << executor.get_output() << std::endl;
    return 0;
}