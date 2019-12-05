#include "day4_part1.cpp"
#include <iostream>

int main(int argc, char** argv) {
    std::size_t lower_bound = 153517;
    std::size_t upper_bound = 630395;
    std::size_t matching_numbers = 0;
    // Just brute-force the solution
    for (std::size_t number = lower_bound; number <= upper_bound; ++number) {
        if (number_matches_criteria(number)) {
            ++matching_numbers;
        }
    }
    std::cout << matching_numbers << std::endl;
    return 0;
}