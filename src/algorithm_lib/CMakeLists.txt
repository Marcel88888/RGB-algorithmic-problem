project(RGB_algorithmic_problem)

add_library(algorithm_lib STATIC RgbAlgorithmUtilities.cpp BreadthSearch.cpp RandomUtilities.cpp NaiveSorting.h NaiveSorting.cpp InitialTripleSearch.cpp InitialTripleSearch.h AdvancedSearch.cpp AdvancedSearch.h MatchingGroup.cpp MatchingGroup.h)