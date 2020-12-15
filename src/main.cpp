#include <iostream>
#include "algorithm_lib/rgbAlgorithmUtilites.h"

template<typename T>
void printVector(std::vector<T> &vector) {
    for (const auto &elem : vector) {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;
}

int main() {
    const int elementsNumber = 9;
    std::vector<int> elements(elementsNumber);
    int count = 1;
    std::generate(elements.begin(), elements.end(), [&count] { return count++; });
    printVector(elements);
    moveTripleBack(elements, 1);
    printVector(elements);

    return 0;
}
