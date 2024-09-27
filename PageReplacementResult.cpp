#include "PageReplacementResult.hpp"
#include <iostream>

PageReplacementResult::PageReplacementResult(const int pageFrame, const int refLength)
    : refLength{refLength}, pageFrame{pageFrame}
{
    this->frameList = new Frame[refLength];
    for (int i = 0; i < refLength; i++){
        this->frameList[i].list = new int[refLength];
    }
}

PageReplacementResult::~PageReplacementResult()
{
    for (int i = 0; i < refLength; i++){
        delete[] frameList[i].list;
    }
    delete[] frameList;
}

Frame *PageReplacementResult::getList()
{
    return frameList;
}

void PageReplacementResult::markFrame(const int index, FrameResult result)
{
    frameList[index].result = result;
    if (result == FrameResult::HIT)
        hitCount++;
    else 
        missCOunt++;
}

void PageReplacementResult::printResult()
{
    if (frameList == nullptr) return;
    using namespace std;

    for (int i = 0; i < refLength; i++){ // Display hit or misses
        FrameResult result = frameList[i].result;

        if (result == FrameResult::HIT){
            cout << "  ";
        } else {
            cout << "* ";
        }
    }
    cout << '\n';
    for (int i = 0; i < pageFrame; i++) { // Per row
        for (int j = 0; j < refLength; j++) { // Per frame/column
            int value = frameList[j].list[i];
            
            if (value != UNINITIALIZED) {
                cout << value << ' ';
            } else {
                cout << "- ";
            }
        }
        cout << '\n';
    }

}

void PageReplacementResult::printFrame(int index)
{
    if (frameList == nullptr) return;
    using namespace std;

    for (int i = 0; i < index; i++){ // Display hit or misses
        FrameResult result = frameList[i].result;

        if (result == FrameResult::HIT){
            cout << "  ";
        } else {
            cout << "* ";
        }
    }
    cout << '\n';
    for (int i = 0; i < pageFrame; i++) { // Per row
        for (int j = 0; j < index; j++) { // Per frame/column
            int value = frameList[j].list[i];
            
            if (value != UNINITIALIZED) {
                cout << value << ' ';
            } else {
                cout << "- ";
            }
        }
        cout << '\n';
    }
}

void PageReplacementResult::printHitRatio()
{
    std::cout << "Hits/Misses: " << hitCount << "/" << missCOunt << "\n\n";
}
