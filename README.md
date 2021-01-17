# Useful howtos and resources

## Useful resources

- [MinGW-w64 - for 32 and 64 bit Windows](https://sourceforge.net/projects/mingw-w64/files/)
- [C++ Core Guidelines: Passing Smart Pointers](https://www.modernescpp.com/index.php/c-core-guidelines-passing-smart-pointer)
- [Official c++ guidelines that explain how to code in c++](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main)
- [How to pass smart pointers and all the most important stuff about the c++11](https://youtu.be/xnqTKD8uD64?t=1141)

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
