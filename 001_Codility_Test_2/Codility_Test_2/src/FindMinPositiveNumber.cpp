//
// Created by Yoric on 21-Feb-22.
//
#include "FindMinPositiveNumber.h"

int solution(std::vector<int> & A)
{
    int counter = 0;

    for(int & i : A)
    {
        if(i < 0) i = 0;
        if(i > 0 && i < counter) i = 0;
        if(i > 0 && i > counter) counter = i;
    }

    for(int i : A)
    {
        if(i == counter) counter++;
    }

    return counter;
}
