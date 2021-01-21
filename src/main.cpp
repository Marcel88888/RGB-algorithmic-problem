#include <iostream>
#include <sstream>
#include "algorithm_lib/AdvancedSearch.h"
#include "algorithm_lib/WindowsPrintingUtilities.h"


int main() {
    std::vector<RgbElement> elements(21);

//      Use of the uniform distribution
    std::generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });
    std::cout << maxRgbGroupsAmount(elements) << std::endl;
    const Solution &s = AdvancedSearch::solution(elements);
    for (int ind : s.indexesOfMovedGroups) {
        printWithHighlightedGroup(std::cout, elements, ind, Color::WHITE_ON_BLACK)
                << std::endl;
        moveTripleBack(elements, ind);
        printWithHighlightedGroup(
                std::cout,
                elements,
                (int) elements.size() - 3, Color::BLUE)
                << std::endl;
    }
    std::cout << s.arrangedElements << std::endl;
    return 0;
}