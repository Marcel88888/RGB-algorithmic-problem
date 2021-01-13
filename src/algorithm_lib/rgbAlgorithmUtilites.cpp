#include "rgbAlgorithmUtilites.h"

bool areElementsArrangedCorrectly(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    int i = 0;
    int numberOfElementsToCheck = maxRgbGroupsAmount * 3;
    for (const auto &elem : elements) {
        if (i >= numberOfElementsToCheck) { break; }
        if (elem != RGB_ELEMENTS[i % 3]) { return false; }
        i++;
    }
    return true;
}

bool Solution::operator==(const Solution &rhs) const {
    return arrangedElements == rhs.arrangedElements &&
           indexesOfRgbGroups == rhs.indexesOfRgbGroups;
}

std::ostream &operator<<(std::ostream &os, const Solution &solution) {
    os << "Elements: " << solution.arrangedElements << ", indexes: " << solution.indexesOfRgbGroups;
    return os;
}

std::ostream &operator<<(std::ostream &os, const RgbElement &other) {
    os << (char) other;
    return os;
}

int maxRgbGroupsAmount(const std::vector<RgbElement> &elements) {
    int rCount = 0;
    int gCount = 0;
    int bCount = 0;
    for (const auto &elem : elements) {
        if (elem == 'R') rCount++;
        else if (elem == 'G') gCount++;
        else if (elem == 'B') bCount++;
    }
    return std::min({rCount, gCount, bCount});
}

int getElemReqPosition(RgbElement element) {
    switch (element) {
        case RgbElement::R:
            return 0;
        case RgbElement::G:
            return 1;
        case RgbElement::B:
            return 2;
    }
}

