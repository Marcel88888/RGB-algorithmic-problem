# How to

## Generate a vector of RGB elements

For now there implemented some distributions and 1 elements generator from the _randomUtilities.h_

```c++
std::vector<RgbElement> elements(kElementsNumber);

//  Use of the uniform distribution
std::generate(elements.begin(), elements.end(),[] {
return RGB_ELEMENTS[randomUniformInteger(0, 2)];
});

//  Use of the linkedRandomIntegersGenerator
const auto generator = linkedRandomIntegersGenerator(0.5, 0, 2);
std::generate(elements.begin(), elements.end(),[&generator] {
return RGB_ELEMENTS[generator()];
});
```

## Print RGB elements

To print a vector of rgb elements or a single RgbElement use functions declared in algorithmUtilities.h

```c++
std::vector<RgbElement> elements{ R, G, B };
std::cout << elements[0] << std::endl;
std::cout << elements << std::endl;
```

## Build an algorithm for the RGB problem

Use some code from the rgbAlgorithmUtilities.h

- **Solution** structure to represent the solution.
- **moveTripleBack()** function to move a group of 3 elements to the back of elements sequence.
- **areElementsArrangedCorrectly()** function to check if elements are arranged correctly.
- **maxRgbGroupsAmount()** function that calculates the maximum amount of groups containing 3 RgbElements that can be
  found in the elements vector.

## Use breadth search algorithm

- There is a **BreadSearchAlgorithm** class which has a static **solution()** function which gives the Solution
  instance. 