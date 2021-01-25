#include "RandomUtilities.h"

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

std::function<int()> linkedRandomIntegersGenerator(double probabilityOfChoosingPreviousElement, int from, int to) {
    return [=, prevElem = -1]() mutable {
        int currentElement;
        if (prevElem == -1) {
            currentElement = randomUniformInteger(from, to);
        } else {
            const bool shouldTakePrevious =
                    uniformRealDistribution(0, 1) <= probabilityOfChoosingPreviousElement;
            currentElement = shouldTakePrevious ? prevElem : randomUniformInteger(from, to);
        }
        prevElem = currentElement;
        return currentElement;
    };
}
