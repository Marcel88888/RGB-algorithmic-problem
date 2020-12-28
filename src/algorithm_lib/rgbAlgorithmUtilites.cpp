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

std::function<int()> linkedRandomIndicesGenerator(float probabilityOfChoosingPreviousElement, int from, int to) {
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

bool isCorrectSolution(const std::vector<RgbElement> &elements, const int maxRgbGroupsAmount) {
    int i = 0;
    int numberOfElementsToCheck = maxRgbGroupsAmount * 3;
    for (const auto &elem : elements) {
        if (i >= numberOfElementsToCheck) { break; }
        if (elem != RGB_ELEMENTS[i % 3]) { return false; }
        i++;
    }
    return true;
}

bool Solution::operator==(const Solution &rhs) const {
    return arrangedElements == rhs.arrangedElements &&
           indexesOfRgbGroups == rhs.indexesOfRgbGroups &&
           rgbGroupsAmount == rhs.rgbGroupsAmount;
}

std::ostream &operator<<(std::ostream &os, const Solution &solution) {
    os << "Elements: " << solution.arrangedElements << ", indexes: " << solution.indexesOfRgbGroups
       << ", RGB groups amount: " << solution.rgbGroupsAmount;
    return os;
}
