#include <iostream>
#include <sstream>
#include "algorithm_lib/rgbAlgorithmUtilites.h"
#include "algorithm_lib/breadthSearch.h"


void tmp();

int main() {
    const int kElementsNumber = 10;
    std::vector<RgbElement> elements(kElementsNumber);
    std::generate(elements.begin(),
                  elements.end(),
                  [] { return RGB_ELEMENTS[randomUniformInteger(0, 2)]; });

    std::cout << elements << std::endl;

    Solution s = solution(elements);
    auto depth = !s.indexesOfRgbGroups.empty() ? s.indexesOfRgbGroups.size() - 1 : 0;

    std::cout << s << "\nDepth: " << depth << std::endl;

    return 0;
}