#include "InitialTripleSearch.h"

using namespace std;

/// Counts rgb groups until it's found first non-rgb group
int countFirstRgbGroups(std::vector<RgbElement>::const_iterator beg,
                        std::vector<RgbElement>::const_iterator end) {
    const int groupSize = kRgbElements.size();
    const auto enoughElementsInNextGroup = [&beg, &end, &groupSize]() { return beg + (groupSize - 1) <= end; };
    int groupsAmount = 0;
    while (enoughElementsInNextGroup() && isRgbTriple(beg)) {
        groupsAmount++;
        beg += groupSize;
    }
    return groupsAmount;
}

/* - Phase 1: Take all RGB triples and put them at the end. The ramp will consist of a set of unsorted [N] balls at the bottom
 * + sorted [S] at the top.
 * - Phase 2: We wisely move the balls from the N set to the top. You can extract the first triple from the set N, which is
 * of the form [R, G, x], if there is no such, then extract [R, x, x] and move the selected triple to the end of the ramp.
 * Then we take the next best three from the set N again and carry it to the end. To select the next best group, we look
 * at the last color at the top of the ramp and try to find a three that starts with the next color. So if the last ball
 * is R, then it is better to choose [G, B, R], worse [G, B, x] and the least priority three is [G, x, x]. These
 * two phases are repeated until number of failures during sorting (after some time the algorithm does the same steps
 * all the time) reaches the limit of failures set calling sorting method.
 * Phase 3: After exceeding the limit of failed attempts on the sorted part, the NaiveSorting algorithm is triggered.
 */
void makeSortingStep(vector<RgbElement> &elements, int startingPoint, int groupSize,
                     const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)> &moveTripleBack) {
    int i = startingPoint;
    int sortedGroupsNumber = 0;

    // phase 1
    while (i < elements.size() - groupSize * sortedGroupsNumber - groupSize) {
        if (i >= 0 && isRgbTriple(elements.cbegin() + i)) {
            moveTripleBack(elements, i);
            sortedGroupsNumber++;
            // after moving a triple back there can appear a new rgb group out of the elements at the positions
            // i - 1 and i - 2 and i + 3 so check if this group can also be moved back
            i -= 2;
        } else { ++i; }
    }

    // phase 2
    int unsorted_balls = (int) elements.size() - sortedGroupsNumber * groupSize -
                         countFirstRgbGroups(elements.cbegin(), elements.cend()) * groupSize;
    int required_moves = unsorted_balls / groupSize;
    for (int j = 0; j < required_moves; ++j) {
        RgbElement last_value = elements.back();
        int next_req_val = (getElemReqPosition(last_value) + 1) % groupSize;
        int best_move_pos1 = -1; // with values [X,?,?]
        bool double_found = false;  // for values [X1,X2,?]
        bool triple_found = false; // for values [X1,X2,X3]
        for (int k = startingPoint;
             k <
             startingPoint + unsorted_balls - 2; ++k) {  // "unsorted_balls - 2" because in the loop I may move a triple
            // starting at k position and ending at k+2 position.
            if (elements[k] == kRgbElements[next_req_val]) {
                best_move_pos1 = k;
                if (elements[k + 1] == kRgbElements[(next_req_val + 1) % groupSize] &&
                    elements[k + 2] == kRgbElements[(next_req_val + 2) % groupSize]) {
                    moveTripleBack(elements, k);
                    unsorted_balls -= groupSize;
                    triple_found = true;
                    break;
                } else if (elements[k + 1] == kRgbElements[(next_req_val + 1) % groupSize]) {
                    moveTripleBack(elements, k);
                    unsorted_balls -= groupSize;
                    double_found = true;
                    break;
                }
            }
        }
        if (!triple_found && !double_found && best_move_pos1 != -1) {
            moveTripleBack(elements, best_move_pos1);
            unsorted_balls -= groupSize;
        } else if (!triple_found && !double_found) {
            moveTripleBack(elements, startingPoint);
            unsorted_balls -= groupSize;
        }
    }
}


Solution InitialTripleSearch::sort(const vector<RgbElement> &elements, int failuresLimit) {
    vector<RgbElement> elementsCopy(elements);
    int groupSize = kRgbElements.size();
    vector<int> indexesOfMovedGroups;
    const std::function<std::vector<RgbElement> &(std::vector<RgbElement> &, int)> moveAndSaveIndex
            = [&indexesOfMovedGroups, &groupSize](std::vector<RgbElement> &elements,
                                                  int groupPosition) -> std::vector<RgbElement> & {
                if (groupPosition < elements.size() - groupSize) {
                    moveTripleBack(elements, groupPosition);
                    indexesOfMovedGroups.push_back(groupPosition);
                }
                return elements;
            };
    int startPoint = (int) elementsCopy.size() % groupSize;
    int rgbGroupsAmount1, rgbGroupsAmount2;
    int failures = 0;
    while (failures < failuresLimit) {
        rgbGroupsAmount1 = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
        rgbGroupsAmount2 = rgbGroupsAmount1;

        makeSortingStep(
                elementsCopy,
                ((int) elementsCopy.size() % groupSize) + rgbGroupsAmount1 * groupSize,
                groupSize,
                moveAndSaveIndex);

        rgbGroupsAmount1 = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
        if (rgbGroupsAmount1 == rgbGroupsAmount2) {
            failures++;
        } else {
            failures = 0;
        }
    }
    return Solution(elementsCopy, indexesOfMovedGroups);
}

Solution InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(const vector<RgbElement> &elements, int failuresLimit) {
    const Solution &solution = sort(elements, failuresLimit);
    int groupSize = kRgbElements.size();
    int startPoint = (int) elements.size() % groupSize;
    const vector<RgbElement> &arrangedElements = solution.arrangedElements;
    int offset = countFirstRgbGroups(arrangedElements.cbegin() + startPoint, arrangedElements.cend()) * groupSize;
    vector<RgbElement> unsorted_elements(arrangedElements.begin() + offset, arrangedElements.end());
    Solution naiveSolution = NaiveSorting::sort(unsorted_elements);
    return AdvancedSort::mergedSolutions(solution, naiveSolution, offset);
}
