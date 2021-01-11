#ifndef RGB_ALGORITHMIC_PROBLEM_RAMP_H
#define RGB_ALGORITHMIC_PROBLEM_RAMP_H

#include <vector>
#include <iostream>
#include "rgbAlgorithmUtilites.h"

using namespace std;

class BruteForceSorting {

public:
    static Solution sort(const vector<RgbElement> &elements, int algorithmIterationsLimit);
};

#endif
