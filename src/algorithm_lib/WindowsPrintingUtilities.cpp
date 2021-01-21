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


std::ostream &printWithHighlightedGroup(std::ostream &out,
                                        const std::vector<RgbElement> &elements,
                                        int indexOfHighlightedGroup,
                                        Color color) {
    int offset = 0;
    auto next = [&]() { return *(elements.cbegin() + offset++); };
    out << "[";
    for (int i = 0; i < indexOfHighlightedGroup; i++) {
        out << next() << ", ";
    }
    int nextOffset = offset + 3;
    WindowsPrintingUtilities::colored([&] {
        printJoined<RgbElement>(out, elements.cbegin() + offset, elements.cbegin() + nextOffset);
    }, color);
    offset = nextOffset;

    if (offset < elements.size())
        out << ", ";

    printJoined<RgbElement>(out, elements.cbegin() + offset, elements.cend());
    out << "]";
    return out;
}

#endif
