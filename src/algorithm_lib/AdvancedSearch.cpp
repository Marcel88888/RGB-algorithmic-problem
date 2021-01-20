#include <iostream>
#include "AdvancedSearch.h"

const int kGroupSize = kRgbElements.size();

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


std::vector<int> AdvancedSearch::findPositionsOfMatchedGroups(
        std::vector<RgbElement>::const_iterator beg,
        std::vector<RgbElement>::const_iterator end,
        const std::vector<MatchingGroup> &matchingGroups) {
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


bool makeMovements(
        int leftBoundIncluding,
        int rightBoundExcluding,
        std::vector<RgbElement> &elements,
        const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)> &moveTripleBack) {
    bool existsMoreThanOneGroup = rightBoundExcluding - leftBoundIncluding >= 2 * kGroupSize;
    if (existsMoreThanOneGroup) {
        for (const GroupsAndPositionOfMidTriple &groupsAndPos : groupsAndMidTriplePositions) {
            const MatchingGroup &leftMatchingGroup = groupsAndPos.first.first;
            const MatchingGroup &rightMatchingGroup = groupsAndPos.first.second;

            std::vector<int> foundPositions = AdvancedSearch::findPositionsOfMatchedGroups(
                    elements.cbegin() + leftBoundIncluding,
                    elements.cbegin() + rightBoundExcluding,
                    {leftMatchingGroup, rightMatchingGroup});
//            Make movements if there were found some positions
            if (!foundPositions.empty()) {
                for (int &foundPosition : foundPositions) { foundPosition += leftBoundIncluding; }
//                mid group position is recalculated because there
//                will be moved 2 triples containing mid triple
                const int midGroupOffset = (int) elements.size() - 2 * kGroupSize + leftBoundIncluding;
                const int recalculatedMidGroupPosition = groupsAndPos.second + midGroupOffset;
                auto calculatedPositions = calculatedPositionsForMakingSequentialMovements(foundPositions);
                calculatedPositions.push_back(recalculatedMidGroupPosition);
                for (const auto &pos : calculatedPositions)
                    moveTripleBack(elements, pos);

                return true;
            }
        }
    }
    return false;
}

Solution AdvancedSearch::solution(const std::vector<RgbElement> &elements) {
//    Pre-checks
    if (elements.size() < kGroupSize) return Solution();
    if (elements.size() % 3 != 0) {
        std::cerr << "The amount of the given elements should be divisible by 3" << std::endl;
        return Solution();
    }
    const int kMaxRgbGroupsAmount = maxRgbGroupsAmount(elements);
    if (areElementsArrangedCorrectly(elements, kMaxRgbGroupsAmount)) {
        return Solution(elements, {});
    }

    std::vector<RgbElement> elementsCopy(elements);
    std::vector<int> indexesOfMovedGroups;
    const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)>
            moveAndSaveIndex = [&indexesOfMovedGroups]
            (std::vector<RgbElement> &elements, int groupPosition) -> std::vector<RgbElement> & {
        moveTripleBack(elements, groupPosition);
        indexesOfMovedGroups.push_back(groupPosition);
        return elements;
    };

    bool movementsWereMade;
    int leftBoundIncluding = 0;
    do {
        //    Move all all the found rgb triples to the end
        std::vector<int> positions = positionsOfAllExistingRgbTriples(
                elementsCopy.cbegin() + leftBoundIncluding, elementsCopy.cend());
        for (int &foundPosition : positions) { foundPosition += leftBoundIncluding; }
        std::vector<int> p = calculatedPositionsForMakingSequentialMovements(positions);
        const int kNumberOfFoundInitialTriples = p.size();
        for (const auto &pos : p)
            moveAndSaveIndex(elementsCopy, pos);

        int rightBoundExcluding = (int) elementsCopy.size() - kNumberOfFoundInitialTriples * kGroupSize;
        movementsWereMade = makeMovements(leftBoundIncluding, rightBoundExcluding, elementsCopy, moveAndSaveIndex);

        int numberOfMovedElementsBeforeRightBound = movementsWereMade ? 2 * kGroupSize : 0;
        int numberOfUnsortedAtTheBeginning = (rightBoundExcluding - numberOfMovedElementsBeforeRightBound) / 3;
        for (int i = 0; i < numberOfUnsortedAtTheBeginning; ++i) {
            moveAndSaveIndex(elementsCopy, 0);
        }
//        at the beginning we move "kNumberOfFoundInitialTriples" triples back and 2 groups matched groups
        leftBoundIncluding = (kNumberOfFoundInitialTriples + 2) * kGroupSize;
    } while (movementsWereMade);

    return Solution(elementsCopy, indexesOfMovedGroups);
}

std::vector<int> AdvancedSearch::positionsOfAllExistingRgbTriples(
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
