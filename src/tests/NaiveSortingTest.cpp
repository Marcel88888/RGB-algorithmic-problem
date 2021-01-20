#include <gtest/gtest.h>
#include "algorithm_lib/NaiveSorting.h"


TEST(NaiveSorting, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, G};
    std::vector<int> expectedIndexes = {2, 3, 7, 7, 8, 8};
    for (int i : NaiveSorting::sort(elements, 3).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements);
}


TEST(NaiveSorting, ElementsAreSortedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedSolution = {R, G, B, R, G, B, R, G, B, R, G, G};
    Solution solution = NaiveSorting::sort(elements, 3);
    EXPECT_EQ(expectedSolution, solution.arrangedElements);
}


