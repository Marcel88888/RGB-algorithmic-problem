#include <gtest/gtest.h>
#include "algorithm_lib/InitialTripleSearch.h"
#include "algorithm_lib/PrintingUtilities.h"


TEST(InitialTripleSearch, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {G, B, R, G, B, B, R, B, G, R, G, R};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, B, G};
    std::vector<int> expectedIndexes = {2, 6, 0, 0, 5, 3, 3};
    EXPECT_EQ(expectedIndexes,
              InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(elements, 100).indexesOfMovedGroups);


    elements = {R, G, B, R, B, B, R, R, R, R, B, G, R, B, G, R, B, R, G, G, B, B, G, R, B, B, R};
    expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, B, R, R, B, R, B, B, R, R};
    for (int i : InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(elements, 100).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements) << "Actual and expected:\n" << elements << '\n' << expectedArrangement;
}


TEST(InitialTripleSearch, ElementsAreSortedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedSolution = {R, G, B, R, G, B, R, G, B, R, G, G};
    Solution solution = InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(elements, 3);
    EXPECT_EQ(expectedSolution, solution.arrangedElements)
                        << "Actual and expected:\n" << solution.arrangedElements << '\n' << expectedSolution;

    elements = {R, G, B, R, B, B, R, R, R, R, B, G, R, B, G, R, B, R, G, G, B, B, G, R, B, B, R};
    expectedSolution = {R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, R, G, B, B, R, R, B, R, B, B, R, R};
    solution = InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(elements, 100);
    EXPECT_EQ(expectedSolution, solution.arrangedElements)
                        << "Actual and expected:\n" << solution.arrangedElements << '\n' << expectedSolution;
}




