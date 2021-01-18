#include <gtest/gtest.h>
#include "algorithm_lib/AdvancedSearch.h"


TEST(AdvancedSearch, SolutionIndexesAreCalculatedCorrectly) {
    std::vector<RgbElement> elements = {R, G, R, R, G, B, G, G, B, R, G, B};
    std::vector<RgbElement> expectedArrangement = {R, G, B, R, G, B, R, G, B, R, G, G};
    std::vector<int> expectedIndexes = {3, 6, 0, 0, 8};
    for (int i : AdvancedSearch::solution(elements).indexesOfMovedGroups) {
        moveTripleBack(elements, i);
    }
    EXPECT_EQ(expectedArrangement, elements);
}

TEST(AdvancedSearch, ElementsAreArrangedCorrectly) {
    std::vector<std::pair<std::vector<RgbElement>, std::vector<RgbElement>>> BeforeAfterSolution =
            {{{R, G, R, R, G, B, G, G, B, R, G, B}, {R, G, B, R, G, B, R, G, B, R, G, G}},
             {{R, G, B, R, G, B},                   {R, G, B, R, G, B}},
             {{R, G, G, R, B, B},                   {R, G, B, G, R, B}},
             {{R, B, G, G, G, B},                   {R, G, B, B, G, G}}};
    for (const auto &pair : BeforeAfterSolution) {
        EXPECT_EQ(AdvancedSearch::solution(pair.first).arrangedElements, pair.second);
    }
}
