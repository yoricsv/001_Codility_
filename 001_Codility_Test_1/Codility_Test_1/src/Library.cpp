//
// Created by Yoric on 20-Feb-22.
//
#include "Library.h"


size_t Library::totalBooks   () const
{
    return books.size();
}

void Library::displayLibrary ()
{
    LibraryMapConst::const_iterator it = books.begin();
    for( ; it != books.end(); it++)
    {
        std::cout << "ID " << it -> first  << std::endl;
        std::cout          << it -> second << std::endl;
    }
}

void Library::addBook        (const std::string & id, BookCard & book)
{
    books.insert(std::pair<std::string, BookCard> (id, book));
}

void Library::removeBook     (const std::string & id )
{
    books.erase(id);
}

BookCard & Library::findBook (const std::string & id )
{
    auto it =  books.find(id);
    return it -> second;
}

