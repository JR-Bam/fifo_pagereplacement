/*
 *   Group 1: FIFO
 *   Members:
 *       Simyunn, Jan Ryan
 *       Aquino, Nathanielle Dae
 *       Lim, Jan Eriko
 *       Alawaddin, Al-Nadheem
 * 
 *   This project uses CMAKE to build and run.
 */

#include <iostream>
#include "PageReplacer.hpp"
using namespace std;

bool refStrValid(const std::string& refStr){
    for (int i = 0; i < refStr.length(); i++){
        if (refStr[i] < 48 || refStr[i] > 57){
            std::cout << "Invalid format.\n";
            return false;
        }
    }
    return true;
}

int main(){
    std::string refString;
    int pageFrame;

    do{
        cout << "Enter refString: ";
        cin >> refString;
    } while (!refStrValid(refString));

    cout << "Enter pageFrame: ";
    cin >> pageFrame;

    PageReplacer replacer(refString, pageFrame);
    
    int printMethodChoice;
    cout << "Print all at once (1) or column by column (2)?\n>> ";
    cin >> printMethodChoice;

    switch (printMethodChoice) {
    case 1:
        replacer.printResultAll();
        break;
    case 2:
        replacer.printResultByColumn();
        break;
    default:
        break;
    }

    return 0;
}

