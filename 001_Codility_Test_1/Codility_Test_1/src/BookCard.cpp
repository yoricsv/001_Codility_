//
// Created by Yoric on 20-Feb-22.
//
#include "BookCard.h"

namespace std
{
    template <>
    struct hash<BookCard>
    {
        size_t operator () (const Book & book_obj) const
        {
            hash<string> hashField;

            return
                  hashField(book_obj.getName())
                ^ hashField(book_obj.getAuthor());
        }
    };
}

void BookCard::showCard (const Book & book)
{
    std::cout
            << std::setw(LEFT_MARGIN_CARD)
            << "Title: "  << book.getName()
        << std::endl
            << std::setw(LEFT_MARGIN_CARD)
            << "Author: " << book.getAuthor()
        << std::endl
            << std::setw(LEFT_MARGIN_CARD)
            << "Year: "   << book.getPublished()
        << std::endl;
}
/**
bool BookCard::operator == (const BookCard & other) const
{
    return
           _name   == other._name
        && _author == other._author
        && _year   == other._year;
}
bool BookCard::operator != (const BookCard & other) const
{
    return !(other == * this);
}
bool BookCard::operator <  (const BookCard & other) const
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
bool BookCard::operator >  (const BookCard & other) const
{
    return other < * this;
}
bool BookCard::operator <= (const BookCard & other) const
{
    return !(other < * this);
}
bool BookCard::operator >= (const BookCard & other) const
{
    return !(* this < other);
}

std::ostream & operator << (
          std::ostream & out_stream,
        const BookCard & book_card
    )
{
    return
        out_stream
                << book_card._name   << '|'
                << book_card._author << '|'
                << book_card._year   << '|'
            << std::endl;
}
*/




