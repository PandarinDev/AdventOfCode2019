add_subdirectory(Part1)

add_executable(Day3Tests day3_tests.cpp)
target_link_libraries(Day3Tests Catch2::Catch2)
catch_discover_tests(Day3Tests)