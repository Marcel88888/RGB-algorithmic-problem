#include "PrintingUtilities.h"

std::ostream &operator<<(std::ostream &out, const std::vector<RgbElement> &v) {
    if (!v.empty()) {
        out << '[';
        auto iter = v.cbegin();
        while (iter < v.cend() - 1) {
            out << *iter++ << ", ";
        }
        out << *iter << ']';
    } else {
        out << "[]";
    }
    return out;
}

std::ostream &operator<<(std::ostream &os, const RgbElement &other) {
    os << (char) other;
    return os;
}