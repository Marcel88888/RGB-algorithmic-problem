#include <iostream>
#include "AdvancedSearch.h"

int AdvancedSearch::positionOfFirstMatchedGroup(MatchingGroup matchingGroup,
                                                std::vector<RgbElement>::const_iterator beg,
                                                std::vector<RgbElement>::const_iterator end) {
    int counter = 0;
    const int groupSize = kRgbElements.size();
    std::vector<RgbElement> currentTriple;
    const auto nextTriple = [](const RgbElement &newElement, std::vector<RgbElement> &previousTriple) {
        return std::vector<RgbElement>({previousTriple[1], previousTriple[2], newElement});
    };

//    if there are at list "groupSize" elements more
    if (beg + (groupSize - 1) <= end) {
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

std::vector<int> calculatedPositionsForMakingSequentialMovements(const std::vector<int> &positions) {
    const int kGroupSize = kRgbElements.size();
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


Solution AdvancedSearch::solution(const std::vector<RgbElement> &elements) {
//    Pre-checks
    const int kGroupSize = kRgbElements.size();
    if (elements.size() < kGroupSize) return Solution();
    const int kMaxRgbGroupsAmount = maxRgbGroupsAmount(elements);
    if (areElementsArrangedCorrectly(elements, kMaxRgbGroupsAmount)) {
        return Solution(elements, {});
    }

    std::vector<RgbElement> elementsCopy(elements);
    std::vector<int> indexesOfMovedGroups;
    const auto moveAndSaveIndex = [&elementsCopy, &indexesOfMovedGroups](int groupPosition) {
        moveTripleBack(elementsCopy, groupPosition);
        indexesOfMovedGroups.push_back(groupPosition);
        return elementsCopy;
    };

//    Move all all the found rgb triples to the end
    std::vector<int> p = calculatedPositionsForMakingSequentialMovements(
            positionsOfAllExistingRgbTriples(elementsCopy));
    const int kNumberOfFoundInitialTriples = p.size();
    for (const auto &pos : p)
        moveAndSaveIndex(pos);

//    Move matched groups to the end
    bool shouldFindMorePairs = true;
    int rightBoundExcluding = (int) elementsCopy.size() - kNumberOfFoundInitialTriples * kGroupSize;
    while (shouldFindMorePairs) {
        shouldFindMorePairs = false;
        for (const GroupsAndPositionOfMidTriple &groupsAndPos : groupsAndMidTriplePositions) {
            if (rightBoundExcluding >= 2 * kGroupSize) {
                const MatchingGroup &leftMatchingGroup = groupsAndPos.first.first;
                const MatchingGroup &rightMatchingGroup = groupsAndPos.first.second;
                const int midGroupOffset = (int) elements.size() - 2 * kGroupSize;
//                mid group position is recalculated because we make 2 movements before
                const int editedMidGroupPosition = groupsAndPos.second + midGroupOffset;
                std::vector<int> foundPositions = findPositionsOfMatchedGroups(
                        elementsCopy.cbegin(),
                        elementsCopy.cbegin() + rightBoundExcluding,
                        {leftMatchingGroup, rightMatchingGroup});
                if (!foundPositions.empty()) {
                    auto calculatedPositions = calculatedPositionsForMakingSequentialMovements(foundPositions);
                    calculatedPositions.push_back(editedMidGroupPosition);
                    for (const auto &pos : calculatedPositions)
                        moveAndSaveIndex(pos);
                    shouldFindMorePairs = true;
                    rightBoundExcluding -= 3 * kGroupSize;
                }
            }
        }
    }
    return Solution(elementsCopy, indexesOfMovedGroups);
}

std::vector<int> AdvancedSearch::findPositionsOfMatchedGroups(
        std::vector<RgbElement>::const_iterator beg,
        std::vector<RgbElement>::const_iterator end,
        const std::vector<MatchingGroup> &matchingGroups) {
    const int kGroupSize = kRgbElements.size();
    std::vector<int> foundPositions;
    int offset = 0;
    for (const auto &group : matchingGroups) {
        int foundPos = offset + AdvancedSearch::positionOfFirstMatchedGroup(group, beg + offset, end);
        if (foundPos != -1) {
            foundPositions.push_back(foundPos);
            offset += kGroupSize;
        } else {
            return {};
        }
    }
    return foundPositions;
}

std::vector<int> AdvancedSearch::positionsOfAllExistingRgbTriples(
        const std::vector<RgbElement> &elements) {
    const int kGroupSize = kRgbElements.size();
    const auto &beg = elements.cbegin();
    const auto &end = elements.cend();
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
