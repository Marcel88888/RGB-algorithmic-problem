
#ifndef RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H
#define RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H

#if defined(_WIN32)

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
/// \param indexOfHighlightedGroup: index of the group
/// \param color: the color of the highlighted group
/// \return: the given output stream
std::ostream &printWithHighlightedGroup(std::ostream &out,
                                        const std::vector<RgbElement> &elements,
                                        int indexOfHighlightedGroup,
                                        Color color);

#endif //WIN
#endif //RGB_ALGORITHMIC_PROBLEM_WINDOWSPRINTINGUTILITIES_H
