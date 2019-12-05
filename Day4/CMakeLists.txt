add_subdirectory(Part1)
add_subdirectory(Part2)

add_executable(Day4Tests day4_tests.cpp)
target_link_libraries(Day4Tests Catch2::Catch2)
catch_discover_tests(Day4Tests)