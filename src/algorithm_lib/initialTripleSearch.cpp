#include "initialTripleSearch.h"

using namespace std;

vector<RgbElement> sortingStep(const vector<RgbElement> &elements, int startingPoint) {
    vector<RgbElement> elementsCopy(elements);
    int colors_number = sizeof(RGB_ELEMENTS) / sizeof(RGB_ELEMENTS[0]); // 3
    int i = startingPoint;
    int triples_sorted = 0;

    // phase 1
    while (i < elementsCopy.size() - colors_number * triples_sorted) {
        if (elementsCopy[i] == RgbElement::R && elementsCopy[i+1] == RgbElement::G &&
        elementsCopy[i+2] == RgbElement::B) {
            moveTripleBack(elementsCopy, i);
            triples_sorted++;
            i -= 2;  // moveTripleBack could make new three from two previous balls and new one after this move.
        }
        else { ++i; }
    }

    // phase 2
    int unsorted_balls = (int)elementsCopy.size() - triples_sorted * colors_number;
    int required_moves = unsorted_balls / colors_number;
    for (int j = 0; j < required_moves; ++j) {
        RgbElement last_value = elementsCopy.back();
        int next_req_val = (getElemReqPosition(last_value) + 1) % colors_number;
        int best_move_pos1 = -1; // with values [X,?,?]
        bool double_found = false;  // for values [X1,X2,?]
        bool triple_found = false; // for values [X1,X2,X3]
        for (int k = startingPoint; k < unsorted_balls - 2; ++k) {  // "unsorted_balls - 2" because in the loop I may move a triple
            // starting at k position and ending at k+2 position.
            if (elementsCopy[k] == RGB_ELEMENTS[next_req_val]) {
                best_move_pos1 = k;
                if (elementsCopy[k+1] == RGB_ELEMENTS[(next_req_val+1) % colors_number] &&
                        elementsCopy[k+2] == RGB_ELEMENTS[(next_req_val+2) % colors_number]) {
                    moveTripleBack(elementsCopy, k);
                    unsorted_balls -= colors_number;
                    triple_found = true;
                    break;
                }
                else if (elementsCopy[k+1] == RGB_ELEMENTS[(next_req_val+1) % colors_number]) {
                    moveTripleBack(elementsCopy, k);
                    unsorted_balls -= colors_number;
                    double_found = true;
                    break;
                }
            }
        }
        if (!triple_found && !double_found && best_move_pos1 != -1) {
            moveTripleBack(elementsCopy, best_move_pos1);
            unsorted_balls -= colors_number;
        }
        else if (!triple_found && !double_found) {
            moveTripleBack(elementsCopy, 0);
            unsorted_balls -= colors_number;
        }
    }
    // TODO after phase 2 if the size is 3k+1 or 3k+2 at the beginning there is/are one/two unsorted ball(s).
    return elementsCopy;
}

Solution InitialTripleSearch::sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    vector<RgbElement> elementsCopy(elements);
    int colors_number = sizeof(RGB_ELEMENTS) / sizeof(RGB_ELEMENTS[0]);
    int well = 0;
    for (int i = 0; i < 1; ++i) {
        elementsCopy = sortingStep(elementsCopy, 0);
        for (int i = 0; i < elementsCopy.size(); i += colors_number) {
            if (elementsCopy[i] == RgbElement::R && elementsCopy[i + 1] == RgbElement::G &&
                elementsCopy[i + 2] == RgbElement::B) {
                well++;
            } else {
                break;
            }
        }
    }
    cout << "Well: " << well << std::endl;
    return Solution(elementsCopy);
}
