#ifndef RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
#define RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H

#include <vector>
#include <iostream>
#include "RgbAlgorithmUtilities.h"
#include <tuple>

class NaiveSorting {

public:
    static Solution sort(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount);
};

#endif //RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
