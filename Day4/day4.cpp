#include <cstdint>
#include <vector>
#include <algorithm>

std::vector<std::int8_t> get_digits_of_number(std::size_t num) {
    std::vector<std::int8_t> digits;
    while (num > 0) {
        digits.emplace_back(static_cast<std::int8_t>(num % 10));
        num /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

