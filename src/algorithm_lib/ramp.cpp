#include "ramp.h"
#include <vector>

using namespace std;

void Ramp::moveThreeAtTheEnd(int start) {
    vector<char> ballsToMove(groupSize);
    for (int i = 0; i < groupSize; i++) {
        ballsToMove[i] = balls[i + start];
    }
    for (int i = start; i < balls.size() - groupSize; i++) {
        balls[i] = balls[i + groupSize];
    }
    for (int i = 0; i < groupSize; i++) {
        balls[balls.size() - groupSize + i] = ballsToMove[i];
    }
}

void Ramp::bruteForceSorting(int algorithm_iterations_limit) {
    vector<char> colors{BallColors::R, BallColors::G, BallColors::B};
    int a, b;
    for (int i = 0; i < balls.size() - groupSize; i++) {
        a = 0;
        b = 0;
        while (balls[i] != colors[i % groupSize] && b < algorithm_iterations_limit) {
            if (a >= (balls.size() - i) / (groupSize * 2)) { //TODO sprawdzic jak czesto musi robic te podmiany
                moveThreeAtTheEnd(i + 1);
                a = 0;
            } else {
                moveThreeAtTheEnd(i);
                ++a;
            }
            printBalls();
            ++b;
        }
    }
}

void Ramp::printBalls() {
    for (int i = 0; i < balls.size(); i++) {
        if (i % groupSize == 0) {
            cout << endl;
        }
        cout << (char) balls[i] << " ";
    }
    cout << endl;
}

