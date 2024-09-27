/*
    Glossary of variables.

    Given this result:
    2 3 4 2 3 3 3 2 5

    2 3 4 4 4 4 4 4 5
    - 2 3 3 3 3 3 3 4
    - - 2 2 2 2 2 2 3
    - - - - - - - - 2
    * * *           *

    >> frameList[2].list = {4, 3, 2, 10}
    >> frameList[2].result = FrameResult::MISS

    >> see the example of refLength and pageFrame on `PageReplacer.hpp`
*/
#pragma once
#ifndef PAGE_REPLACEMENT_RESULT_HPP
#define PAGE_REPLACEMENT_RESULT_HPP
#define UNINITIALIZED 10 // I set 10 as uninitialized because a data can only hold 0-9

enum class FrameResult {
    HIT,
    MISS
};

struct Frame{ // treat as a java data class
    int* list = nullptr; 
    FrameResult result;
};

class PageReplacementResult
{
private:
    int hitCount = 0;
    int missCOunt = 0;

    int refLength;
    int pageFrame;

    Frame* frameList;
public:
    PageReplacementResult(const int, const int);
    ~PageReplacementResult();

    Frame* getList();
    void markFrame(const int, FrameResult);

    void printResult();
    void printFrame(int);
};


#endif