#include "../day4.cpp"

bool number_matches_criteria(std::size_t num) {
    std::vector<std::int8_t> digits = get_digits_of_number(num);
    bool never_decreased = true;
    bool has_double = false;
    for (std::size_t i = 1; i < digits.size(); ++i) {
        if (digits[i] < digits[i - 1]) {
            never_decreased = false;
            break;
        }
        has_double |= (digits[i] == digits[i - 1]);
    }
    return never_decreased && has_double;
}