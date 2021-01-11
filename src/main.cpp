#include <iostream>
#include <sstream>
#include "algorithm_lib/rgbAlgorithmUtilites.h"
#include "algorithm_lib/breadthSearch.h"
#include "algorithm_lib/bruteForceSorting.h"
#include "algorithm_lib/naiveSorting.h"


int main() {
//    const int kElementsNumber = 10;
//    std::vector<RgbElement> elements(kElementsNumber);
//
//    const auto generator = linkedRandomIntegersGenerator(0.2, 0, 2);
//    std::generate(elements.begin(), elements.end(), [&generator] {
//        return RGB_ELEMENTS[generator()];
//    });
//
//    std::cout << elements << std::endl;
//
//    Solution s = BreadthSearchAlgorithm::solution(elements);
//    auto depth = !s.indexesOfRgbGroups.empty() ? s.indexesOfRgbGroups.size() - 1 : 0;
//
//    std::cout << s << "\nDepth: " << depth << std::endl;
//
//    return 0;




    const int kElementsNumber = 102;
    std::vector<RgbElement> elements(kElementsNumber);

    std::generate(elements.begin(), elements.end(),[] {
        return RGB_ELEMENTS[randomUniformInteger(0, 2)];
    });

    std::cout << elements << std::endl;
    int r = 0, g = 0, b = 0;
    for (auto & element : elements) {
        if(element == RgbElement::R) r++;
        else if(element == RgbElement::G) g++;
        else b++;
    }
    std::cout << "R: " << r << std::endl << "G: " << g << std::endl << "B: " << b << std::endl;

    int max = maxRgbGroupsAmount(elements);

    cout << "max: " << max << std::endl;

    Solution s = NaiveSorting::sort(elements, max);
    std::cout << s << std::endl;

    bool correct = areElementsArrangedCorrectly(s.arrangedElements, max);
    cout << "Correctly: " << correct << std::endl;

//    const int kElementsNumber = 10;
//    std::vector<RgbElement> elements(kElementsNumber);
//    std::generate(elements.begin(), elements.end(),[] {
//        return RGB_ELEMENTS[randomUniformInteger(0, 2)];
//    });
//
//    std::cout << elements << std::endl;
//    moveTripleBack(elements, kElementsNumber-1);
//    std::cout << elements << std::endl;
//    moveTripleBack(elements, kElementsNumber-2);
//    std::cout << elements << std::endl;
//    moveTripleBack(elements, kElementsNumber-3);
//    std::cout << elements << std::endl << std::endl;
//
//    moveTripleBack(elements, kElementsNumber-4);
//    std::cout << elements << std::endl;
    return 0;
}