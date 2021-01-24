#ifndef RGB_ALGORITHMIC_PROBLEM_ADVANCEDSORT_H
#define RGB_ALGORITHMIC_PROBLEM_ADVANCEDSORT_H

#include "RgbAlgorithmUtilities.h"
#include <vector>
#include "AdvancedSort.h"
#include "MatchingGroup.h"
#include "WindowsPrintingUtilities.h"

class AdvancedSort {
public:
    static int positionOfFirstMatchedGroup(const MatchingGroup &matchingGroup,
                                           std::vector<RgbElement>::const_iterator beg,
                                           std::vector<RgbElement>::const_iterator end);

    /// Find the positions of all RGB groups that exist in the given vector of elements.
    /// \param beg: beginning iterator over rgb elements
    /// \param end: ending iterator over rgb elements
    /// \return vector of the found positions, empty if no groups were matched
    static std::vector<int> positionsOfAllExistingRgbTriples(
            std::vector<RgbElement>::const_iterator beg,
            std::vector<RgbElement>::const_iterator end);

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

    /// Get the solution as the result of merging 2 solutions. There are taken "startingIndexOfNextSolutionElements"
    /// elements of the solution 1 and the remaining elements will be taken from the s2
    /// \param s1
    /// \param s2
    /// \param startingIndexOfNextSolutionElements
    /// \return the solution where elements will be partly taken from the s1.arrangedElements and s2.arrangedElements and
    /// all the indexes will be merged
    static Solution mergedSolutions(const Solution &s1, const Solution &s2, int startingIndexOfNextSolutionElements);
};


#endif //RGB_ALGORITHMIC_PROBLEM_ADVANCEDSORT_H
