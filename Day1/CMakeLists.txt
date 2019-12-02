add_executable(Day1 main.cpp)
set_target_properties(Day1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Day1Tests day1_tests.cpp)
target_link_libraries(Day1Tests Catch2::Catch2)
catch_discover_tests(Day1Tests)