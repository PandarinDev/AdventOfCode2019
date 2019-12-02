#include <cstddef>

std::size_t calculate_required_fuel_for_mass(std::size_t mass) {
    return ((std::size_t) (mass / 3.0)) - 2;
}