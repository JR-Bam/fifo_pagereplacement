#include <iostream>
#include "PageReplacer.hpp"
using namespace std;


int main(){
    std::string refString;
    int pageFrame;

    cout << "Enter refString: ";
    cin >> refString;

    cout << "Enter pageFrame: ";
    cin >> pageFrame;

    PageReplacer replacer(refString, pageFrame);
    
    int printMethodChoice;
    cout << "Print all at once (1) or frame by frame (2)?\n>> ";
    cin >> printMethodChoice;

    switch (printMethodChoice) {
    case 1:
        replacer.printResultAll();
        break;
    case 2:
        replacer.printResultByFrame();
        break;
    default:
        break;
    }

    return 0;
}

