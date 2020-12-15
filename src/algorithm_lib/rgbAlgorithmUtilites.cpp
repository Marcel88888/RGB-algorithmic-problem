#include "rgbAlgorithmUtilites.h"

int randomUniformInteger(int from, int to) {
    // TODO(@pochka15): think about the better seed
    static auto seed = static_cast<long unsigned int>(time(0));
    std::mt19937 gen(seed++); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(from, to);
    return distrib(gen);
}


double uniformRealDistribution(double from, double to) {
    // TODO(@pochka15): think about the better seed
    static auto seed = static_cast<long unsigned int>(time(0));
    std::default_random_engine eng{seed++};
    std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(from, to);
    return distribution(eng);
}

std::function<char()> linkedRandomElementsGenerator(float probabilityOfChoosingPreviousElement) {
    std::shared_ptr<char> previousElement_p = std::make_shared<char>();
    *previousElement_p = ' ';
    return [previousElement_p, probabilityOfChoosingPreviousElement]() {
        char currentElement;
        if (*previousElement_p == ' ') {
            currentElement = RGB_ELEMENTS[randomUniformInteger(0, 2)];
        } else {
            const bool shouldTakePrevious =
                    uniformRealDistribution(0, 1) <= probabilityOfChoosingPreviousElement;
            currentElement = shouldTakePrevious ?
                             *previousElement_p :
                             RGB_ELEMENTS[randomUniformInteger(0, 2)];
        }
        *previousElement_p = currentElement;
        return currentElement;
    };
}