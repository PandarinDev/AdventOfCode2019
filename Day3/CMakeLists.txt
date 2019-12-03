add_executable(Day3 main.cpp)
set_target_properties(Day3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Day3Tests day3_tests.cpp)
target_link_libraries(Day3Tests Catch2::Catch2)
catch_discover_tests(Day3Tests)