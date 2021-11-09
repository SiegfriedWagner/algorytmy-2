add_executable(Hashset_tests int32.cpp)
add_compile_definitions(VERBOSE)
target_link_libraries(Hashset_tests gtest gmock gtest_main)