
#ifndef RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H
#define RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H


#include <windows.h>
#include <functional>
#include <ostream>
#include "RgbAlgorithmUtilities.h"

std::ostream &operator<<(std::ostream &out, const std::vector<RgbElement> &v);

std::ostream &operator<<(std::ostream &os, const RgbElement &other);

#endif //RGB_ALGORITHMIC_PROBLEM_PRINTINGUTILITIES_H
