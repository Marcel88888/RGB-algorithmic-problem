#include <gtest/gtest.h>
#include "algorithm_lib/rgbAlgorithmUtilites.h"

template<typename T>
struct TmpStruct {
    TmpStruct(std::vector<T> inputVector, std::vector<T> expectedVector, int position) :
            inputVector(std::move(inputVector)), expectedVector(std::move(expectedVector)), position(position) {}

    std::vector<T> inputVector;
    std::vector<T> expectedVector;
    int position;
};


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
                            << "Input vector: " << nextStruct.inputVector
                            << "\nPosition: " << nextStruct.position;
    }
}