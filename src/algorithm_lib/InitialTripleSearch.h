#ifndef RGB_ALGORITHMIC_PROBLEM_INITIALTRIPLESEARCH_H
#define RGB_ALGORITHMIC_PROBLEM_INITIALTRIPLESEARCH_H

#include <vector>
#include <iostream>
#include "RgbAlgorithmUtilities.h"
#include "NaiveSorting.h"
#include <algorithm>


class InitialTripleSearch {

public:
    static Solution sort(const std::vector<RgbElement> &elements, int failuresLimit);

};


#endif //RGB_ALGORITHMIC_PROBLEM_INITIALTRIPLESEARCH_H
