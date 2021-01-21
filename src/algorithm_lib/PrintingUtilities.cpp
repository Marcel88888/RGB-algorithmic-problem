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

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &v) {
    printJoined<std::string>(os, v.cbegin(), v.cend());
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
    printJoined<int>(os, v.cbegin(), v.cend());
    return os;
}
