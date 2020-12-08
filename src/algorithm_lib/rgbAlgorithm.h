#ifndef RGB_ALGORITHMIC_PROBLEM_RGBALGORITHM_H
#define RGB_ALGORITHMIC_PROBLEM_RGBALGORITHM_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <functional>


const char RGB_ELEMENTS[3] = {'R', 'G', 'B'};

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


#endif //RGB_ALGORITHMIC_PROBLEM_RGBALGORITHM_H
