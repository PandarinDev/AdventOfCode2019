add_subdirectory(Part1)

add_executable(Day5Tests day5_tests.cpp)
target_link_libraries(Day5Tests Catch2::Catch2)
catch_discover_tests(Day5Tests)