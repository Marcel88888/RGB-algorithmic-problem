#ifndef RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
#define RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H

#include <vector>
#include <iostream>
#include "RgbAlgorithmUtilities.h"

using namespace std;

class NaiveSorting {

public:
    static Solution sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount);
};

#endif //RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
