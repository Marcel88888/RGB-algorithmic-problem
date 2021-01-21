cmake_minimum_required(VERSION 3.17)
project(RGB_algorithmic_problem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/googletest)
add_subdirectory(src/tests)
add_subdirectory(src/algorithm_lib)

add_executable(RGB_algorithmic_problem src/main.cpp src/InteractionWithUser.cpp src/InteractionWithUser.h src/Commands.cpp src/Commands.h src/CommandLineArgumentsParsing.cpp src/CommandLineArgumentsParsing.h)
target_link_libraries(RGB_algorithmic_problem algorithm_lib)


target_compile_options(RGB_algorithmic_problem BEFORE PUBLIC
-Werror
-Wall
-Wextra
-Wpedantic
-O2
#
#        -Wcast-align
#        -Wcast-qual
#        -Wconversion
#        -Wctor-dtor-privacy
#        -Wenum-compare
#        -Wfloat-equal
#        -Wnon-virtual-dtor
#        -Wold-style-cast
#        -Woverloaded-virtual
#        -Wredundant-decls
#        -Wsign-conversion
#        -Wsign-promo
)
