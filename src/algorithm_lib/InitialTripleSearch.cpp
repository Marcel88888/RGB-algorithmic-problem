#include "InitialTripleSearch.h"
#include "RgbAlgorithmUtilities.h"

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


vector<RgbElement> sortingStep(const vector<RgbElement> &elements, int startingPoint, int groupSize) {
    vector<RgbElement> elementsCopy(elements);
    int i = startingPoint;
    int sortedGroupsNumber = 0;

    // phase 1
    while (i < elementsCopy.size() - groupSize * sortedGroupsNumber - groupSize) {
        if (i >= 0 && isRgbTriple(elementsCopy.cbegin() + i)) {
            moveTripleBack(elementsCopy, i);
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
             k < unsorted_balls - 2; ++k) {  // "unsorted_balls - 2" because in the loop I may move a triple
            // starting at k position and ending at k+2 position.
            if (elementsCopy[k] == kRgbElements[next_req_val]) {
                best_move_pos1 = k;
                if (elementsCopy[k + 1] == kRgbElements[(next_req_val + 1) % groupSize] &&
                    elementsCopy[k + 2] == kRgbElements[(next_req_val + 2) % groupSize]) {
                    moveTripleBack(elementsCopy, k);
                    unsorted_balls -= groupSize;
                    triple_found = true;
                    break;
                } else if (elementsCopy[k + 1] == kRgbElements[(next_req_val + 1) % groupSize]) {
                    moveTripleBack(elementsCopy, k);
                    unsorted_balls -= groupSize;
                    double_found = true;
                    break;
                }
            }
        }
        if (!triple_found && !double_found && best_move_pos1 != -1) {
            moveTripleBack(elementsCopy, best_move_pos1);
            unsorted_balls -= groupSize;
        } else if (!triple_found && !double_found) {
            moveTripleBack(elementsCopy, startingPoint);
            unsorted_balls -= groupSize;
        }
    }
    return elementsCopy;
}


Solution InitialTripleSearch::sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    vector<RgbElement> elementsCopy(elements);
    int groupSize = kRgbElements.size();
    int startPoint = (int) elementsCopy.size() % groupSize;
    int rgbGroupsAmount = 0;
    while (rgbGroupsAmount < maxRgbGroupsAmount - 2) {
        rgbGroupsAmount = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
        cout << "Sorted groups number: " << rgbGroupsAmount << std::endl;

        elementsCopy = sortingStep(
                elementsCopy,
                ((int) elementsCopy.size() % groupSize) + rgbGroupsAmount * groupSize,
                groupSize);
        cout << "Elements: " << elementsCopy << endl;

        rgbGroupsAmount = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
    }
//    int i = 0;
//    while (i < 10) {
//        rgbGroupsAmount = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
//        cout << "Sorted groups number: " << rgbGroupsAmount << std::endl;
//
//        elementsCopy = sortingStep(
//                elementsCopy,
//                ((int) elementsCopy.size() % groupSize) + rgbGroupsAmount * groupSize,
//                groupSize);
//        cout << "Elements: " << elementsCopy << endl;
//
//        rgbGroupsAmount = countFirstRgbGroups(elementsCopy.cbegin() + startPoint, elementsCopy.cend());
//        ++i;
//    }

    cout << "Sorted groups number: " << rgbGroupsAmount << std::endl;
    return Solution(elementsCopy);
}
