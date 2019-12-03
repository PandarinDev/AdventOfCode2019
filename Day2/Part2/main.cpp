#include "../day2.cpp"

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    constexpr auto EXPECTED_RESULT = 19690720;

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
    std::size_t result = 0;
    // Both noun and verb are between [0, 99] so we just brute-force the result
    for (std::size_t noun = 0; noun <= 99; ++noun) {
        for (std::size_t verb = 0; verb <= 99; ++verb) {
            Executor executor(values);
            executor.initialize(noun, verb);
            executor.run_program();
            result = executor.get_output();
            if (result == EXPECTED_RESULT) {
                std::cout << 100 * noun + verb << std::endl;
                return 0;
            }
        }
    }
    std::cerr << "Couldn't find required noun and verb for expected result." << std::endl;
    return 1;
}