#include "PageReplacer.hpp"
#include <algorithm>
#include <iostream>

PageReplacer::PageReplacer(std::string refString, int pageFrame)
    : pageFrame{pageFrame}, refLength{(int)refString.length()},
        result{PageReplacementResult(pageFrame, this->refLength)}
{
    // Convert the refString to an array of int values
    this->refStringAsInt = new int[this->refLength];
    this->refStrToInt(refString);

    // Proceed to calculate the page replacement thing
    this->calculatePageReplacement();
}

void PageReplacer::printResultAll()
{
    for (int i = 0; i < refLength; i++)
        std::cout << refStringAsInt[i] << ' ';
    std::cout << "\n\n";
    result.printResult();
}

void PageReplacer::refStrToInt(std::string& str)
{
    // This heavily depends on the assumption that the reference string is all digits 0-9
    // The ascii value of `0` is 48 and `1` being 49, so on and so forth
    // So for example if I convert `2` to int it will have the value of 50.
    // And I subtract that with 48 which will be 2 which is the final value.
    for (int i = 0; i < refLength; i++){
        refStringAsInt[i] = (int) str[i] - 48;
    }
}

void PageReplacer::calculatePageReplacement()
{
    // Initializes a buffer that contains all uninitialized frame data
    int* prevFrameData = new int[pageFrame]; // TODO : Try to free this without making this code more bullshit 
    std::fill(prevFrameData, prevFrameData + pageFrame, UNINITIALIZED);
    
    for (int i = 0; i < refLength; i++){
        Frame* currFrame = &result.getList()[i];
        const int currRefInt = refStringAsInt[i];

        // Copies the previous frame data to the current
        std::copy(prevFrameData, prevFrameData + pageFrame, currFrame->list);

        // The current frame data can either be left alone or a value can be pushed
        // Depending if there was a hit or miss
        if (isInFrameList(currRefInt, currFrame->list)){
            result.markFrame(i, FrameResult::HIT);
        } else {
            result.markFrame(i, FrameResult::MISS);
            pushFrame(currRefInt, currFrame->list);
        }
        
        // Sets the buffer to point to the current frame data for the next iteration.
        prevFrameData = currFrame->list;
    }
}

bool PageReplacer::isInFrameList(const int reference, const int *frame)
{
    for (int i = 0; i < pageFrame; i++){
        if (reference == frame[i])
            return true;
    }
    return false;
}

void PageReplacer::pushFrame(int toPush, int *frame)
{
    for (int i = pageFrame - 1; i > 0; i--){
        frame[i] = frame[i-1];
    }
    frame[0] = toPush;
}

PageReplacer::~PageReplacer()
{
    delete[] refStringAsInt;
}
