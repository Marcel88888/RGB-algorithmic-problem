#include "naiveSorting.h"

using namespace std;


int findExpValTriplePosition(int prevPosition, vector<RgbElement> elementsCopy, RgbElement expectedValue,
                              int displacement) {
    for(int j = prevPosition+1; j < elementsCopy.size(); ++j) {
        if (elementsCopy[j] == expectedValue)
            return j - displacement;
    }
    return -1;
}

vector<RgbElement> moveExpValToTheBeg(int requiredMoves, vector<RgbElement> elementsCopy, int moveIndex) {
    int k = 0;
    while (k < requiredMoves) {
        moveTripleBack(elementsCopy, moveIndex);
        ++k;
    }
    return elementsCopy;
}


/*
 * Algorithm: First we have a problem where there must be a letter x under the index [0] (usually we start with x = R).
 * We try to search for x in 3k places, if we find it then we just move the first three to the end so it starts with x.
 * If there is not the desired value in those places, then we look for the index of the first x encountered (iterating
 * from bottom to top) and try put it to the beginning. Depending on the number of balls, there are 3 cases:
 * - size (input) == 3n ⇒ take the three of the x at the beginning [x,?,?] and put it at the end and keep moving all the
 * first three at the end until x stops at the beginning.
 * - size (input) == 3n + 1 ⇒ take the triple of x at the end [?,?,x] and move it to the end. Then again, taking all
 * three of them out of the beginning, x at some point will stand in the desired place.
 * size (input) == 3n + 2 ⇒ you have to take the three of x so that x stands in 2nd place [?,x,?] And take the first
 * three.
*/

Solution NaiveSorting::sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    vector<RgbElement> elementsCopy(elements);
    int colors_number = sizeof(RGB_ELEMENTS) / sizeof(RGB_ELEMENTS[0]); // 3
    for (int i = 0; i < maxRgbGroupsAmount * colors_number; ++i) {
        RgbElement expected_value = RGB_ELEMENTS[i % colors_number];
        if (elementsCopy[i] == expected_value) {
            continue;
        }
        int position = findExpValTriplePosition(i, elementsCopy, expected_value, 0);
        if (expected_value == RgbElement::R) {
            int moves;
            if (position % colors_number == 0) {  // on position 3k
                moves = (position - i) / colors_number;
                elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
            }
            else if (position % colors_number == 1 || position % colors_number == 2) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 0);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 2);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 1);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
            }
        }
        else if (expected_value == RgbElement::G) {
            int moves;
            if (position % colors_number == 1) {  // on position n 3k + 1
                moves = (position - i) / colors_number;
                elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
            }
            else if (position % colors_number == 2 || position % colors_number == 0) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 1);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 0);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 2);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
            }
        }
        else if (expected_value == RgbElement::B) {
            int moves;
            if (position % colors_number == 2) {  // on position 3k + 2
                moves = (position - i) / colors_number;
                elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
            }
            else if (position % colors_number == 0 || position % colors_number == 1) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 2);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 1);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we may move already sorted balls and we need to find
                        // expected value further
                        move_position = findExpValTriplePosition(position, elementsCopy, expected_value, 0);
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    elementsCopy = moveExpValToTheBeg(moves, elementsCopy, i);
                }
            }
        }
    }

    int well = 0;
    for (int i = 0; i < elementsCopy.size(); i += colors_number) {
        if (elementsCopy[i] == RgbElement::R && elementsCopy[i + 1] == RgbElement::G &&
            elementsCopy[i + 2] == RgbElement::B) {
            well++;
        } else {
            break;
        }
    }
    cout << "Well: " << well << std::endl;
    return Solution(elementsCopy);
}



