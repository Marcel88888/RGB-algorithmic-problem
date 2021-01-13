#ifndef RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
#define RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H

#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <iterator>
#include <ostream>
#include "randomUtilities.h"


enum RgbElement {
    R = 'R',
    G = 'G',
    B = 'B'
};

std::ostream &operator<<(std::ostream &os, const RgbElement &other);

const RgbElement RGB_ELEMENTS[3] = {R, G, B};

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    } else {
        out << "[]";
    }
    return out;
}

/// The structure that represents the solution for the rgb problem. It has a vector of arranged elements which
/// represents a sequence of rgb elements after moving all the groups of elements to the end of the sequence.
/// The groups of elements are positioned at indexes from the indexesOfRgbGroups vector.
struct Solution {
    Solution(std::vector<RgbElement> arrangedElements, std::vector<int> indexesOfRgbGroups) :
            arrangedElements(std::move(arrangedElements)),
            indexesOfRgbGroups(std::move(indexesOfRgbGroups)) {}

    explicit Solution(std::vector<RgbElement> arrangedElements) :
            arrangedElements(std::move(arrangedElements)) {}

    Solution() = default;

    std::vector<RgbElement> arrangedElements;
    std::vector<int> indexesOfRgbGroups;

    bool operator==(const Solution &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Solution &solution);
};

/// Move a sequence of 3 vector elements to the end of the vector. E.x. we get 1, 2, 3, 4, 5 -> 1, 5, 2, 3, 4 if we want to move a triple at index 1 to the end
/// \tparam T: type of vector elements
/// \param elements: vector elements of type T. elements size >= 3
/// \param triplePosition: an value from 0 to (elements.size() - 3 inclusively). This must be an index of the first element of a subsequence, containing 3 elements that will be moved to the end of the elements vector
/// \return the given elements
template<typename T>
std::vector<T> &moveTripleBack(std::vector<T> &elements, int triplePosition) {
    int colors_number = sizeof(RGB_ELEMENTS)/sizeof(RGB_ELEMENTS[0]);
    if (triplePosition < (int)elements.size() - colors_number) {
        std::rotate(elements.begin() + triplePosition, elements.begin() + triplePosition + 3, elements.end());
    }
    return elements;
}

/// Check if the elements are arranged in a proper sequence (rgb -> rgb -> ...).
/// \param elements: vector of RGB elements
/// \param maxRgbGroupsAmount: the maximum amount of groups of 3 rgb elements that can be found in the elements vector
/// \return true if the solution is correct
bool areElementsArrangedCorrectly(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount);

/// The maximum amount of groups of 3 rgb elements that can be found in the elements vector
/// \param elements: vector of RGB elements
/// \return int value from 0 to infinity
int maxRgbGroupsAmount(const std::vector<RgbElement> &elements);

int getElemReqPosition(RgbElement element);

#endif //RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
