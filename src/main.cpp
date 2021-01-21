#include <iostream>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/BreadthSearch.h"
#include "algorithm_lib/NaiveSorting.h"
#include "algorithm_lib/InitialTripleSearch.h"
#include "algorithm_lib/PrintingUtilities.h"
#include "algorithm_lib/AdvancedSort.h"

using namespace std;

struct CommandWithoutArgs {
    string name;
    string description;
    /// must return false if execution finished incorrectly
    function<bool()> executionFunction;

    bool operator==(const CommandWithoutArgs &rhs) const {
        return name == rhs.name &&
               description == rhs.description;
    }

    bool operator!=(const CommandWithoutArgs &rhs) const {
        return !(rhs == *this);
    }

    CommandWithoutArgs(string name,
                       string description,
                       function<bool()> runnable) :
            name(std::move(name)), description(std::move(description)), executionFunction(std::move(runnable)) {}
};

bool printAllCommandsCm(const std::vector<CommandWithoutArgs> &allCommands) {
    for (const auto &cmd : allCommands) {
        std::cout << cmd.name << ": " << cmd.description << "\n";
    }
    std::cout << flush;
    return true;
}


vector<string> splitWords(const string &str) {
    vector<string> splitWords;
    istringstream ss(str);
    string word;
    while (ss >> word) {
        splitWords.push_back(word);
    }
    return splitWords;
}

bool advancedSort() {
    cout << "Enter the number of balls divisible by 3" << endl;
    int ballsNumber;
    cin >> ballsNumber;
    vector<RgbElement> elements(ballsNumber);

//  Use of the uniform distribution
    generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });

    cout << "Result:\n";
    std::cout << elements << std::endl;
    cout << AdvancedSort::solution(elements).arrangedElements << std::endl;
    return true;
}


int main() {
    const std::vector<CommandWithoutArgs> allCommandsWithoutArgs = {
            {"exit", "terminate the process",
                    [] { return false; }},
            {"help", "list all the commands",
                    [&allCommandsWithoutArgs] {
                        return printAllCommandsCm(allCommandsWithoutArgs);
                    }},
            {"adv",  "sort the balls using the advanced algorithm", advancedSort}

//    cout << "naive - NaiveSorting" << endl;
//    cout << "initial - InitialTripleSearch" << endl;
//    cout << "advanced - AdvancedSearch" << endl;
//    cout << "breadth - BreadthSearch" << endl;
//    cout << endl;
    };


    std::unordered_map<string, CommandWithoutArgs> mappedCommandsWithoutArgs;
    for (const CommandWithoutArgs &cmd : allCommandsWithoutArgs) {
        mappedCommandsWithoutArgs.insert(make_pair(cmd.name, cmd));
    }


    bool shouldTerminate = false;
    while (!shouldTerminate) {
//        Read command
        vector<string> commandWords;
        cout << "Enter your command: " << flush;
        string enteredCommand;
        getline(cin, enteredCommand);
        commandWords = splitWords(enteredCommand);
        cout << commandWords << endl;
//        Run mapped execution function
        const auto iter = mappedCommandsWithoutArgs.find(enteredCommand);
        if (iter != mappedCommandsWithoutArgs.cend()) {
            const auto &cmd = iter->second;
            shouldTerminate = !cmd.executionFunction();
        } else {
            std::cout << "Command is not found!" << std::endl;
        }
    }
    return 0;
}