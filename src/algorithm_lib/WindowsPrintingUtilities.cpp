#if defined(_WIN32)

#include "WindowsPrintingUtilities.h"
#include "PrintingUtilities.h"

void WindowsPrintingUtilities::setColor(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int) color);
}

void WindowsPrintingUtilities::colored(const std::function<void()> &runnable, Color color) {
    setColor(color);
    runnable();
    setColor(Color::DEFAULT);
}


std::ostream &printWithHighlightedGroups(std::ostream &out,
                                         const std::vector<RgbElement> &elements,
                                         const std::vector<int> &indexesOfHighlightedGroups,
                                         Color color) {
    if (indexesOfHighlightedGroups.empty()) {
        out << elements;
    } else {
        int offset = 0;
        out << "[";
        for (int ind : indexesOfHighlightedGroups) {
            printJoined<RgbElement>(out, elements.cbegin() + offset, elements.cbegin() + ind);
            if (ind > offset)
                out << ", ";
            offset = ind;
            int nextOffset = offset + 3;
            WindowsPrintingUtilities::colored([&] {
                printJoined<RgbElement>(out, elements.cbegin() + offset, elements.cbegin() + nextOffset);
            }, color);
            offset = nextOffset;
            if (offset < elements.size())
                out << ", ";
        }
        printJoined<RgbElement>(out, elements.cbegin() + offset, elements.cend());
        out << "]";
    }
    return out;
}

#endif
