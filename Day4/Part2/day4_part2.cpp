#include "../day4.cpp"

bool number_matches_criteria(std::size_t num) {
    std::vector<std::int8_t> digits = get_digits_of_number(num);
    bool never_decreased = true;
    for (std::size_t i = 1; i < digits.size(); ++i) {
        if (digits[i] < digits[i - 1]) {
            never_decreased = false;
            break;
        }
    }

    bool has_exactly_double = false;
    std::size_t consecutive_counter = 0;
    for (std::size_t i = 1; i < digits.size(); ++i) {
        if (digits[i] == digits[i - 1]) {
            ++consecutive_counter;
        }
        else if (consecutive_counter == 1) {
            has_exactly_double = true;
            break;
        }
        else {
            consecutive_counter = 0;
        }
    }
    // Run the terminating condition for the last number too
    has_exactly_double |= (consecutive_counter == 1);

    return never_decreased && has_exactly_double;
}