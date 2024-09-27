#include "PageReplacementResult.hpp"
#include <iostream>
#include <string>
#include "tabulate/table.hpp"

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

    cout << "\nHits/Misses: " << hitCount << "/" << missCOunt << '\n';
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

void PageReplacementResult::prettyPrintResult()
{
    if (frameList == nullptr) return;
    using namespace tabulate;
    using namespace std;

    Table tb;
    tb.format() // Remove all borders
        .border_top(" ")
        .border_bottom(" ")
        .border_left(" ")
        .border_right(" ")
        .corner(" ");
    

    Table::Row_t header;
    for (int i = 0; i < refLength; i++){ // Display hit or misses
        FrameResult result = frameList[i].result;
        header.push_back((result == FrameResult::HIT)? " ": "*");
    }
    tb.add_row(header);

    // Format whole header row
    tb[0].format()
        .padding_bottom(0.5)
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold});
    
    // Format each individual cell according to a condition
    for (Cell &cell : tb[0]){
        if (cell.get_text() == "*"){
            cell.format()
                .font_color(Color::white)
                .font_background_color(Color::red);
        }
    }
    

    for (int i = 0; i < pageFrame; i++) { 
        // Per row
        Table::Row_t dataRow; 

        for (int j = 0; j < refLength; j++) { // Per frame/column
            int value = frameList[j].list[i];
            
            if (value != UNINITIALIZED) {
                dataRow.push_back(std::to_string(value));
            } else {
                dataRow.push_back(" ");
            }
        }
        tb.add_row(dataRow);
        
        // Format each individual cell in a row according to a condition
        for (Cell &cell : tb[i+1]){
            if (cell.get_text() != " "){ // if there's data
                cell.format()
                    .font_background_color(Color::blue)
                    .border_bottom_background_color(Color::blue)
                    .border_top_background_color(Color::blue)
                    .corner("-");
            }
        }

    }

    cout << tb << '\n';
}
