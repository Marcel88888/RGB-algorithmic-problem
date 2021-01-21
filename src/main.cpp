#include <iostream>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Commands.h"
#include "InteractionWithUser.h"
#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/BreadthSearch.h"
#include "algorithm_lib/NaiveSorting.h"
#include "algorithm_lib/InitialTripleSearch.h"
#include "algorithm_lib/PrintingUtilities.h"
#include "algorithm_lib/AdvancedSort.h"
#include "algorithm_lib/TimeMeasurment.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        const std::vector<CommandWithoutArgs> allCommandsWithoutArgs = {
                {"exit", "terminate the process",
                        [] { return false; }},
                {"help", "list all the commands",
                        [&allCommandsWithoutArgs] { return printAllCommandsCm(allCommandsWithoutArgs); }},
                {"adv",  "sort the balls using the advanced algorithm",
                        advancedSortCm},
                {"mes",  "Measure time of the advanced algorithm",
                        measureAdvancedCm}
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
        InteractionWithUser::interactWithUser(mappedCommandsWithoutArgs);
    } else { // Execute single command using argc, argv
        std::unordered_map<string, CommandWithoutArgs> mappedCommands = {
                {"generate", {"generate", "generate a bunch of elements", [&]() {
//        TODO(@pochka15): we need to parse the next snippet
//--generate --generator uniform --starting_elements_amount 12 --number_of_elements_added 12 --iterations_number 100 >> generatedElements.txt
//                    return generateElementsCm(parsedArguments);
                    std::cout << argv[1] << std::endl;
                    return true;
                }}}
        };
        auto iter = mappedCommands.find(
                "parsed command from user, e.x. user can give --generate, so we look for the generate command");
        if (iter != mappedCommands.end()) {
            const CommandWithoutArgs &foundCommand = iter->second;
            foundCommand.ececute();
        }
    }

    return 0;
}