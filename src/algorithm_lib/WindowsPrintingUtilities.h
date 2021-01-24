#if defined(_WIN32)
#ifndef RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H
#define RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H

#include <windows.h>
#include "RgbAlgorithmUtilities.h"
#include "PrintingUtilities.h"
#include <functional>
#include <ostream>

enum Color {
    RED = 4,
    DEFAULT = 0,
    BLUE = 1,
    WHITE_ON_BLACK = 143
};

class WindowsPrintingUtilities {
public:
    /// Execute runnable with enabled console color.
    /// \param runnable
    /// \param color
    static void colored(const std::function<void()> &runnable, Color color);

private:
    static void setColor(Color color);
};

/// Print vector elements with a colorized group
/// \param out: output stream
/// \param elements: RGB vector elements
/// \param indexesOfHighlightedGroups: index of the group
/// \param color: the color of the highlighted group
/// \return: the given output stream
std::ostream &printWithHighlightedGroups(std::ostream &out,
                                         const std::vector<RgbElement> &elements,
                                         const std::vector<int> &indexesOfHighlightedGroups,
                                         Color color);

#endif //RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H
#endif //WIN
