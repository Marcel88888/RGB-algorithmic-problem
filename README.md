# Some info

## About

The task is to put **R G B** balls to the beginning of the queue. The only movement we can make is to put a group of 3
elements to the end.

## Runtime example

```txt
./RGB_algorithmic_problem.exe
---
Use 'help' to see the list of commands
Enter your command: help
help
exit: terminate the process
help: list all the commands
adv: sort the balls using the advanced algorithm
naive: sort the balls using the naive sorting algorithm
breadth: sort the balls using the breadth search algorithm
ini: sort the balls using the initialTripleSearch algorithm
ini2: sort the balls using the initialTripleSearch algorithm
meas: Measure time of the advanced algorithm
Enter your command: adv
adv
Enter the number of balls divisible by 3
12
```

![Runtime](./images/runtime.png)

## How to generate a vector of RGB elements

For now there implemented some distributions and 1 elements generator from the _randomUtilities.h_

```c++
std::vector<RgbElement> elements(kElementsNumber);

//  Use of the uniform distribution
std::generate(elements.begin(), elements.end(),[] {
return kRgbElements[randomUniformInteger(0, 2)];
});

//  Use of the linkedRandomIntegersGenerator
const auto generator = linkedRandomIntegersGenerator(0.5, 0, 2);
std::generate(elements.begin(), elements.end(),[&generator] {
return kRgbElements[generator()];
});
```

## How to print RGB elements

To print a vector of rgb elements or a single RgbElement use functions declared in algorithmUtilities.h

```c++
std::vector<RgbElement> elements{ R, G, B };
std::cout << elements[0] << std::endl;
std::cout << elements << std::endl;
```

## How to build an algorithm for the RGB problem

Use some code from the rgbAlgorithmUtilities.h

- **Solution** structure to represent the solution.
- **moveTripleBack()** function to move a group of 3 elements to the back of elements sequence.
- **areElementsArrangedCorrectly()** function to check if elements are arranged correctly.
- **maxRgbGroupsAmount()** function that calculates the maximum amount of groups containing 3 RgbElements that can be
  found in the elements vector.

## How to use the breadth search algorithm

- There is a **BreadSearchAlgorithm** class which has a static **solution()** function which gives the Solution
  instance.
