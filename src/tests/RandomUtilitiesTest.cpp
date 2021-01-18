#include <gtest/gtest.h>
#include "algorithm_lib/RgbAlgorithmUtilities.h"


TEST(Random, RandomIntegersAreDifferent) {
    auto randInt = [] { return randomUniformInteger(0, 5); };
    std::vector<int> v1(10);
    std::generate(v1.begin(), v1.end(), randInt);
    std::vector<int> v2(10, v1[0]);
    ASSERT_NE(v1, v2);
}

TEST(Random, RandomDoublesAreDifferent) {
    auto randDouble = [] { return uniformRealDistribution(0, 1); };
    std::vector<double> v1(10);
    std::generate(v1.begin(), v1.end(), randDouble);
    std::vector<double> v2(10, v1[0]);
    ASSERT_NE(v1, v2);
}


TEST(Random, ElementsAreEqualUsingLinkedRandomizer) {
    std::vector<char> v1(20);
    auto gen = linkedRandomIntegersGenerator(1, 0, 2);
    std::generate(v1.begin(), v1.end(), [&gen] { return kRgbElements[gen()]; });
    std::vector<char> v2(20, v1[0]);
    ASSERT_EQ(v1, v2);
}

TEST(Random, ElementsAreDifferentUsingLinkedRandomizer) {
    std::vector<char> v1(30);
    auto gen = linkedRandomIntegersGenerator(0.3, 0, 2);
    std::generate(v1.begin(), v1.end(), [&gen] { return kRgbElements[gen()]; });
    std::vector<char> v2(30, v1[0]);
    ASSERT_NE(v1, v2);
}
