#ifndef CONSOLENOTIFIER_H
#define CONSOLENOTIFIER_H
#include "Progress.h"
#include <iostream>
class ConsoleNotifier :
    public Progress
{
    void updateProgress(double value) override
    {
        int barWidth = 70;

        std::cout << "[";
        int pos = barWidth * value;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(value * 100.0) << " %\r";
        std::cout.flush();
    }
};
#endif

