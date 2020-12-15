#include <gtest/gtest.h>
#include "algorithm_lib/rgbAlgorithmUtilites.h"
#include <string>
#include <utility>

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
    std::generate(v1.begin(), v1.end(), linkedRandomElementsGenerator(1));
    std::vector<char> v2(20, v1[0]);
    ASSERT_EQ(v1, v2);
}

TEST(Random, ElementsAreDifferentUsingLinkedRandomizer) {
    std::vector<char> v1(30);
    std::generate(v1.begin(), v1.end(), linkedRandomElementsGenerator(0.3));
    std::vector<char> v2(30, v1[0]);
    ASSERT_NE(v1, v2);
}

template<typename T>
struct TmpStruct {
    TmpStruct(std::vector<T> inputVector, std::vector<T> expectedVector, int position) :
            inputVector(std::move(inputVector)), expectedVector(std::move(expectedVector)), position(position) {}

    std::vector<T> inputVector;
    std::vector<T> expectedVector;
    int position;
};


template<typename T>
std::string vecAsString(const std::vector<T> &vector) {
    std::ostringstream oss;
    if (!vector.empty()) {
        std::copy(vector.begin(), vector.end() - 1, std::ostream_iterator<int>(oss, ", "));
        oss << vector.back();
    }
    return oss.str();
}

TEST(MoveTripleBack, TriplesAreMovedCorrectly) {
    std::vector<TmpStruct<int>> testVector{
            TmpStruct<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 5, 6, 7, 8, 9, 2, 3, 4}, 1),
            TmpStruct<int>({1, 2, 3}, {1, 2, 3}, 0),
            TmpStruct<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {4, 5, 6, 7, 8, 9, 1, 2, 3}, 0),
            TmpStruct<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 8, 9, 5, 6, 7}, 4),
            TmpStruct<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 6),
            TmpStruct<int>({1, 2, 3, 4, 5}, {1, 5, 2, 3, 4}, 1)
    };
    for (const auto &nextStruct : testVector) {
        std::vector<int> inputVector = nextStruct.inputVector;
        EXPECT_EQ(nextStruct.expectedVector,
                  moveTripleBack(inputVector, nextStruct.position))
                            << "Input vector: " << vecAsString(nextStruct.inputVector)
                            << "\nPosition: " << nextStruct.position;
    }
}