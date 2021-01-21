project(RGB_algorithmic_problem)

add_library(algorithm_lib STATIC RgbAlgorithmUtilities.cpp BreadthSearch.cpp RandomUtilities.cpp NaiveSorting.h NaiveSorting.cpp InitialTripleSearch.cpp InitialTripleSearch.h AdvancedSort.cpp AdvancedSort.h MatchingGroup.cpp MatchingGroup.h WindowsPrintingUtilities.cpp WindowsPrintingUtilities.h PrintingUtilities.cpp PrintingUtilities.h TimeMeasurment.cpp TimeMeasurment.h)

if (UNIX)
    #    Time measurement
    target_link_libraries(algorithm_lib librt)
endif (UNIX)