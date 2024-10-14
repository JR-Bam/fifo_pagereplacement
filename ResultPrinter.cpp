#include "PageReplacer.hpp"
#include <iostream>

namespace Terminal{
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#elif defined(__APPLE__) || defined(__linux__)
        system("clear");
#else
        cout << "Error determining platform." << endl;
#endif
    }

    static void printReferenceString(int length, int* refString){
        for (int i = 0; i < length; i++)
            std::cout << refString[i] << ' ';
        std::cout << "\n\n";
    }
}

void PageReplacer::printResultAll()
{
    Terminal::clearScreen();
    Terminal::printReferenceString(refLength, refStringAsInt);
    result.printResult();
    result.printHitRatio();
}

void PageReplacer::printResultByColumn()
{
    // I have absolutely no idea why this starts at 1 in the terminal
    for (int i = 0; i <= refLength; i++){ 
        Terminal::clearScreen();
        Terminal::printReferenceString(refLength, refStringAsInt);
        result.printUptoColumn(i);

        std::cout << "Press enter to proceed... " << i << '/' << refLength << '\n';
        std::cin.get(); // Awaits user to press enter
    }
    std::cout << "Finished!\n";
    result.printHitRatio();
}