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

std::vector<std::vector<RgbElement>> generateElements(const RandomBallsGenerator generator,
                      const int startingElementsAmount,
                      const int numberOfElementsAdded,
                      const int iterationsNumber) {
    std::vector<std::vector<RgbElement>> all_elements;
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
        all_elements.push_back(elements);
    }
    return all_elements;
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
//    RandomBallsGenerator gen;
//    if (parsedOpts.generator == "rand")
//        gen = RandomBallsGenerator::Random;
//    else
//        gen = RandomBallsGenerator::LinkedRandom;

//    generateElements(gen,
//                     parsedOpts.startingElementsAmount,
//                     parsedOpts.numberOfElementsAdded,
//                     parsedOpts.iterationsNumber,
//                     std::cout);
    return true;
}

void doTimeTest(SortingAlgorithms algorithm,
                int startingElementsAmount,
                int numberOfElementsAdded,
                int iterationsNumber,
                const string& fileName) {
    std::ofstream outfile (fileName);
    vector<vector<RgbElement>> all_elements = generateElements(RandomBallsGenerator::Random,
                                                               startingElementsAmount,
                                                               numberOfElementsAdded,
                                                               iterationsNumber);
    outfile << fileName << " startingElementsAmount: " << startingElementsAmount <<
    " numberOfElementsAdded: " << numberOfElementsAdded <<
    " iterationsNumber: " << iterationsNumber << "\n";
    int i = 0;
    for (auto & elements : all_elements) {
        if (algorithm == SortingAlgorithms::NaiveSorting) {
            outfile << elements.size() << "\n";
            int max_rgb_groups_amount = maxRgbGroupsAmount(elements);
            double time = elapsedTime([&] {
                cout << NaiveSorting::sort(elements, max_rgb_groups_amount).arrangedElements << std::endl;
            });
            outfile << time << "\n";
        }
        else if (algorithm == SortingAlgorithms::InitialTripleSearch) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                cout << InitialTripleSearch::sort(elements, (int)elements.size()/100).arrangedElements << std::endl;
            });
            outfile << time << "\n";
        }
        else if (algorithm == SortingAlgorithms::AdvancedSort) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                cout << AdvancedSort::solution(elements).arrangedElements << std::endl;
            });
            outfile << time << "\n";
        }
        else if (algorithm == SortingAlgorithms::BreadthSearch) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                cout << BreadthSearchAlgorithm::solution(elements).arrangedElements << std::endl;
            });
            outfile << time << "\n";
        }
        ++i;
    }
    outfile.close();
}