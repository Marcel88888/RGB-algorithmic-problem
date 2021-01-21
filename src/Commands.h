
#ifndef RGB_ALGORITHMIC_PROBLEM_COMMANDS_H
#define RGB_ALGORITHMIC_PROBLEM_COMMANDS_H

#include <string>
#include <functional>
#include <iostream>
#include "algorithm_lib/PrintingUtilities.h"
#include "algorithm_lib/TimeMeasurment.h"
#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/AdvancedSort.h"

struct CommandWithoutArgs {
    std::string name;
    std::string description;
    /// must return false if execution finished incorrectly
    std::function<bool()> ececute;

    bool operator==(const CommandWithoutArgs &rhs) const {
        return name == rhs.name &&
               description == rhs.description;
    }

    bool operator!=(const CommandWithoutArgs &rhs) const {
        return !(rhs == *this);
    }

    CommandWithoutArgs(std::string name,
                       std::string description,
                       std::function<bool()> runnable) :
            name(std::move(name)), description(std::move(description)), ececute(std::move(runnable)) {}
};


bool printAllCommandsCm(const std::vector<CommandWithoutArgs> &allCommands);

bool advancedSortCm();

bool measureAdvancedCm();

//TODO(@pochka15):
bool generateElementsCm() {
    /*  fun generateValues(generator, starting_elements_amount, number_of_elements_added, iterations_number)
 * generator type should be an enum value, see RandomUtilities
 * starting_elements_amount: the starting amount of generated elements will be equal to this value
 * number_of_elements_added: after each iteration it's increased the amount of elements by the number_of_elements_added
 * iterations_number: how many times we generate the values
 * */
}


#endif //RGB_ALGORITHMIC_PROBLEM_COMMANDS_H
