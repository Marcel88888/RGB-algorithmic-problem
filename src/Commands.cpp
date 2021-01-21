
#include "Commands.h"

using namespace std;

bool printAllCommandsCm(const std::vector<CommandWithoutArgs> &allCommands) {
    for (const auto &cmd : allCommands) {
        std::cout << cmd.name << ": " << cmd.description << "\n";
    }
    std::cout << std::flush;
    return true;
}

bool measureAdvancedCm() {
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
    double t = elapsedTime([&] {
        cout << AdvancedSort::solution(elements).arrangedElements << std::endl;
    });
    fprintf(stdout, "CPU time used = %lf\n", t);

    return true;
}

bool advancedSortCm() {
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
