#include "PageReplacer.hpp"
#include <iostream>
#include <string>
#include "tabulate/table.hpp"

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

    static void prettyPrintReferenceString(int length, int* refString){
        using namespace tabulate;
        Table refTable;
        refTable.format() // Format the borders and stuff
            .border_bottom("_")
            .border_top(" ")
            .border_left(" ")
            .border_right(" ")
            .corner(" ")
            .corner_bottom_left("_")
            .corner_bottom_right("_")
            .border_bottom_color(Color::cyan)
            .corner_bottom_left_color(Color::cyan)
            .corner_bottom_right_color(Color::cyan);

        Table::Row_t refRow; // The row to include each digit of the reference string
        for (int i = 0; i < length; i++)
            refRow.push_back(std::to_string(refString[i]));
        refTable.add_row(refRow);
        refTable[0].format().font_align(FontAlign::center);

        std::cout << refTable << std::endl; // Print it out
    }
}

void PageReplacer::printResultAll()
{
    Terminal::printReferenceString(refLength, refStringAsInt);
    result.printResult();
}

void PageReplacer::printResultByFrame()
{
    for (int i = 0; i <= refLength; i++){ // I have absolutely no idea why this starts at 1 in the terminal
        Terminal::clearScreen();
        Terminal::printReferenceString(refLength, refStringAsInt);
        result.printFrame(i);

        std::cout << "Press enter to proceed... " << i << '/' << refLength << '\n';
        std::cin.get();
    }
    std::cout << "Finished!\n";
}

void PageReplacer::prettyPrintResultAll(){
    Terminal::prettyPrintReferenceString(refLength, refStringAsInt);
    result.prettyPrintResult();
}