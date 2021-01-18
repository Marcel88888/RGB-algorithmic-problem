
#include "MatchingGroup.h"

bool MatchingGroup::matches(std::vector<RgbElement>::const_iterator beg, std::vector<RgbElement>::const_iterator end) {
    for (const auto &element : elements) {
        if (beg != end) {
            const auto &cur = *beg;
            if (element != AnyElement && element.value() != cur) {
                return false;
            }
            beg = next(beg);
        } else {
            return false;
        }
    }
    return true;
}

bool MatchingGroup::operator==(const MatchingGroup &rhs) const {
    return elements == rhs.elements;
}

bool MatchingGroup::operator!=(const MatchingGroup &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const MatchingGroup &group) {
    os << "[";
    for (const auto &element : group.elements) {
        if (!element.has_value()) {
            os << "Any, ";
        } else {
            os << element.value() << ", ";
        }
    }
    os << "\b\b]";
    return os;
}

