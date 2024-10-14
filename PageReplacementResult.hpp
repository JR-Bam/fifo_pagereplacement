/*
    Glossary of variables.

    Given this result:
    2 3 4 2 3 3 3 2 5

    2 3 4 4 4 4 4 4 5
    - 2 3 3 3 3 3 3 4
    - - 2 2 2 2 2 2 3
    - - - - - - - - 2
    * * *           *

    >> columnList[2].list = {4, 3, 2, 10}
    >> columnList[2].result = ColumnResult::MISS

    >> see the example of refLength and pageFrame on `PageReplacer.hpp`
*/
#pragma once
#ifndef PAGE_REPLACEMENT_RESULT_HPP
#define PAGE_REPLACEMENT_RESULT_HPP

#define UNINITIALIZED 10 // I set 10 as uninitialized because a data can only hold 0-9

enum class ColumnResult {
    HIT,
    MISS
};

struct Column{ // treat as a java data class
    int* array = nullptr; 
    ColumnResult result;
};

class PageReplacementResult
{
private:
    int hitCount = 0;
    int missCOunt = 0;

    int refLength;
    int pageFrame;

    Column* columnList;
public:
    PageReplacementResult(const int, const int);
    ~PageReplacementResult();

    Column* getList();
    void markColumn(const int, ColumnResult);

    void printResult();
    void printColumn(int);
    void printHitRatio();
};


#endif