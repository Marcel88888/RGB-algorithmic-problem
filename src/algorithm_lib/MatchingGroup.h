
#ifndef RGB_ALGORITHMIC_PROBLEM_MATCHINGGROUP_H
#define RGB_ALGORITHMIC_PROBLEM_MATCHINGGROUP_H

#include <map>
#include <utility>
#include <vector>
#include <ostream>
#include "RgbAlgorithmUtilities.h"
#include "WindowsPrintingUtilities.h"

inline const std::nullopt_t AnyElement = std::nullopt;

class MatchingGroup {
public:
    explicit MatchingGroup(std::vector<std::optional<RgbElement>> elements) :
            elements(std::move(elements)) {}

    bool operator==(const MatchingGroup &rhs) const;

    bool operator!=(const MatchingGroup &rhs) const;

    std::vector<std::optional<RgbElement>> elements;

    [[nodiscard]] bool matches(std::vector<RgbElement>::const_iterator beg,
                               std::vector<RgbElement>::const_iterator end) const;

    friend std::ostream &operator<<(std::ostream &os, const MatchingGroup &group);
};


#endif //RGB_ALGORITHMIC_PROBLEM_MATCHINGGROUP_H
