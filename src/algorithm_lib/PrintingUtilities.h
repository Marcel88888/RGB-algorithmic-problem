#ifndef RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H
#define RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H


//#include <windows.h>
#include <functional>
#include <ostream>
#include "RgbAlgorithmUtilities.h"

std::ostream &operator<<(std::ostream &out, const std::vector<RgbElement> &v);

std::ostream &operator<<(std::ostream &os, const RgbElement &other);

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &v);

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v);

template<typename T>
std::ostream &printJoined(std::ostream &out,
                          typename std::vector<T>::const_iterator beg,
                          typename std::vector<T>::const_iterator end) {
    while (beg != end) {
        const T &prev = *beg++;
        out << prev;
        if (beg != end) {
            const T &next = *beg++;
            out << ", " << next;
            if (beg != end) {
                out << ", ";
            }
        }
    }
    return out;
}

#endif //RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H
