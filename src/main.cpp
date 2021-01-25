#include <iostream>
#include <unordered_map>
#include <vector>
#include "Commands.h"
#include "InteractionWithUser.h"
#include "algorithm_lib/NaiveSorting.h"

using namespace std;


int main(int argc, const char *argv[]) {
    if (argc == 1) {
        const std::vector<CommandWithoutArgs> allCommandsWithoutArgs = {
                {"exit",    "terminate the process",
                        [] { return false; }},
                {"help",    "list all the commands",
                        [&allCommandsWithoutArgs] { return printAllCommandsCm(allCommandsWithoutArgs); }},
                {"adv",     "sort the balls using the advanced algorithm",
                        advancedSortCm},
                {"naive",   "sort the balls using the naive sorting algorithm",
                        naiveSortCm},
                {"breadth", "sort the balls using the breadth search algorithm",
                        breadthSearchCm},
                {"ini",     "sort the balls using the initialTripleSearch algorithm",
                        initialTripleCm},
                {"meas",    "Measure time of the advanced algorithm",
                        measureAdvancedCm}
        };
        std::unordered_map<string, CommandWithoutArgs> mappedCommandsWithoutArgs;
        for (const CommandWithoutArgs &cmd : allCommandsWithoutArgs) {
            mappedCommandsWithoutArgs.insert(make_pair(cmd.name, cmd));
        }
        InteractionWithUser::interactWithUser(mappedCommandsWithoutArgs);
    } else { // Execute single command using argc, argv
        std::unordered_map<string, CommandWithoutArgs> mappedCommands = {
                {"--generate", {"generate", "generate a bunch of elements", [&]() {
                    return generateElementsCm(argc, argv);
                }}}
        };
        auto iter = mappedCommands.find(argv[1]);
        if (iter != mappedCommands.end()) {
            const CommandWithoutArgs &foundCommand = iter->second;
            foundCommand.execute();
        } else {
            std::cerr << "No command found" << std::endl;
        }
    }

    return 0;
}