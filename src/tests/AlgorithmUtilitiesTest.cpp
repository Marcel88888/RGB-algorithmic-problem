#include <gtest/gtest.h>
#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/PrintingUtilities.h"

template<typename T>
struct TestData {
    TestData(std::vector<T> inputVector, std::vector<T> expectedVector, int position) :
            inputVector(std::move(inputVector)), expectedVector(std::move(expectedVector)), position(position) {}

    std::vector<T> inputVector;
    std::vector<T> expectedVector;
    int position;
};


TEST(MoveTripleBack, TriplesAreMovedCorrectly) {
    std::vector<TestData<int>> testVector{
            TestData<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 5, 6, 7, 8, 9, 2, 3, 4}, 1),
            TestData<int>({1, 2, 3}, {1, 2, 3}, 0),
            TestData<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {4, 5, 6, 7, 8, 9, 1, 2, 3}, 0),
            TestData<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 8, 9, 5, 6, 7}, 4),
            TestData<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 6),
            TestData<int>({1, 2, 3, 4, 5}, {1, 5, 2, 3, 4}, 1)
    };
    for (const auto &nextStruct : testVector) {
        std::vector<int> inputVector = nextStruct.inputVector;
        EXPECT_EQ(nextStruct.expectedVector,
                  moveTripleBack(inputVector, nextStruct.position))
                            << "Input vector: " << nextStruct.inputVector
                            << "\nPosition: " << nextStruct.position;
    }
}