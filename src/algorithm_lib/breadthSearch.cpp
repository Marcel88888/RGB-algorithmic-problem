#include "breadthSearch.h"

typedef std::vector<Node<int>> NodesVector;


/// The maximum amount of groups of 3 rgb elements that can be found in the elements vector
/// \param elements: vector of RGB elements
/// \return int value from 0 to infinity
int maxRgbGroupsAmount(const std::vector<RgbElement> &elements) {
    int rCount = 0;
    int gCount = 0;
    int bCount = 0;
    for (const auto &elem : elements) {
        if (elem == 'R') rCount++;
        else if (elem == 'G') gCount++;
        else if (elem == 'B') bCount++;
    }
    return std::min({rCount, gCount, bCount});
}

Solution recursiveSolution(const std::vector<RgbElement> &elements, const NodesVector &nodes,
                           const int kChildNodesNumber, const int kMaxRgbGroupsAmount) {
    if (kMaxRgbGroupsAmount > 0) {
        NodesVector nodesForNextDepth;
        for (const auto &node : nodes) {
            for (int i = 0; i < kChildNodesNumber; ++i) {
                Node<int> childNode(i, std::make_shared<Node<int>>(node));
                std::vector<RgbElement> elementsCopy(elements);
                std::vector<int> indexesOfRgbGroups = nodeValuesFromGivenNodeToRoot(childNode);

                std::reverse(indexesOfRgbGroups.begin(), indexesOfRgbGroups.end());
                for (int ind : indexesOfRgbGroups) moveTripleBack(elementsCopy, ind);

                if (isCorrectSolution(elementsCopy, kMaxRgbGroupsAmount)) {
                    return Solution(std::move(elementsCopy), std::move(indexesOfRgbGroups), kMaxRgbGroupsAmount);
                } else { nodesForNextDepth.emplace_back(childNode); }
            }
        }
        return recursiveSolution(elements, nodesForNextDepth, kChildNodesNumber, kMaxRgbGroupsAmount);
    }
    return Solution();
}

/*
 * Algorithm: create root nodes with values from 0 to kChildNodesNumber exclusively which represent
 * the indexes of groups of elements which will be moved to the end of the elements sequence.
 * For each root node check if after moving groups of elements we get the correct solution. If not then
 * for each root node create child nodes and call the recursiveSolution with all the child nodes.
 */
Solution solution(const std::vector<RgbElement> &elements) {
    const int kGroupSize = 3;
    if (elements.size() < kGroupSize) return Solution();
    const int kChildNodesNumber = (int) elements.size() - kGroupSize;
    const int kMaxRgbGroupsAmount = maxRgbGroupsAmount(elements);
    if (isCorrectSolution(elements, kMaxRgbGroupsAmount)) {
        return Solution(elements, {}, kMaxRgbGroupsAmount);
    }

    NodesVector nextNodes;
    for (int i = 0; i < kChildNodesNumber; ++i) {
        Node<int> node(i, nullptr);
        std::vector<RgbElement> elementsCopy(elements);
        std::vector<int> indexesOfRgbGroups = nodeValuesFromGivenNodeToRoot(node);

        std::reverse(indexesOfRgbGroups.begin(), indexesOfRgbGroups.end());
        for (int ind : indexesOfRgbGroups) moveTripleBack(elementsCopy, ind);

        if (isCorrectSolution(elementsCopy, kMaxRgbGroupsAmount)) {
            return Solution(std::move(elementsCopy), std::move(indexesOfRgbGroups), kMaxRgbGroupsAmount);
        } else { nextNodes.emplace_back(node); }
    }
    return recursiveSolution(elements, nextNodes, kChildNodesNumber, kMaxRgbGroupsAmount);
}
