#include "BreadthSearch.h"

Solution BreadthSearchAlgorithm::recursiveSolution(const std::vector<RgbElement> &elements, const NodesVector &nodes,
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

                if (areElementsArrangedCorrectly(elementsCopy, kMaxRgbGroupsAmount)) {
                    return Solution(std::move(elementsCopy), std::move(indexesOfRgbGroups));
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
Solution BreadthSearchAlgorithm::solution(const std::vector<RgbElement> &elements) {
    const int kGroupSize = kRgbElements.size();
    if (elements.size() < kGroupSize) return Solution();
    const int kChildNodesNumber = (int) elements.size() - kGroupSize;
    const int kMaxRgbGroupsAmount = maxRgbGroupsAmount(elements);
    if (areElementsArrangedCorrectly(elements, kMaxRgbGroupsAmount)) {
        return Solution(elements, {});
    }

    NodesVector nextNodes;
    for (int i = 0; i < kChildNodesNumber; ++i) {
        Node<int> node(i, nullptr);
        std::vector<RgbElement> elementsCopy(elements);
        std::vector<int> indexesOfRgbGroups = nodeValuesFromGivenNodeToRoot(node);

        std::reverse(indexesOfRgbGroups.begin(), indexesOfRgbGroups.end());
        for (int ind : indexesOfRgbGroups) moveTripleBack(elementsCopy, ind);

        if (areElementsArrangedCorrectly(elementsCopy, kMaxRgbGroupsAmount)) {
            return Solution(std::move(elementsCopy), std::move(indexesOfRgbGroups));
        } else { nextNodes.emplace_back(node); }
    }
    return recursiveSolution(elements, nextNodes, kChildNodesNumber, kMaxRgbGroupsAmount);
}

