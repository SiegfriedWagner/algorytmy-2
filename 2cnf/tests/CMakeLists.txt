add_executable(test_2cnf test_2cnf.cpp)
add_compile_definitions(VERBOSE)
target_link_libraries(test_2cnf gtest gmock gtest_main)