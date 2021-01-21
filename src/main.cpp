#include <iostream>
#include <sstream>
//#include "algorithm_lib/RgbAlgorithmUtilities.h"
#include "algorithm_lib/BreadthSearch.h"
//#include "algorithm_lib/NaiveSorting.h"
//#include "algorithm_lib/InitialTripleSearch.h"
#include "algorithm_lib/PrintingUtilities.h"
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

void printHelp() {
    cout << "Help:" << endl << endl;
    cout << "exit - exit program" << endl;
    cout << "naive - NaiveSorting" << endl;
    cout << "initial - InitialTripleSearch" << endl;
    cout << "advanced - AdvancedSearch" << endl;
    cout << "breadth - BreadthSearch" << endl;
    cout << endl;
}

vector<string> splitWords(const string& str)
{
    vector<string> splitWords;
    istringstream ss(str);
    string word;
    while (ss >> word)
    {
        splitWords.push_back(word);
    }
    return splitWords;
}

int main() {
    bool running = true;
    string command;

    while (running)
    {
        vector<string> command_words;
        cout << "rgbRobot$ ";
        getline(cin, command);
        command_words = splitWords(command);
        cout << command_words << endl;

        if (command_words[0] == "exit" && command_words.size() == 1)
            running = false;
        else if (command_words[0] == "naive") {
            if (command_words[1] == "-m1") {
                if (command_words[2] == "<<" && command_words[4] == ">>" && command_words.size() == 6) {

                }
                else
                    cout << "Invalid command." << endl;
            } else if (command_words[1] == "-m2") {

            } else if (command_words[1] == "-m3") {

            }
            else
                cout << "Invalid command." << endl;
        }
        else if (command_words[0] == "initial") {
            if (command_words[1] == "-m1") {

            } else if (command_words[1] == "-m2") {

            } else if (command_words[1] == "-m3") {

            }
            else
                cout << "Invalid command." << endl;
        }
        else if (command_words[0] == "advanced") {
            if (command_words[1] == "-m1") {

            } else if (command_words[1] == "-m2") {

            } else if (command_words[1] == "-m3") {

            }
            else
                cout << "Invalid command." << endl;
        }
        else if (command_words[0] == "breadth") {
            if (command_words[1] == "-m1") {

            } else if (command_words[1] == "-m2") {

            } else if (command_words[1] == "-m3") {

            }
            else
                cout << "Invalid command." << endl;
        }
        else if (command_words[0] == "help" && command_words.size() == 1)
            printHelp();
        else
            cout << "Command not found." << endl;
    }

    return 0;
}