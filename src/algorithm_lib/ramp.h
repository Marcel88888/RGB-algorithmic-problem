#ifndef RGB_ALGORITHMIC_PROBLEM_RAMP_H
#define RGB_ALGORITHMIC_PROBLEM_RAMP_H

#include <vector>
#include <iostream>

using namespace std;


class Ramp {

private:
    vector<int> balls;
    const int groupSize = 3;

public:
    enum BallColors {
        R = 'R',
        G = 'G',
        B = 'B',
    };

    void moveThreeAtTheEnd(int start);

    void bruteForceSorting(int algorithm_iterations_limit);

    void printBalls();
};


#endif
