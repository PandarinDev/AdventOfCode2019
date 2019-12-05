#include <cstddef>

std::size_t calculate_required_fuel_for_mass(std::size_t mass) {
    std::size_t division_result = mass / 3;
    // Avoid underflowing with the subtraction
    return (division_result > 2)
        ? division_result - 2
        : 0ull;
}

std::size_t calculate_required_fuel_for_mass_recursive(std::size_t mass) {
    std::size_t accumulator = 0;
    std::size_t fuel_required = calculate_required_fuel_for_mass(mass);
    while (fuel_required > 0) {
        accumulator += fuel_required;
        fuel_required = calculate_required_fuel_for_mass(fuel_required);
    }

    return accumulator;
}