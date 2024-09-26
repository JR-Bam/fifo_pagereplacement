#include <iostream>
#include "PageReplacer.hpp"
using namespace std;

// void clearScreen() {
// #ifdef _WIN32
//     system("cls");
// #elif defined(__APPLE__) || defined(__linux__)
//     system("clear");
// #else
//     cout << "Error determining platform." << endl;
// #endif
// }



int main(){
    std::string refString;
    int pageFrame;

    cout << "Enter refString: ";
    cin >> refString;

    cout << "Enter pageFrame: ";
    cin >> pageFrame;

    PageReplacer replacer(refString, pageFrame);
    replacer.printResultAll();
    
    return 0;
}

