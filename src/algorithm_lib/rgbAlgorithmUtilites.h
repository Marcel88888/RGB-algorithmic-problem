#ifndef RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
#define RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <functional>


const char RGB_ELEMENTS[3] = {'R', 'G', 'B'};

/// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
/// \param from: minimal value that can be returned
/// \param to: maximal value that can be returned
/// \return an integer value from the uniform distribution
int randomUniformInteger(int from, int to);

/// \param from: minimal value that can be returned
/// \param to: maximal value that can be returned
/// \return a float value from the uniform distribution
double uniformRealDistribution(double from, double to);

/// \param probabilityOfChoosingPreviousElement: if a random value from the range [0; 1] will be less or equal
/// than the given parameter then it will be returned the previously generated element.
/// \return a lambda that returns random RGB elements or previously generated values.
std::function<char()> linkedRandomElementsGenerator(float probabilityOfChoosingPreviousElement);

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

#endif //RGB_ALGORITHMIC_PROBLEM_RGBALGORITHMUTILITES_H
