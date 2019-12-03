add_subdirectory(Part1)
add_subdirectory(Part2)

add_executable(Day2Tests day2_tests.cpp)
target_link_libraries(Day2Tests Catch2::Catch2)
catch_discover_tests(Day2Tests)