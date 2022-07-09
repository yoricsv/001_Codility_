//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef READER_H
#define READER_H

#include <iostream>
#include <iomanip>

#include "CheckEntry.h"

constexpr auto PATH_READER        = "ReaderDB.dat";
constexpr  int LEFT_MARGIN_READER = 50;
constexpr auto MAX_ISSUE_BOOKS    = 15;

class Reader
{
public:
    Reader() = default;                       // DEFAULT CONSTRUCTOR //
    ~Reader() = default;                      // DEFAULT DESTRUCTOR //

    explicit Reader(
            std::string name,
            std::string date_of_birth,
            std::string phone,
            std::string email
        )                            noexcept; // CONSTRUCTOR //
    Reader(const Reader &  copy_obj) noexcept; // COPY CONSTRUCTOR //
    Reader(      Reader && move_obj) noexcept; // MOVE CONSTRUCTOR //


    static    unsigned   getReaderID  ()        {return reader_id;}
           std::string   getName       () const {return _name;}
           std::string   getBirthDay   () const {return _birth_day;}
           std::string   getPhone      () const {return _phone;}
           std::string   getEMail      () const {return _email;}
//           std::string & getIssueBook () const {return reinterpret_cast<std::string &>(_books_issue_id);};
                  bool   getArriars   () const {return _arrears;}

    void setName    (const std::string & name)  {this -> _name      = name;}
    void setBDay    (const std::string & dob)   {this -> _birth_day = dob;}
    void setPhone   (const std::string & phone) {this -> _phone     = phone;}
    void setEmail   (const std::string & email) {this -> _email     = email;}
    void setArrears ()                          {this -> _arrears   = true;}
    void delArrears ()                          {this -> _arrears   = false;}

       void   createReader ();
     Reader & editReader   (      Reader & reader_obj);
       void   showReader   (const Reader & reader_obj);

//     size_t   operator () (const Reader &  reader_obj) const;
    Reader & operator =  (const Reader &  copy_obj) noexcept; // COPY ASSIGNMENT OPERATOR (OVERLOAD = ) //
    Reader & operator =  (      Reader && move_obj) noexcept; // MOVE ASSIGNMENT OPERATOR (OVERLOAD = ) //
      bool   operator == (const Reader &  other)    const;
      bool   operator != (const Reader &  other)    const;
      bool   operator <  (const Reader &  other)    const;
      bool   operator >  (const Reader &  other)    const;
      bool   operator <= (const Reader &  other)    const;
      bool   operator >= (const Reader &  other)    const;

    friend std::ostream & operator << (
            std::ostream & out_stream,
            const Reader & reader
    );
private:
    static unsigned int   reader_id;
            std::string   _name;
            std::string   _birth_day;
            std::string   _phone;
            std::string   _email;
            std::string   _books_issue_id[MAX_ISSUE_BOOKS];
                   bool   _arrears = false;
                 Reader * _ptr_read{};
};

unsigned Reader::reader_id = 0;


#endif //READER_H
