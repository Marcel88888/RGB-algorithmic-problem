#ifndef RGB_ALGORITHMIC_PROBLEM_COMMANDS_H
#define RGB_ALGORITHMIC_PROBLEM_COMMANDS_H

#include <string>
#include <functional>
#include <iostream>
#include <ostream>
#include <fstream>
#include "algorithm_lib/PrintingUtilities.h"
#include "algorithm_lib/TimeMeasurment.h"
#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/AdvancedSort.h"
#include "algorithm_lib/BreadthSearch.h"
#include "algorithm_lib/NaiveSorting.h"
#include "algorithm_lib/InitialTripleSearch.h"
#include "CommandLineArgumentsParsing.h"


enum SortingAlgorithms {
    AdvancedSort,
    BreadthSearch,
    InitialTripleSearch,
    NaiveSorting,
};


enum RandomBallsGenerator {
    Random,
    LinkedRandom
};

struct CommandWithoutArgs {
    std::string name;
    std::string description;
    /// must return false if execution finished incorrectly
    std::function<bool()> execute;

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
            name(std::move(name)), description(std::move(description)), execute(std::move(runnable)) {}
};


bool printAllCommandsCm(const std::vector<CommandWithoutArgs> &allCommands);

bool advancedSortCm();

bool measureAdvancedCm();

bool generateElementsCm(int argc, const char *argv[]);

void doTimeTest(SortingAlgorithms algorithm,
                int startingElementsAmount,
                int numberOfElementsAdded,
                int iterationsNumber,
                const string& fileName);


#endif //RGB_ALGORITHMIC_PROBLEM_COMMANDS_H
