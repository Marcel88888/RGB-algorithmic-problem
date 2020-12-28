#include <iostream>
#include <sstream>
#include "algorithm_lib/rgbAlgorithmUtilites.h"
#include "algorithm_lib/breadthSearch.h"


int main() {
    const int kElementsNumber = 10;
    std::vector<RgbElement> elements(kElementsNumber);

    const auto generator = linkedRandomIntegersGenerator(0.2, 0, 2);
    std::generate(elements.begin(), elements.end(), [&generator] {
        return RGB_ELEMENTS[generator()];
    });

    std::cout << elements << std::endl;

    Solution s = BreadthSearchAlgorithm::solution(elements);
    auto depth = !s.indexesOfRgbGroups.empty() ? s.indexesOfRgbGroups.size() - 1 : 0;

    std::cout << s << "\nDepth: " << depth << std::endl;

    return 0;
}