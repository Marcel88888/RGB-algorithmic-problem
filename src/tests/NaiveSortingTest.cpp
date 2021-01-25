#include <gtest/gtest.h>
#include "algorithm_lib/NaiveSorting.h"
#include "algorithm_lib/PrintingUtilities.h"


TEST(NaiveSorting, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, G};
    std::vector<int> expectedIndexes = {2, 3, 7, 7, 8, 8};
    EXPECT_EQ(expectedIndexes, NaiveSorting::sort(elements).indexesOfMovedGroups);

    elements = {G, R, B, B, G, G, R, R, G, B, R, G, G, B, B, G, B, G, B, G, B, B, B, R, R, R, G};
    expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, G, B, B, G, G, B};
    for (int i : NaiveSorting::sort(elements).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements);
}


TEST(NaiveSorting, ElementsAreSortedCorrectly) {
    std::vector<std::pair<std::vector<RgbElement>, std::vector<RgbElement>>> testCases =
            {
                    {{R, G, R, R, G, B, G, G, B, R, G, B},
                            {R, G, B, R, G, B, R, G, B, R, G, G}},
                    {{G, R, B, B, G, G, R, R, G, B, R, G, G, B, B, G, B, G, B, G, B, B, B, R, R, R, G},
                            {R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, G, B, B, G, G, B}}
            };

    for (const auto &testCase : testCases) {
        Solution solution = NaiveSorting::sort(testCase.first);
        EXPECT_EQ(testCase.second, solution.arrangedElements) <<
                                                              "Actual and expected:\n" << solution.arrangedElements
                                                              << '\n' << testCase.second;
    }
}


