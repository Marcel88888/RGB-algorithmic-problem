#include <gtest/gtest.h>
#include "algorithm_lib/AdvancedSort.h"


TEST(AdvancedSort, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, G};
    std::vector<int> expectedIndexes = {3, 6, 0, 0, 8};
    for (int i : AdvancedSort::solution(elements).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements);
}

TEST(AdvancedSort, ElementsAreArrangedCorrectly) {
    std::vector<std::pair<std::vector<RgbElement>, std::vector<RgbElement>>> BeforeAfterSolution =
            {
                    {{R, G, G, R, B, B},                                              {R, G, B, G, R, B}},
                    {{R, G, B, R, G, B},                                              {R, G, B, R, G, B}},
                    {{R, B, G, G, G, B},                                              {R, G, B, B, G, G}},
                    {{R, G, R, R, G, B, G, G, B, R, G, B},                            {R, G, B, R, G, B, R, G, B, R, G, G}},
                    {{B, R, G, B, R, G, G, G, G, G, G, G, B, R, G, B, R, G, B, G, G}, {R, G, B, R, G, B, R, G, B, R, G, B, G, G, G, B, G, G, G, G, G}}};
    for (const auto &pair : BeforeAfterSolution) {
        EXPECT_EQ(AdvancedSort::solution(pair.first).arrangedElements, pair.second);
    }
}
