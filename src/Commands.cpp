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

bool generateElements(const RandomBallsGenerator generator,
                      const int startingElementsAmount,
                      const int numberOfElementsAdded,
                      const int iterationsNumber,
                      std::ostream &stream) {
    for (int i = 0; i < iterationsNumber; ++i) {
        int elements_size = startingElementsAmount + i * numberOfElementsAdded;
        std::vector<RgbElement> elements(elements_size);
        if (generator == RandomBallsGenerator::Random) {
            std::generate(elements.begin(), elements.end(), [] {
                return kRgbElements[randomUniformInteger(0, 2)];
            });
        } else if (generator == RandomBallsGenerator::LinkedRandom) {
//            TODO(@pochka15): maybe add to the arguments optional linkedRandomIntegersGenerator parameters
            const auto gen = linkedRandomIntegersGenerator(0.5, 0, 2);
            std::generate(elements.begin(), elements.end(), [&gen] {
                return kRgbElements[gen()];
            });
        }
        stream << elements << std::endl;
    }
    return true;
}

bool generateElementsCm(int argc, const char *argv[]) {
    struct MyOpts {
        string generator{};
        int startingElementsAmount{};
        int numberOfElementsAdded{};
        int iterationsNumber{};
    };

    auto parser = CmdOpts<MyOpts>::Create(
            {
                    {"--generator",                &MyOpts::generator},
                    {"--starting_elements_amount", &MyOpts::startingElementsAmount},
                    {"--number_of_elements_added", &MyOpts::numberOfElementsAdded},
                    {"--iterations_number",        &MyOpts::iterationsNumber}});

    auto parsedOpts = parser->parse(argc, argv);
    RandomBallsGenerator gen;
    if (parsedOpts.generator == "rand")
        gen = RandomBallsGenerator::Random;
    else
        gen = RandomBallsGenerator::LinkedRandom;

    generateElements(gen,
                     parsedOpts.startingElementsAmount,
                     parsedOpts.numberOfElementsAdded,
                     parsedOpts.iterationsNumber,
                     std::cout);
    return true;
}
