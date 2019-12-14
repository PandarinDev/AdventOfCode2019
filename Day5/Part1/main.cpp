#include "../day5.cpp"

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include <cstdlib>

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
    auto input_supplier = []() { return 1; };
    auto output_consumer = [](const std::size_t& output, const std::optional<Operation>& next_operation) {
        // If the next operation is a halt this is not an error code, but the diagnostic code
        if (next_operation && next_operation->opcode == Opcode::HALT) {
            std::cout << output << std::endl;
        }
        // Otherwise this is an error code and we're supposed to stop if we receive a non-zero value
        if (output != 0) {
            std::cerr << "Operation was off by " + std::to_string(output) << std::endl;
            std::exit(1);
        }
    };
    Executor executor(std::move(values), input_supplier, output_consumer);
    executor.run_program();
    return 0;
}