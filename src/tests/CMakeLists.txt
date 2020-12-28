project(RGB_algorithmic_problem)

add_executable(Google_Tests_run utilitesTest.cpp breadthSearchTest.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main algorithm_lib)
target_include_directories(Google_Tests_run PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../)