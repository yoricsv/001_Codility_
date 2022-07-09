//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef CHECK_INPUT_H
#define CHECK_INPUT_H

#include <iostream>
#include <string>

#include "Menu.h"

template <typename T>
T checkInputData(
        const std::string & message
    )
{
    T input_value;

    do
    {
        /** int checkInputNumber() */
//        std::cout << "\nChoose an option from the menu ";
        std::cout << message << std::endl;

        std::cin  >> input_value;

        if(!std::cin.fail())
            return input_value;
        else
        {
            /** int checkInputNumber() */
//        std::cout << "\nPlease enter an integer\n";
            std::cout << "\nThere is something wrong! Try again...\n";

            std::cin.clear();
            /** int checkInputNumber() */
//            std::cin.ignore(
//                std::numeric_limits<std::streamsize>::max(),
//                '\n'
//            );
        }
    }
    while(!std::cin.fail());

    return input_value;
}

bool isStringTheSame(
        const std::string & var_1,
        const std::string & var_2
    )
{
    size_t length  = var_1.size();
    size_t length1 = var_2.size();
    size_t i       = 0;

    if(length != length1)
        return false;

    for(i = 0; i < length; i++)
    {
        if(tolower(var_1[i]) != tolower(var_2[i]))
            return false;
    }
    return true;
}

#endif //CHECK_INPUT_H
