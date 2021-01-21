
#include "MatchingGroup.h"
#include "PrintingUtilities.h"

bool MatchingGroup::matches(std::vector<RgbElement>::const_iterator beg,
                            std::vector<RgbElement>::const_iterator end) const {
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
    os << '[';
    auto iter = group.elements.cbegin();
    while (iter < group.elements.cend() - 1) {
        const auto &opt = *iter;
        if (!opt.has_value()) {
            os << "Any, ";
        } else {
            os << (opt.value()) << ", ";
        }
        iter = next(iter);
    }
    const auto &lastOpt = *iter;
    if (lastOpt.has_value())
        os << iter->value() << "]";
    else
        os << "Any]";
    return os;
}

