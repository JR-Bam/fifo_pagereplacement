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
    replacer.prettyPrintResultAll();

    return 0;
}

