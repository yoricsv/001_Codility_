//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef BOOK_CARD_H
#define BOOK_CARD_H


#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Book.h"

const int LEFT_MARGIN_CARD = 20;

class BookCard :
    protected Book
{
public:
    BookCard()  = default;
    virtual ~BookCard() = 0;
/**    BookCard(
             std::string title,
             std::string writer,
            unsigned int run_year
        ) :
        _name  (std::move(title)),
        _author(std::move(writer)),
        _year  (run_year)
    {}

     std::string getName      () const {return _name;}
     std::string getAuthor    () const {return _author;}
    unsigned int getPublished () const {return _year;}

    void setName   (const std::string & title)    {this -> _name   = title;}
    void setAuthor (const std::string & writer)   {this -> _author = writer;}
    void setYear   (         unsigned   run_year) {this -> _year   = run_year;}
*/
    static void showCard (const Book & book);
/**
    bool operator == (const BookCard & other) const;
    bool operator != (const BookCard & other) const;
    bool operator <  (const BookCard & other) const;
    bool operator >  (const BookCard & other) const;
    bool operator <= (const BookCard & other) const;
    bool operator >= (const BookCard & other) const;

    friend std::ostream & operator << (
          std::ostream & out_stream,
        const BookCard & book_card
    );
*/
/**
private:
     std::string _name;
     std::string _author;
    unsigned int _year{};
*/
};

#endif //BOOK_CARD_H
