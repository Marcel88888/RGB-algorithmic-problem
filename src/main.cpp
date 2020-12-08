#include <iostream>
#include "algorithm_lib/rgbAlgorithm.h"

int main() {
    const int elementsNumber = 10;
    std::vector<char> elements(elementsNumber);
    std::generate(elements.begin(),
                  elements.end(),
                  linkedRandomElementsGenerator(0.5));
    for (const char &elem : elements) {
        std::cout << elem;
    }
    return 0;
}
