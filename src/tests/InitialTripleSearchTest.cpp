#include <gtest/gtest.h>
#include "algorithm_lib/InitialTripleSearch.h"


TEST(InitialTripleSearch, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {G, B, R, G, B, B, R, B, G, R, G, R};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, B, G};
    std::vector<int> expectedIndexes = {2, 6, 0, 0, 5, 3, 3, 9, 9, 9};
    for (int i : InitialTripleSearch::sort(elements, 3).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements);
}


TEST(InitialTripleSearch, ElementsAreSortedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedSolution = {R, G, B, R, G, B, R, G, B, R, G, G};
    Solution solution = InitialTripleSearch::sort(elements, 3);
    EXPECT_EQ(expectedSolution, solution.arrangedElements);
}




