#include "PageReplacementResult.hpp"
#include <iostream>

PageReplacementResult::PageReplacementResult(const int pageFrame, const int refLength)
    : refLength{refLength}, pageFrame{pageFrame}
{
    this->columnList = new Column[refLength];
    for (int i = 0; i < refLength; i++){
        this->columnList[i].array = new int[refLength];
    }
}

PageReplacementResult::~PageReplacementResult()
{
    for (int i = 0; i < refLength; i++){
        delete[] columnList[i].array;
    }
    delete[] columnList;
}

Column *PageReplacementResult::getList()
{
    return columnList;
}

void PageReplacementResult::markColumn(const int index, ColumnResult result)
{
    columnList[index].result = result;
    if (result == ColumnResult::HIT)
        hitCount++;
    else 
        missCOunt++;
}

void PageReplacementResult::printResult()
{
    if (columnList == nullptr) return;
    using namespace std;

    for (int i = 0; i < refLength; i++){ // Display hit or misses
        ColumnResult result = columnList[i].result;

        if (result == ColumnResult::HIT){
            cout << "  ";
        } else {
            cout << "* ";
        }
    }
    cout << '\n';
    for (int i = 0; i < pageFrame; i++) { // Per row
        for (int j = 0; j < refLength; j++) { // Per frame/column
            int value = columnList[j].array[i];
            
            if (value != UNINITIALIZED) {
                cout << value << ' ';
            } else {
                cout << "- ";
            }
        }
        cout << '\n';
    }

}

void PageReplacementResult::printColumn(int index)
{
    if (columnList == nullptr) return;
    using namespace std;

    for (int i = 0; i < index; i++){ // Display hit or misses
        ColumnResult result = columnList[i].result;

        if (result == ColumnResult::HIT){
            cout << "  ";
        } else {
            cout << "* ";
        }
    }
    cout << '\n';
    for (int i = 0; i < pageFrame; i++) { // Per row
        for (int j = 0; j < index; j++) { // Per frame/column
            int value = columnList[j].array[i];
            
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
