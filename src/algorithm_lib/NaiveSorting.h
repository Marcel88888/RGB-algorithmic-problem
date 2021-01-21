#ifndef RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
#define RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H

#include <vector>
#include <iostream>
#include "RgbAlgorithmUtilities.h"

class NaiveSorting {

public:
    static Solution sort(const std::vector<RgbElement> &elements, int maxRgbGroupsAmount);

    static std::tuple<std::vector<RgbElement>, std::vector<int>>
    moveExpValToTheBeg(int requiredMoves, std::vector<RgbElement>
    elementsCopy, int moveIndex);
};

#endif //RGB_ALGORITHMIC_PROBLEM_NAIVESORTING_H
