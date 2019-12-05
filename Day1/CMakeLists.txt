add_subdirectory(Part1)
add_subdirectory(Part2)

add_executable(Day1Tests day1_tests.cpp)
target_link_libraries(Day1Tests Catch2::Catch2)
catch_discover_tests(Day1Tests)