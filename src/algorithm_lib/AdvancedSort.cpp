#include <iostream>
#include "AdvancedSort.h"

const int kGroupSize = kRgbElements.size();

int AdvancedSort::positionOfFirstMatchedGroup(const MatchingGroup &matchingGroup,
                                              std::vector<RgbElement>::const_iterator beg,
                                              std::vector<RgbElement>::const_iterator end) {
    int counter = 0;
    const int groupSize = kRgbElements.size();
    std::vector<RgbElement> currentTriple;
    const auto nextTriple = [](const RgbElement &newElement, std::vector<RgbElement> &previousTriple) {
        return std::vector<RgbElement>({previousTriple[1], previousTriple[2], newElement});
    };

//    if there are at list "groupSize" elements more
    if (beg + groupSize <= end) {
        currentTriple = {*beg++, *beg++, *beg};

        while (beg != end) {
            if (matchingGroup.matches(currentTriple.cbegin(), currentTriple.cend())) {
                return counter;
            }
            beg = next(beg);
            currentTriple = nextTriple(*beg, currentTriple);
            counter++;
        }
    }
    return -1;
}

/// After making group movements the positions of other groups are changed, so this function recalculates them.
/// Positions will be calculated correctly only when we move groups at ascending indexes (meaning next group position > prev group position)
std::vector<int> calculatedPositionsForMakingSequentialMovements(const std::vector<int> &positions) {
    std::vector<int> out;

//   + 1 is just for an extra space (I need it because I will push one more value to the vec)
    out.reserve(positions.size() + 1);
    for (int i = 0; i < positions.size(); ++i)
        out.push_back(positions[i] - kGroupSize * i);
    return out;
}

using GroupsAndPositionOfMidTriple = std::pair<std::pair<MatchingGroup, MatchingGroup>, int>;
const inline std::vector<GroupsAndPositionOfMidTriple> groupsAndMidTriplePositions =
        {{{MatchingGroup({R, G, AnyElement}),
                  MatchingGroup({AnyElement, AnyElement, B})}, 2},
         {{MatchingGroup({R, AnyElement, AnyElement}),
                  MatchingGroup({AnyElement, G, B})},          1}};


std::vector<int> AdvancedSort::findPositionsOfMatchedGroups(
        std::vector<RgbElement>::const_iterator beg,
        std::vector<RgbElement>::const_iterator end,
        const std::vector<MatchingGroup> &matchingGroups) {
    std::vector<int> foundPositions;
    int offset = 0;
    for (const auto &group : matchingGroups) {
        int foundPos = AdvancedSort::positionOfFirstMatchedGroup(group, beg + offset, end);
        if (foundPos != -1) {
            foundPositions.push_back(foundPos + offset);
            offset = foundPos + kGroupSize;
        } else {
            return {};
        }
    }
    return foundPositions;
}


/// Main algorithm function where we look for the matching groups -> move them to the end -> move the middle group to the end
bool makeMovements(
        int rightBoundExcluding,
        std::vector<RgbElement> &elements,
        const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)> &moveTripleBack) {
    const bool existsMoreThanOneGroup = rightBoundExcluding >= 2 * kGroupSize;
    if (!existsMoreThanOneGroup) return false;
    for (const GroupsAndPositionOfMidTriple &groupsAndPos : groupsAndMidTriplePositions) {
        const MatchingGroup &leftMatchingGroup = groupsAndPos.first.first;
        const MatchingGroup &rightMatchingGroup = groupsAndPos.first.second;

        std::vector<int> foundPositions = AdvancedSort::findPositionsOfMatchedGroups(
                elements.cbegin(),
                elements.cbegin() + rightBoundExcluding,
                {leftMatchingGroup, rightMatchingGroup});
//            Make movements if there were found some positions
        if (!foundPositions.empty()) {
//                mid group position is recalculated because there
//                will be moved 2 triples containing mid triple
            const int midGroupOffset = (int) elements.size() - 2 * kGroupSize;
            const int recalculatedMidGroupPosition = groupsAndPos.second + midGroupOffset;
            auto calculatedPositions = calculatedPositionsForMakingSequentialMovements(foundPositions);
            calculatedPositions.push_back(recalculatedMidGroupPosition);
            for (const auto &pos : calculatedPositions)
                moveTripleBack(elements, pos);
            return true;
        }
    }

    return false;
}

