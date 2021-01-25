#ifndef RGB_ALGORITHMIC_PROBLEM_RANDOMUTILITIES_H
#define RGB_ALGORITHMIC_PROBLEM_RANDOMUTILITIES_H

#include <functional>
#include <chrono>
#include <random>

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
std::function<int()> linkedRandomIntegersGenerator(double probabilityOfChoosingPreviousElement, int from, int to);


#endif //RGB_ALGORITHMIC_PROBLEM_RANDOMUTILITIES_H
