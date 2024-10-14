/*
    Glossary of variables.

    Given this result:
    2 3 4 2 3 3 3 2 5

    2 3 4 4 4 4 4 4 5
    - 2 3 3 3 3 3 3 4
    - - 2 2 2 2 2 2 3
    - - - - - - - - 2
    * * *           *

    >> pageFrame = 4
    >> refLength = 9
    >> refString = "234233325"
    >> refStringAsInt = {2, 3, 4, 2, 3, 3, 3, 2, 5}
*/

#pragma once
#ifndef PAGE_REPLACER_HPP
#define PAGE_REPLACER_HPP


#include <string>
#include "PageReplacementResult.hpp"

class PageReplacer
{
private:
    int pageFrame;
    int refLength;

    int* refStringAsInt = nullptr;
    PageReplacementResult result;

    void refStrToInt(std::string&);
    void calculatePageReplacement();
    bool isInColumn(const int, const int*);
    void pushToColumn(int, int*);

public:
    PageReplacer(std::string, int);
    void printResultAll();
    void printResultByColumn();
    ~PageReplacer();
};


#endif