Solution mergedSolutions(const Solution &s1, const Solution &s2, int startingIndexOfNextSolutionElements) {
    const unsigned long long int elementsNumber = s1.arrangedElements.size();
    int j = 0;
    std::vector<RgbElement> elements;
    std::vector<int> positions;
    elements.reserve(elementsNumber);
//    Push elements from s1 and s2
    auto it1 = s1.arrangedElements.cbegin();
    auto it2 = s2.arrangedElements.cbegin();
    for (int i = 0; i < startingIndexOfNextSolutionElements; ++i) {
        elements.push_back(*it1++);
    }
    for (int i = startingIndexOfNextSolutionElements; i < elementsNumber; ++i) {
        elements.push_back(*it2++);
    }
//    Push indexes
    for (int ind : s1.indexesOfMovedGroups) {
        positions.push_back(ind);
    }
    for (int ind : s2.indexesOfMovedGroups) {
        positions.push_back(ind);
    }
    return Solution(elements, positions);
}


Solution AdvancedSort::solution(const std::vector<RgbElement> &elements) {
//    Pre-checks
    if (elements.size() <= kGroupSize) return Solution(elements);
    if (elements.size() % 3 != 0) {
        std::cerr << "The amount of the given elements should be divisible by 3" << std::endl;
        return Solution();
    }
    const int kMaxRgbGroupsAmount = maxRgbGroupsAmount(elements);
    if (areElementsArrangedCorrectly(elements, kMaxRgbGroupsAmount)) {
        return Solution(elements);
    }
//    Preparations
    std::vector<RgbElement> elementsCopy(elements);
    const int groupsAmount = (int) elementsCopy.size() / 3;
    std::vector<int> indexesOfMovedGroups;
    const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)> moveAndSaveIndex
            = [&indexesOfMovedGroups](std::vector<RgbElement> &elements,
                                      int groupPosition) -> std::vector<RgbElement> & {
                if (groupPosition < elements.size() - kGroupSize) {
                    moveTripleBack(elements, groupPosition);
                    indexesOfMovedGroups.push_back(groupPosition);
                }
                return elements;
            };

    //    Move all all the found rgb triples to the end
    std::vector<int> positions = positionsOfAllExistingRgbTriples(
            elementsCopy.cbegin(), elementsCopy.cend());
    std::vector<int> p = calculatedPositionsForMakingSequentialMovements(positions);
    const int numberOfInitialMovements = p.size();
    const int numberOfUntouchedGroups = groupsAmount - numberOfInitialMovements;
    for (const auto &pos : p)
        moveAndSaveIndex(elementsCopy, pos);

    const int rightBoundExcluding = numberOfUntouchedGroups * kGroupSize;
    const bool movementsWereMade = makeMovements(rightBoundExcluding, elementsCopy, moveAndSaveIndex);

    const int numberOfGroupsToMoveToTheEnd = movementsWereMade ?
                                             numberOfUntouchedGroups - 2 :
                                             numberOfUntouchedGroups;
//    Move starting unsorted groups
    if (numberOfGroupsToMoveToTheEnd != groupsAmount) {
        for (int i = 0; i < numberOfGroupsToMoveToTheEnd; ++i) {
            moveAndSaveIndex(elementsCopy, 0);
        }
    }
    if (movementsWereMade) {
        int startingIndexOfNextSolutionElements = (numberOfInitialMovements + 1) * kGroupSize;
        std::vector<RgbElement> elementsForInnerSolution(elementsCopy.begin() + startingIndexOfNextSolutionElements,
                                                         elementsCopy.end());
        return mergedSolutions(Solution(elementsCopy, indexesOfMovedGroups),
                               solution(elementsForInnerSolution),
                               startingIndexOfNextSolutionElements);
    }

    return Solution(elementsCopy, indexesOfMovedGroups);
}

std::vector<int> AdvancedSort::positionsOfAllExistingRgbTriples(
        std::vector<RgbElement>::const_iterator beg,
        std::vector<RgbElement>::const_iterator end) {
    const auto leftMoreThan2Elements = [&beg, &end](int offset) { return beg + offset + 2 < end; };
    std::vector<int> foundPositions;

    int offset = 0;
    while (leftMoreThan2Elements(offset)) {
        int incValue;
        if (isRgbTriple(beg + offset)) {
            foundPositions.push_back(offset);
            incValue = kGroupSize;
        } else { incValue = 1; }
        offset += incValue;
    }
    return foundPositions;
}
