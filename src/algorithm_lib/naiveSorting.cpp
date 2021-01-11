#include "naiveSorting.h"

using namespace std;

//Solution NaiveSorting::sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount) {
//    vector<RgbElement> elementsCopy(elements);
//    int size = sizeof(RGB_ELEMENTS)/sizeof(RGB_ELEMENTS[0]);; // 3
//    for (int i = 0; i < maxRgbGroupsAmount * size; ++i) {
//        if (elementsCopy[i] == RGB_ELEMENTS[i % size]) {
//            continue;
//        }
//        else {
//            for (int j = i + int(size - (elementsCopy.size() % size));
//                j < elementsCopy.size() - size; j += size) {
//                cout << j << endl;
//                if (elementsCopy[j] == RGB_ELEMENTS[i % size]) {
//                    int moves = 0;
//                    if (elementsCopy.size() % size == 0) { //  [x, ?, ?]
//                        moveTripleBack(elementsCopy, j);
//                        moves = int((elementsCopy.size() - 3) / size);
//                    }
//                    else if (elementsCopy.size() % size == 1) {  // [?, ?, x]
//                        moveTripleBack(elementsCopy, j-2);
//                        moves = int((elementsCopy.size() - 1) / size);
//                    }
//                    else { // [?, x, ?]
//                        moveTripleBack(elementsCopy, j-1);
//                        moves = int((elementsCopy.size() - 2) / size);
//                    }
//                    for (int k = 0; k < moves; ++k) {
//                        moveTripleBack(elementsCopy, i);
//                    }
//                    break;
//                }
//            }
//        }
//    }
//    return Solution(move(elementsCopy));
//}

Solution NaiveSorting::sort(const vector<RgbElement> &elements, int maxRgbGroupsAmount) {
    vector<RgbElement> elementsCopy(elements);
    int colors_number = sizeof(RGB_ELEMENTS)/sizeof(RGB_ELEMENTS[0]); // 3
    for(int i = 0; i < maxRgbGroupsAmount * colors_number; ++i) {
        RgbElement expected_value = RGB_ELEMENTS[i % colors_number];
        if (elementsCopy[i] == expected_value) {
            continue;
        }
        int position = -1;
        for(int j = i+1; j < elementsCopy.size(); ++j) {
            if (elementsCopy[j] == expected_value) {
                position = j;
                break;
            }
        }
        if (expected_value == RgbElement::R) {
            int moves;
            int k = 0;
            if (position % colors_number == 0) {  // on position 3k
                moves = (position - i) / colors_number;
                while (k < moves) {
                    moveTripleBack(elementsCopy, i);
                    ++k;
                }
            }
            else if (position % colors_number == 1 || position % colors_number == 2) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 2;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 1;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
            }
        }
        else if (expected_value == RgbElement::G) {
            int moves;
            int k = 0;
            if (position % colors_number == 1) {  // on position 3k + 1
                moves = (position - i) / colors_number;
                while (k < moves) {
                    moveTripleBack(elementsCopy, i);
                    ++k;
                }
            }
            else if (position % colors_number == 2 || position % colors_number == 0) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 1;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 2;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
            }
        }
        else if (expected_value == RgbElement::B) {
            int moves;
            int k = 0;
            if (position % colors_number == 2) {  // on position 3k + 2
                moves = (position - i) / colors_number;
                while (k < moves) {
                    moveTripleBack(elementsCopy, i);
                    ++k;
                }
            }
            else if (position % colors_number == 0 || position % colors_number == 1) {
                if (elementsCopy.size() % colors_number == 0) {
                    int move_position = position - 2;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 2;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 1 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 1) {
                    int move_position = position - 1;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l - 1;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 2 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
                else if (elementsCopy.size() % colors_number == 2) {
                    int move_position = position;
                    if (move_position < i) { // because sometimes we can move already sorted balls
                        for(int l = position+1; l < elementsCopy.size(); ++l) {
                            if(elementsCopy[l] == expected_value) {
                                move_position = l;
                                break;
                            }
                        }
                    }
                    moveTripleBack(elementsCopy, move_position);
                    moves = (int(elementsCopy.size()) - 3 - i) / colors_number;
                    while (k < moves) {
                        moveTripleBack(elementsCopy, i);
                        ++k;
                    }
                }
            }
        }
    }

    int well = 0;
//    for(int i = 0; i < elementsCopy.size(); i += colors_number) {
//        if(elementsCopy[i] == RgbElement::R && elementsCopy[i+1] == RgbElement::G &&
//           elementsCopy[i+2] == RgbElement::B) {
//            well++;
//        }
//    }
//
//    int z = 0;
//    while(z < well * colors_number) {
//        if(elementsCopy[z] == RgbElement::R && elementsCopy[z+1] == RgbElement::G &&
//        elementsCopy[z+2] == RgbElement::B) {
//            z += colors_number;
//        }
//        else { moveTripleBack(elementsCopy, z); }
//    }

    well = 0;
    for(int i = 0; i < elementsCopy.size(); i += colors_number) {
        if(elementsCopy[i] == RgbElement::R && elementsCopy[i+1] == RgbElement::G &&
           elementsCopy[i+2] == RgbElement::B) {
            well++;
        }
        else {
            break;
        }
    }
    cout << "Well: " << well << std::endl;
    return Solution(elementsCopy);
}
