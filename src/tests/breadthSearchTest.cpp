#include <gtest/gtest.h>
#include <ostream>
#include "algorithm_lib/breadthSearch.h"

TEST(BreadthSearch, branchValuesAreExtractedCorrectly) {
    Node<int> n0(0, nullptr);
    Node<int> n1(1, std::make_shared<Node<int>>(n0));
    Node<int> n2(2, std::make_shared<Node<int>>(n1));
    Node<int> n3(3, std::make_shared<Node<int>>(n2));
    std::vector<Node<int>> vec{n0, n1, n2, n3};
    const std::vector<int> &extractedValues = BreadthSearchAlgorithm::nodeValuesFromGivenNodeToRoot(n3);
    EXPECT_EQ(extractedValues, std::vector<int>({3, 2, 1, 0}));
}

TEST(BreadthSearch, movementIndexesAreCorrectlyCalculated) {
    std::vector<RgbElement> elements{G, B, R, R, B, R, G, G, G, B};
    Solution s = BreadthSearchAlgorithm::solution(elements);
    for (const int ind :s.indexesOfRgbGroups) {
        moveTripleBack(elements, ind);
    }
    ASSERT_EQ(elements, s.arrangedElements);
}

TEST(BreadthSearch, calculatesSolutionInDifferentCases) {
    std::vector<std::pair<std::vector<RgbElement>, Solution>> expectedSolutionsForGivenElements{
            {{R, G, B},                      Solution({R, G, B}, {})},
            {{R, G, B, G},                   Solution({R, G, B, G}, {})},
            {{G, R, G, B},                   Solution({R, G, B, G}, {0, 0, 0})},
            {{G, B, R, R, B, R, G, G, G, B}, Solution({R, G, B, R, G, B, R, G, B, G},
                                                      {0, 3, 1, 6, 5})}
    };
    for (const auto &ElementsSolutionPair : expectedSolutionsForGivenElements) {
        const Solution &calculatedSolution = BreadthSearchAlgorithm::solution(ElementsSolutionPair.first);
        ASSERT_EQ(calculatedSolution, ElementsSolutionPair.second);
    }
}