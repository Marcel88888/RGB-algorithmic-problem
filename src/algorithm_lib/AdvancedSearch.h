#ifndef RGB_ALGORITHMIC_PROBLEM_ADVANCEDSEARCH_H
#define RGB_ALGORITHMIC_PROBLEM_ADVANCEDSEARCH_H

#include "RgbAlgorithmUtilities.h"
#include <vector>
#include "AdvancedSearch.h"
#include "MatchingGroup.h"

class AdvancedSearch {
public:
    static int positionOfFirstMatchedGroup(MatchingGroup matchingGroup,
                                           std::vector<RgbElement>::const_iterator beg,
                                           std::vector<RgbElement>::const_iterator end);

    /// Find the positions of all RGB groups that exist in the given vector of elements.
    /// \param elements: vector of rgb elements
    /// \return vector of the found positions, empty if no groups were matched
    static std::vector<int> positionsOfAllExistingRgbTriples(const std::vector<RgbElement> &elements);

    /// For each given matching group find the position of the matched group. Each next group is searched
    /// starting after the last element of the last found group (not from the beginning)
    /// \param beg: beginning iterator containing rgb values
    /// \param end: ending iterator containing rgb values
    /// \param matchingGroups: groups that will be matched with the groups containing elements over which we iterate
    /// \return vector of the found positions, empty if no groups were matched
    static std::vector<int> findPositionsOfMatchedGroups(
            std::vector<RgbElement>::const_iterator beg,
            std::vector<RgbElement>::const_iterator end,
            const std::vector<MatchingGroup> &matchingGroups);

    static Solution solution(const std::vector<RgbElement> &elements);
};


#endif //RGB_ALGORITHMIC_PROBLEM_ADVANCEDSEARCH_H
