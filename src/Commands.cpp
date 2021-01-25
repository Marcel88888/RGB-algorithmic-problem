#include "Commands.h"

using namespace std;

bool printAllCommandsCm(const std::vector<CommandWithoutArgs> &allCommands) {
    for (const auto &cmd : allCommands) {
        std::cout << cmd.name << ": " << cmd.description << "\n";
    }
    std::cout << std::flush;
    return true;
}

ostream &printResults(ostream &os, const std::vector<RgbElement> &elements, const Solution &solution) {
    std::vector<RgbElement> elementsCopy(elements);
#if defined(_WIN32)
    for (const int ind : solution.indexesOfMovedGroups) {
        printWithHighlightedGroups(
                os, elementsCopy,
                {ind}, Color::WHITE_ON_BLACK) << "\n";
        moveTripleBack(elementsCopy, ind);
        printWithHighlightedGroups(
                os, elementsCopy,
                {(int) elementsCopy.size() - 3}, Color::RED) << "\n";
    }
    printWithHighlightedGroups(
            os,
            elementsCopy,
            AdvancedSort::positionsOfAllExistingRgbTriples(
                    elementsCopy.cbegin(), elementsCopy.cend()), Color::WHITE_ON_BLACK);
# endif

#ifndef _WIN32
    for (const int ind : solution.indexesOfMovedGroups) {
        os << elementsCopy << '\n';
        moveTripleBack(elementsCopy, ind);
    }
    os << elementsCopy;
# endif
    return os;
}

bool measureAdvancedAlgorithmCm() {
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
    std::cout << "Max amount of triples: " << maxRgbGroupsAmount(elements) << std::endl;

    cout << "Result:\n";
    const Solution &sol = AdvancedSort::solution(elements);
    printResults(cout, elements, sol) << std::endl;
    return true;
}

bool naiveSortCm() {
    cout << "Enter the number of balls: ";
    int ballsNumber;
    cin >> ballsNumber;
    vector<RgbElement> elements(ballsNumber);

//  Use of the uniform distribution
    generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });
    std::cout << "Max amount of triples: " << maxRgbGroupsAmount(elements) << std::endl;

    cout << "Result:\n";
    const Solution &sol = NaiveSorting::sort(elements);
    printResults(cout, elements, sol) << std::endl;
    return true;
}

bool breadthSearchCm() {
    cout << "Enter the number of balls: ";
    int ballsNumber;
    cin >> ballsNumber;
    vector<RgbElement> elements(ballsNumber);

//  Use of the uniform distribution
    generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });
    std::cout << "Max amount of triples: " << maxRgbGroupsAmount(elements) << std::endl;

    cout << "Result:\n";
    const Solution &sol = BreadthSearchAlgorithm::solution(elements);
    printResults(cout, elements, sol) << std::endl;
    return true;
}

bool initialTripleCm() {
    cout << "Enter the number of balls divisible by 3: ";
    int ballsNumber;
    cin >> ballsNumber;
    vector<RgbElement> elements(ballsNumber);

//  Use of the uniform distribution
    generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });
    std::cout << "Max amount of triples: " << maxRgbGroupsAmount(elements) << std::endl;

    cout << "Result:\n";
    int limit = elements.size();
    const Solution &sol = InitialTripleSearch::sort(elements, limit);
    printResults(cout, elements, sol) << std::endl;
    return true;
}

bool initialTripleWithNaiveCm() {
    cout << "Enter the number of balls divisible by 3: ";
    int ballsNumber;
    cin >> ballsNumber;
    vector<RgbElement> elements(ballsNumber);

//  Use of the uniform distribution
    generate(elements.begin(), elements.end(), [] {
        return kRgbElements[randomUniformInteger(0, 2)];
    });
    std::cout << "Max amount of triples: " << maxRgbGroupsAmount(elements) << std::endl;

    cout << "Result:\n";
    int limit = elements.size();
    const Solution &sol = InitialTripleSearch::sortUsingNaiveAlgorithmAtTheEnd(elements, limit);
    printResults(cout, elements, sol) << std::endl;
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
            const auto gen = linkedRandomIntegersGenerator(0.5, 0, 2);
            std::generate(elements.begin(), elements.end(), [&gen] {
                return kRgbElements[gen()];
            });
        }
        all_elements.push_back(elements);
    }
    return all_elements;
}

