#ifndef RGB_ALGORITHMIC_PROBLEM_BREADTHSEARCH_H
#define RGB_ALGORITHMIC_PROBLEM_BREADTHSEARCH_H


#include <algorithm>
#include <utility>
#include <vector>
#include <ostream>
#include <iostream>
#include "RgbAlgorithmUtilities.h"

/// Structure that represents graph nodes. Each node has a single parent and contains a value.
/// \tparam T: type of the node value
template<typename T>
struct Node {
    Node(T nodeValue, std::shared_ptr<Node<T>> parentNodePtr) :
            nodeValue(std::move(nodeValue)), parentNodePtr(std::move(parentNodePtr)) {}

    friend std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
        os << "{" << node.nodeValue << ", " << node.parentNodePtr.get() << "}";
        return os;
    }

    T nodeValue;
    std::shared_ptr<Node<T>> parentNodePtr;
};


class BreadthSearchAlgorithm {
public:
    /// A breadth search algorithm that tries to move groups of 3 elements to the end of the elements sequence recursively.
    /// The algorithm tries to find the solution and it doesn't check some corner cases like RBGR which has no solutions
    /// but the algorithm will still try to move groups of elements back endlessly.
    /// \param elements: a vector of RGB elements. The size of the vector must be in range of [0; infinity)
    /// \return the solution for the algorithm.
    static Solution solution(const std::vector<RgbElement> &elements);

    /// A vector of node values that were extracted starting from the given node up to the root node.
    /// \tparam T: type of the node values
    /// \param node: the first node that will be taken to extract a node value
    /// \return: vector, containing node values
    template<typename T>
    static std::vector<T> nodeValuesFromGivenNodeToRoot(const Node<T> &node) {
        std::vector<T> vec;
        const Node<T> *curNodePtr = &node;
//    go from the bottom upstairs while curNode is not a root node
        while (curNodePtr != nullptr) {
            vec.push_back(curNodePtr->nodeValue);
            curNodePtr = curNodePtr->parentNodePtr.get();
        }
        return vec;
    }

private:

    typedef std::vector<Node<int>> NodesVector;

    static Solution recursiveSolution(const std::vector<RgbElement> &elements, const NodesVector &nodes,
                                      int kChildNodesNumber, int kMaxRgbGroupsAmount);
};

#endif //RGB_ALGORITHMIC_PROBLEM_BREADTHSEARCH_H
