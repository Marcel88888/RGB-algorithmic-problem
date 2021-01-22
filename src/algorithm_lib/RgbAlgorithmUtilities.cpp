#include "RgbAlgorithmUtilities.h"

bool areElementsArrangedCorrectly(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    int i = 0;
    const int groupSize = kRgbElements.size();
    int numberOfElementsToCheck = maxRgbGroupsAmount * groupSize;
    for (const auto &elem : elements) {
        if (i >= numberOfElementsToCheck) { break; }
        if (elem != kRgbElements[i % groupSize]) { return false; }
        i++;
    }
    return true;
}

bool Solution::operator==(const Solution &rhs) const {
    return arrangedElements == rhs.arrangedElements &&
           indexesOfMovedGroups == rhs.indexesOfMovedGroups;
}


int maxRgbGroupsAmount(const std::vector<RgbElement> &elements) {
    int rCount = 0;
    int gCount = 0;
    int bCount = 0;
    for (const auto &elem : elements) {
        if (elem == R) rCount++;
        else if (elem == G) gCount++;
        else if (elem == B) bCount++;
    }
    return std::min({rCount, gCount, bCount});
}

int getElemReqPosition(RgbElement element) {
    if (element == R) return 0;
    if (element == G) return 1;
    return 2;
}

bool isRgbTriple(std::vector<RgbElement>::const_iterator iterator) {
    for (const auto &elem : kRgbElements) {
        if (elem != *(iterator))
            return false;
        iterator = next(iterator);
    }
    return true;
}
