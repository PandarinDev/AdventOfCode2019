#include "../day4.cpp"

bool number_matches_criteria(std::size_t num) {
    std::vector<std::int8_t> digits = get_digits_of_number(num);
    bool never_decreased = true;
    bool has_exactly_double = false;
    for (std::size_t i = 1; i < digits.size(); ++i) {
        if (digits[i] < digits[i - 1]) {
            never_decreased = false;
            break;
        }
        bool is_double = (digits[i] == digits[i - 1]);
        is_double &= (i < digits.size() - 1)
            ? (digits[i] != digits[i + 1])
            : (digits[i] != digits[i - 2]);
        has_exactly_double |= is_double;
    }
    return never_decreased && has_exactly_double;
}