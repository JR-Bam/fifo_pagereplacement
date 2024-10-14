#include "PageReplacer.hpp"
#include <algorithm>


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
    int* prevColumnArr = result.getList()[0].array;
    std::fill(prevColumnArr, prevColumnArr + pageFrame, UNINITIALIZED);
    
    for (int i = 0; i < refLength; i++){
        Column* currentColumn = &result.getList()[i];
        const int currRefInt = refStringAsInt[i];

        // Copies the previous column data to the current column
        std::copy(prevColumnArr, prevColumnArr + pageFrame, currentColumn->array);

        // The current frame data can either be left alone or a value can be pushed
        // Depending if there was a hit or miss
        if (isInColumn(currRefInt, currentColumn->array)){
            result.markColumn(i, ColumnResult::HIT);
        } else {
            result.markColumn(i, ColumnResult::MISS);
            pushToColumn(currRefInt, currentColumn->array);
        }
        // 4th Iteration
        /*      v
            4 6 7 6 5 7 4 5 7
            
            4 6 7 7
            - 4 6 6
            - - 4 4
            * * *
        */
        
        // Sets the buffer to point to the current frame data for the next iteration.
        prevColumnArr = currentColumn->array;
    }
}

bool PageReplacer::isInColumn(const int reference, const int *columnArr)
{
    for (int i = 0; i < pageFrame; i++){
        if (reference == columnArr[i])
            return true;
    }
    return false;
}

void PageReplacer::pushToColumn(int toPush, int *columnArr)
{
    for (int i = pageFrame - 1; i > 0; i--){
        columnArr[i] = columnArr[i-1];
    }
    columnArr[0] = toPush;
}

PageReplacer::~PageReplacer()
{
    delete[] refStringAsInt;
}

