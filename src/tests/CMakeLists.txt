project(RGB_algorithmic_problem)

add_executable(run_all_tests AlgorithmUtilitiesTest.cpp BreadthSearchTest.cpp RandomUtilitiesTest.cpp AdvanceSearchTest.cpp NaiveSortingTest.cpp InitialTripleSearchTest.cpp)
target_link_libraries(run_all_tests gtest gtest_main algorithm_lib)
target_include_directories(run_all_tests PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../)