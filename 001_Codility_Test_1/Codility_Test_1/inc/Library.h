//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H


#include <iostream>
#include <memory>
#include <unordered_map>

#include "BookCard.h"

class Library
{
public:
    using LibraryMap      =       std::unordered_multimap<std::string, BookCard>; // ALIAS //
    using LibraryMapConst = const std::unordered_multimap<std::string, BookCard>; // ALIAS //

    Library () = default;                                           // DEFAULT CONSTRUCTOR //
    ~Library() = default;                                                    // DISTRUCTOR //

    size_t     totalBooks    () const;
    void       displayLibrary();

    void       addBook       (const std::string & id, BookCard & book);
    void       removeBook    (const std::string & id);
    BookCard & findBook      (const std::string & id);

private:
    LibraryMap books;
};

#endif //LIBRARY_H
