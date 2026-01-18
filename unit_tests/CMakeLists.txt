
add_executable(xfichecker_tests "unit_test.cpp")

target_link_libraries(xfichecker_tests PRIVATE 
    xfichecker_libs 
    gtest_main 
    gtest
)

include(GoogleTest)
gtest_discover_tests(xfichecker_tests)
