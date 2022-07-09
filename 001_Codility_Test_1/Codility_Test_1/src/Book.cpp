//
// Created by Yoric on 20-Feb-22.
//
#include "Book.h"

#include <utility>

Book::Book(
         std::string title,
         std::string writer,
        unsigned int run_year
    ) noexcept
{
    this -> _name   = std::move(title);
    this -> _author = std::move(writer);
    this -> _year   = run_year;

    Book::bookID++;
}

void   Book::createBook()
{
    std::string  name,
                 auth;
    unsigned int year;

    name =
        checkInputData< std::string>(
            "\nEnter The Title of book: "
        );
    auth =
        checkInputData< std::string>(
            "\nEnter The Author's Name: "
        );
    year =
        checkInputData<unsigned int>(
            "\nEnter The Year of Publication: "
        );

    Book(
        name,
        auth,
        year
    );
}
Book & Book::editBook  (      Book & book_obj)
{
    std::string  name = book_obj._name,
                 auth = book_obj._author;
    unsigned int year = book_obj._year;

    std::cout
            << "\nModify Book Card No. : "
            << Book::bookID
            << book_obj
        << std::endl;

    name =
        checkInputData< std::string>(
            "\nEnter a new Title for the book: " +
            name
        );
    auth =
        checkInputData< std::string>(
            "\nEnter a new Author name: " +
            auth
        );
    year =
        checkInputData<unsigned int>(
            "\nEnter new publication Year: " +
            static_cast<std::string>(
                reinterpret_cast<const char *>(year)
            )
        );

    Book tmp_book(
        name,
        auth,
        year
    );

    return book_obj = tmp_book;
}
void   Book::showBook  (const Book & book_obj)
{
    std::cout
        << std::setw(84)
        << std::right
        << "***************************************************\n"

        << "|"
        << std::setw(70)
        << "BOOK CARD No. : " << Book::bookID
        << std::setw(47)
        << "|\n"

        << std::setw(84)
        << std::right
        << "***************************************************\n"

        << "|" << std::setw(20) << book_obj._author
        << "|" << std::setw(82) << book_obj._name
        << "|" << std::setw(10) << book_obj._year

        << "|\n"
        << std::setw(84)
        << std::right
        << "***************************************************\n";
}

bool Book::operator == (const Book & other) const
{
    return
           _name   == other._name
        && _author == other._author
        && _year   == other._year;
}
bool Book::operator != (const Book & other) const
{
    return !(other == * this);
}
bool Book::operator <  (const Book & other) const
{
    if (other._name   < _name)
        return false;
    if (other._author < _author)
        return false;

    if (_name   < other._name)
        return true;
    if (_author < other._author)
        return true;

    return _year < other._year;
}
bool Book::operator >  (const Book & other) const
{
    return other < * this;
}
bool Book::operator <= (const Book & other) const
{
    return !(other < * this);
}
bool Book::operator >= (const Book & other) const
{
    return !(* this < other);
}
/**
std::ostream & operator << (
            std::ostream & out_stream,
        const TBinary<T> & book
    )
{
    return
        out_stream
            << std::setw(LEFT_MARGIN_BOOK)
            << "Title: "    << book._name
            << std::endl

            << std::setw(LEFT_MARGIN_BOOK)
            << "Author: "   << book._author
            << std::endl

            << std::setw(LEFT_MARGIN_BOOK)
            << "Year: "     << book._year
            << std::endl;
}
 */
std::ostream & operator << (
        std::ostream & out_stream,
          const Book & book
    )
{
    return
        out_stream
            << Book::bookID << '|'
            << book._name   << '|'
            << book._author << '|'
            << book._year
        << std::endl;
}
/**
std::istream & operator >> (
        std::istream & in_stream,
                Book & book
    )
{
    return
        in_stream
            >> book.setAuthor()
            >> book._name
            >> book._author
            >> book._year;
}
size_t Book::operator () (const Book & bookObj) const
{
    return 0;
}
*/

