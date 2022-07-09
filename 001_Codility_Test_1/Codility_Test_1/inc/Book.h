//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <iomanip>
#include <iostream>
#include <string>

#include "CheckEntry.h"

constexpr auto PATH_BOOK        = "BookDB.dat";
constexpr  int LEFT_MARGIN_BOOK = 20;

class Book
{
public:

    Book()  = default;
    virtual ~Book() = default;

    explicit Book(
             std::string title,
             std::string writer,
            unsigned int run_year
        ) noexcept;

            std::string getName      () const {return _name;}
            std::string getAuthor    () const {return _author;}
           unsigned int getPublished () const {return _year;}
    static unsigned int getBookID    ()       {return bookID;}

           void setName  (const  std::string & title)    {this -> _name   = title;}
           void setAuthor(const  std::string & writer)   {this -> _author = writer;}
           void setYear  (      unsigned int   run_year) {this -> _year   = run_year;}
    static void setBookId(      unsigned int   bookId)   {        bookID  = bookId;}

         static void   createBook ();
         static Book & editBook   (      Book & book_obj);
         static void   showBook   (const Book & book_obj);

    /** size_t operator () (const Book & other) const; */
      bool operator == (const Book & other) const;
      bool operator != (const Book & other) const;
      bool operator <  (const Book & other) const;
      bool operator >  (const Book & other) const;
      bool operator <= (const Book & other) const;
      bool operator >= (const Book & other) const;

    friend std::ostream & operator << (
        std::ostream & out_stream,
          const Book & book
    );
    /**
    friend std::istream & operator >> (
        std::istream & in_stream,
          const Book & book
    );
    */
private:
    static unsigned int   bookID;
            std::string   _name;
            std::string   _author;
           unsigned int   _year{};
                   Book * _ptr_book{};
};

unsigned int Book::bookID = 0;


#endif //BOOK_H
