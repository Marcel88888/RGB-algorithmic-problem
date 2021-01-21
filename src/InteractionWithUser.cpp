
#include "InteractionWithUser.h"

using namespace std;


vector<string> splitWords(const string &str) {
    vector<string> splitWords;
    istringstream ss(str);
    string word;
    while (ss >> word) {
        splitWords.push_back(word);
    }
    return splitWords;
}


void InteractionWithUser::interactWithUser(const unordered_map<std::string,
        CommandWithoutArgs> &mappedCommandsWithoutArgs) {
    std::cout << "Use 'help' to see the list of commands" << std::endl;
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
            shouldTerminate = !cmd.ececute();
        } else {
            std::cout << "Command is not found!" << std::endl;
        }
    }
}
