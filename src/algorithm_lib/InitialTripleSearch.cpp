#include "InitialTripleSearch.h"
#include "RgbAlgorithmUtilities.h"
#include <algorithm>

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
 *
 */
tuple<vector<RgbElement>, vector<int>> sortingStep(const vector<RgbElement> &elements, int startingPoint, int groupSize) {
    vector<RgbElement> elementsCopy(elements);
    vector<int> indexesOfMovedGroups;
    int i = startingPoint;
    int sortedGroupsNumber = 0;

    // phase 1
    while (i < elementsCopy.size() - groupSize * sortedGroupsNumber - groupSize) {
        if (i >= 0 && isRgbTriple(elementsCopy.cbegin() + i)) {
            moveTripleBack(elementsCopy, i);
            indexesOfMovedGroups.push_back(i);
            sortedGroupsNumber++;
            // after moving a triple back there can appear a new rgb group out of the elements at the positions
            // i - 1 and i - 2 and i + 3 so check if this group can also be moved back
            i -= 2;
        } else { ++i; }
    }

    // phase 2
    int unsorted_balls = (int) elementsCopy.size() - sortedGroupsNumber * groupSize -
            countFirstRgbGroups(elementsCopy.cbegin(), elementsCopy.cend()) * groupSize;
    int required_moves = unsorted_balls / groupSize;
    for (int j = 0; j < required_moves; ++j) {
        RgbElement last_value = elementsCopy.back();
        int next_req_val = (getElemReqPosition(last_value) + 1) % groupSize;
        int best_move_pos1 = -1; // with values [X,?,?]
        bool double_found = false;  // for values [X1,X2,?]
        bool triple_found = false; // for values [X1,X2,X3]
        for (int k = startingPoint;
             k < startingPoint + unsorted_balls - 2; ++k) {  // "unsorted_balls - 2" because in the loop I may move a triple
            // starting at k position and ending at k+2 position.
            if (elementsCopy[k] == kRgbElements[next_req_val]) {
                best_move_pos1 = k;
                if (elementsCopy[k + 1] == kRgbElements[(next_req_val + 1) % groupSize] &&
                    elementsCopy[k + 2] == kRgbElements[(next_req_val + 2) % groupSize]) {
                    moveTripleBack(elementsCopy, k);
                    indexesOfMovedGroups.push_back(k);
                    unsorted_balls -= groupSize;
                    triple_found = true;
                    break;
                } else if (elementsCopy[k + 1] == kRgbElements[(next_req_val + 1) % groupSize]) {
                    moveTripleBack(elementsCopy, k);
                    indexesOfMovedGroups.push_back(k);
                    unsorted_balls -= groupSize;
                    double_found = true;
                    break;
                }
            }
        }
        if (!triple_found && !double_found && best_move_pos1 != -1) {
            moveTripleBack(elementsCopy, best_move_pos1);
            indexesOfMovedGroups.push_back(best_move_pos1);
            unsorted_balls -= groupSize;
        } else if (!triple_found && !double_found) {
            moveTripleBack(elementsCopy, startingPoint);
            indexesOfMovedGroups.push_back(startingPoint);
            unsorted_balls -= groupSize;
        }
    }
    return make_tuple(elementsCopy, indexesOfMovedGroups);
}


Solution InitialTripleSearch::sort(const vector<RgbElement> &elements, int failuresLimit) {
    vector<RgbElement> elementsCopy(elements);
    vector<int> indexesOfMovedGroups;
    int groupSize = kRgbElements.size();
    int startPoint = (int) elementsCopy.size() % groupSize;
    int rgbGroupsAmount1, rgbGroupsAmount2;
    int failures = 0;
    while (failures < failuresLimit) {
        rgbGroupsAmount1 = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
        rgbGroupsAmount2 = rgbGroupsAmount1;

        tuple <vector<RgbElement>, vector<int>> sorting_step_results = sortingStep(
                elementsCopy,
                ((int) elementsCopy.size() % groupSize) + rgbGroupsAmount1 * groupSize,
                groupSize);
        elementsCopy = get<0>(sorting_step_results);
        indexesOfMovedGroups.insert(indexesOfMovedGroups.end(),
                                    get<1>(sorting_step_results).begin(),
                                    get<1>(sorting_step_results).end() );

        rgbGroupsAmount1 = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
        if (rgbGroupsAmount1 == rgbGroupsAmount2) {
            failures++;
        }
        else {
            failures = 0;
        }
    }

    // sorting the unsorted part of the vector using NaiveSorting
    auto unsorted_beg = elementsCopy.begin() +
            countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend()) * groupSize;
    auto unsorted_end = elementsCopy.end();
    vector<RgbElement> unsorted_elements(unsorted_beg, unsorted_end);
    int max = maxRgbGroupsAmount(unsorted_elements);
    vector<RgbElement> sorted_part = NaiveSorting::sort(unsorted_elements, max).arrangedElements;
    copy(sorted_part.begin(), sorted_part.end(), unsorted_beg);
    return Solution(elementsCopy, indexesOfMovedGroups);
}