std::vector<std::vector<RgbElement>> generateLinkedElements(double probabilityOfChoosingPrevElement,
                                                            const int startingElementsAmount,
                                                            const int numberOfElementsAdded,
                                                            const int iterationsNumber) {
    std::vector<std::vector<RgbElement>> all_elements;
    for (int i = 0; i < iterationsNumber; ++i) {
        int elements_size = startingElementsAmount + i * numberOfElementsAdded;
        std::vector<RgbElement> elements(elements_size);
        const auto gen = linkedRandomIntegersGenerator(probabilityOfChoosingPrevElement, 0, 2);
        std::generate(elements.begin(), elements.end(), [&gen] {
            return kRgbElements[gen()];
        });
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
        double probability{};
    };

    auto parser = CmdOpts<MyOpts>::Create(
            {
                    {"--generator",                    &MyOpts::generator},
                    {"--starting_elements_amount",     &MyOpts::startingElementsAmount},
                    {"--number_of_elements_added",     &MyOpts::numberOfElementsAdded},
                    {"--iterations_number",            &MyOpts::iterationsNumber},
                    {"--probability_of_choosing_prev", &MyOpts::probability}});

    auto parsedOpts = parser->parse(argc, argv);
    if (parsedOpts.generator == "rand") {
        const vector<std::vector<RgbElement>> &generatedElements = generateElements(
                RandomBallsGenerator::Random, parsedOpts.startingElementsAmount,
                parsedOpts.numberOfElementsAdded, parsedOpts.iterationsNumber);
        for (const std::vector<RgbElement> &elements : generatedElements) {
            std::cout << elements << std::endl;
        }
    } else {
        const vector<std::vector<RgbElement>> &generatedElements = generateLinkedElements(
                parsedOpts.probability, parsedOpts.startingElementsAmount,
                parsedOpts.numberOfElementsAdded, parsedOpts.iterationsNumber);
        for (const std::vector<RgbElement> &elements : generatedElements) {
            std::cout << elements << std::endl;
        }
    };
    return true;
}

void measureAlgorithmExecutionTime(SortingAlgorithm algorithm,
                                   int startingElementsAmount,
                                   int numberOfElementsAdded,
                                   int iterationsNumber,
                                   const string &fileName) {
    std::ofstream outfile(fileName);
    vector<vector<RgbElement>> generatedElements = generateElements(
            RandomBallsGenerator::Random,
            startingElementsAmount,
            numberOfElementsAdded,
            iterationsNumber);
    outfile << fileName << " startingElementsAmount: " << startingElementsAmount <<
            " numberOfElementsAdded: " << numberOfElementsAdded <<
            " iterationsNumber: " << iterationsNumber << "\n";
    int i = 0;
    for (const auto &elements : generatedElements) {
        if (algorithm == SortingAlgorithm::NaiveSorting) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                NaiveSorting::sort(elements);
            });
            outfile << time << "\n";
        } else if (algorithm == SortingAlgorithm::InitialTripleSearch) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                InitialTripleSearch::sort(elements, (int) elements.size() / 100);
            });
            outfile << time << "\n";
        } else if (algorithm == SortingAlgorithm::AdvancedSort) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                AdvancedSort::solution(elements);
            });
            outfile << time << "\n";
        } else if (algorithm == SortingAlgorithm::BreadthSearch) {
            outfile << elements.size() << "\n";
            double time = elapsedTime([&] {
                BreadthSearchAlgorithm::solution(elements);
            });
            outfile << time << "\n";
        }
        ++i;
    }
    outfile.close();
}

bool measureAlgorithmExecutionTimeCm(int argc, const char **argv) {
    struct MyOpts {
        string algorithmName{};
    };
    auto parser = CmdOpts<MyOpts>::Create({{"--algorithmName", &MyOpts::algorithmName}});
    auto parsedOpts = parser->parse(argc, argv);
    if (parsedOpts.algorithmName == "initial")
        measureAlgorithmExecutionTime(
                SortingAlgorithm::InitialTripleSearch, 999,
                501, 30, "../benchmarking/initialTripleSearch.txt");
    else if (parsedOpts.algorithmName == "breadth") {
        measureAlgorithmExecutionTime(SortingAlgorithm::BreadthSearch, 7, 1, 9,
                                      "../benchmarking/breadthSearch.txt");
    } else if (parsedOpts.algorithmName == "naive") {
        measureAlgorithmExecutionTime(SortingAlgorithm::NaiveSorting, 1000, 125, 30,
                                      "../benchmarking/naiveSorting.txt");
    } else if (parsedOpts.algorithmName == "advanced") {
        measureAlgorithmExecutionTime(SortingAlgorithm::AdvancedSort, 432, 108, 30,
                                      "../benchmarking/advancedSort.txt");
    }
    return true;
}