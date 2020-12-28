#ifndef RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
#define RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <functional>
#include <iterator>
#include <ostream>

enum RgbElement {
    R = 'R',
    G = 'G',
    B = 'B',
};

const char RGB_ELEMENTS[3] = {R, G, B};

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}


/// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
/// \param from: minimum value that can be returned
/// \param to: maximum value that can be returned
/// \return an integer value from the uniform distribution
int randomUniformInteger(int from, int to);

/// \param from: minimum value that can be returned
/// \param to: maximum value that can be returned
/// \return a float value from the uniform distribution
double uniformRealDistribution(double from, double to);

/// \param from: minimum value that can be returned
/// \param to: maximum value that can be returned
/// \param probabilityOfChoosingPreviousElement: if a random value from the range [0; 1] will be less or equal
/// than the given parameter then it will be returned the previously generated element.
/// \return a random lambda that returns integer from the range [from, to]
std::function<int()> linkedRandomIndicesGenerator(float probabilityOfChoosingPreviousElement, int from, int to);

struct Solution {
    Solution(std::vector<RgbElement> arrangedElements, std::vector<int> indexesOfRgbGroups, int rgbGroupsAmount) :
            arrangedElements(std::move(arrangedElements)),
            indexesOfRgbGroups(std::move(indexesOfRgbGroups)),
            rgbGroupsAmount(rgbGroupsAmount) {}

    Solution() = default;

    std::vector<RgbElement> arrangedElements;
    std::vector<int> indexesOfRgbGroups;
    int rgbGroupsAmount = 0;

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
    std::rotate(elements.begin() + triplePosition, elements.begin() + triplePosition + 3, elements.end());
    return elements;
}

/// Check if the elements are arranged in a proper sequence (rgb -> rgb -> ...).
/// \param elements: vector of RGB elements
/// \param maxRgbGroupsAmount: the maximum amount of groups of 3 rgb elements that can be found in the elements vector
/// \return true if the solution is correct
bool isCorrectSolution(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount);

#endif //RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
