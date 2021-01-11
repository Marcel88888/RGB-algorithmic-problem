#include "bruteForceSorting.h"

using namespace std;

Solution BruteForceSorting::sort(const vector<RgbElement> &elements, int algorithmIterationsLimit) {
    vector<RgbElement> elementsCopy(elements);
    int a, b;
    for (int i = 0; i < elementsCopy.size() - sizeof(RGB_ELEMENTS); i++) {
        a = 0;
        b = 0;
        while (elementsCopy[i] != RGB_ELEMENTS[i % sizeof(RGB_ELEMENTS)] && b < algorithmIterationsLimit) {
            if (a >= (elementsCopy.size() - i) / (sizeof(RGB_ELEMENTS)*5)) { //TODO sprawdzic jak czesto musi robic te podmiany
                moveTripleBack(elementsCopy, i+1);
                a = 0;
            } else {
                moveTripleBack(elementsCopy, i);
                ++a;
            }
            ++b;
        }
    }
    return Solution(move(elementsCopy));
}
