#include <iostream>
#include <sstream>
#include "algorithm_lib/rgbAlgorithmUtilites.h"
#include "algorithm_lib/breadthSearch.h"
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




    const int kElementsNumber = 1000;
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
    cout << "Correctly: " << correct << std::endl << std::endl;




    const int kElementsNumber2 = 1001;
    std::vector<RgbElement> elements2(kElementsNumber2);

    std::generate(elements2.begin(), elements2.end(),[] {
        return RGB_ELEMENTS[randomUniformInteger(0, 2)];
    });

    std::cout << elements2 << std::endl;
    int r2 = 0, g2 = 0, b2 = 0;
    for (auto & element : elements2) {
        if(element == RgbElement::R) r2++;
        else if(element == RgbElement::G) g2++;
        else b2++;
    }
    std::cout << "R: " << r2 << std::endl << "G: " << g2 << std::endl << "B: " << b2 << std::endl;

    int max2 = maxRgbGroupsAmount(elements2);

    cout << "max: " << max2 << std::endl;

    Solution s2 = NaiveSorting::sort(elements2, max2);
    std::cout << s2 << std::endl;

    bool correct2 = areElementsArrangedCorrectly(s2.arrangedElements, max2);
    cout << "Correctly: " << correct2 << std::endl << std::endl;




    const int kElementsNumber3 = 1002;
    std::vector<RgbElement> elements3(kElementsNumber3);

    std::generate(elements3.begin(), elements3.end(),[] {
        return RGB_ELEMENTS[randomUniformInteger(0, 2)];
    });

    std::cout << elements3 << std::endl;
    int r3 = 0, g3 = 0, b3 = 0;
    for (auto & element : elements3) {
        if(element == RgbElement::R) r3++;
        else if(element == RgbElement::G) g3++;
        else b3++;
    }
    std::cout << "R: " << r3 << std::endl << "G: " << g3 << std::endl << "B: " << b3 << std::endl;

    int max3 = maxRgbGroupsAmount(elements3);

    cout << "max: " << max3 << std::endl;

    Solution s3 = NaiveSorting::sort(elements3, max3);
    std::cout << s3 << std::endl;

    bool correct3 = areElementsArrangedCorrectly(s3.arrangedElements, max3);
    cout << "Correctly: " << correct3 << std::endl << std::endl;

    return 0;
}