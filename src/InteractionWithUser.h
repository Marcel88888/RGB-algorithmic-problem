
#ifndef RGB_ALGORITHMIC_PROBLEM_INTERACTIONWITHUSER_H
#define RGB_ALGORITHMIC_PROBLEM_INTERACTIONWITHUSER_H


#include <unordered_map>
#include "Commands.h"
#include <sstream>
#include "algorithm_lib/PrintingUtilities.h"

class InteractionWithUser {
public:
    static void interactWithUser(
            const std::unordered_map<std::string, CommandWithoutArgs> &mappedCommandsWithoutArgs);

};


#endif //RGB_ALGORITHMIC_PROBLEM_INTERACTIONWITHUSER_H
