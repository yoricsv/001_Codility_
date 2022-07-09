//
// Created by Yoric on 20-Feb-22.
//
#include "Reader.h"

#include <utility>

Reader::Reader(
        std::string name,
        std::string date_of_birth,
        std::string phone,
        std::string email
    )
    noexcept
{
    this -> _name      = std::move(name);
    this -> _birth_day = std::move(date_of_birth);
    this -> _phone     = std::move(phone);
    this -> _email     = std::move(email);

    Reader::reader_id++;
}
// COPY CONSTRUCTOR //
Reader::Reader(const Reader &  copy_obj) noexcept
{
    if(Reader::reader_id <= 0)
        reader_id = 0;
    else
        reader_id = Reader::reader_id;

    _ptr_read  = new Reader;

    this -> _ptr_read  = copy_obj._ptr_read;
}
// MOVE CONSTRUCTOR //
Reader::Reader(      Reader && move_obj) noexcept
{
    if(Reader::reader_id <= 0)
        reader_id = 0;
    else
        reader_id = Reader::reader_id;

    this -> _ptr_read = move_obj._ptr_read;

    Reader::reader_id = 0;
    move_obj._ptr_read  = nullptr;
}
// COPY ASSIGNMENT OPERATOR (OVERLOAD = ) //
Reader & Reader::operator = (const Reader &  copy_obj) noexcept
{
    if (this != &copy_obj)
    {
        delete this -> _ptr_read;

        if(Reader::reader_id <= 0)
            Reader::reader_id = 0;
        else
            Reader::reader_id = Reader::reader_id;

        _ptr_read  = new Reader;

        this -> _ptr_read = copy_obj._ptr_read;
    }
    return *this;
}
// MOVE ASSIGNMENT OPERATOR (OVERLOAD = ) //
Reader & Reader::operator = (      Reader && move_obj) noexcept
{
    if (this != & move_obj)
    {
        delete this -> _ptr_read;

        if(move_obj.reader_id <= 0)
            reader_id = 0;
        else
            reader_id = move_obj.reader_id;

        this -> _ptr_read = move_obj._ptr_read;

        move_obj.reader_id = 0;
        move_obj._ptr_read = nullptr;
    }
    return *this;
}

void Reader::createReader()
{
    std::string name,
                dob,
                phone,
                email;

    name  = checkInputData<std::string>("\nEnter The Reader Name and Surname: ");
    dob   = checkInputData<std::string>("\nEnter The Reader Date of Birth: ");
    phone = checkInputData<std::string>("\nEnter The Reader Mobile Phone: ");
    email = checkInputData<std::string>("\nEnter The Reader e-Mail: ");

    Reader(
        name,
        dob,
        phone,
        email
    );
}
  void   Reader::showReader   (const Reader & reader_obj)
{
    std::cout
        << std::setw(84)
        << std::right
        << "***************************************************\n"

        << "|"
        << std::setw(70)
        << "READER CARD No. : "
        << Reader::reader_id
        << std::setw(47)
        << "|\n"
    
        << std::setw(84)
        << std::right
        << "***************************************************\n"
        
        << "|"
        << std::setw(33)
        << reader_obj._name
        << "|"
        << std::setw(12)
        << reader_obj._birth_day
        << "|"
        << std::setw(18)
        << reader_obj._phone
        << "|"
        << std::setw(49)
        << reader_obj._email
        << "|\n"
        
        << std::setw(84)
        << std::right
        << "***************************************************"
        << std::endl;
}
Reader & Reader::editReader(Reader & reader_obj)
{
    std::string name,
                dob,
                phone,
                email;

    std::cout
            << "\nModify Reader Card No. : "
            << Reader::reader_id
            << reader_obj
        << std::endl;

    name  =
        checkInputData<std::string>(
            "\nEnter The Reader Name and Surname: " +
            name
        );
    dob   =
        checkInputData<std::string>(
            "\nEnter The Reader Date of Birth: "    +
            dob
        );
    phone =
        checkInputData<std::string>(
            "\nEnter The Reader Mobile Phone: "     +
            phone
        );
    email =
        checkInputData<std::string>(
            "\nEnter The Reader e-Mail: "           +
            email
        );

    Reader
        tmp_reader(
            name,
            dob,
            phone,
            email
        );

    return reader_obj = std::move(tmp_reader);
}

//size_t Reader::operator () (const Reader & reader_obj) const
//{
//    return 0;
//}
  bool Reader::operator == (const Reader & other) const
{
    return
            _name           == other._name
            && _birth_day      == other._birth_day
            && _phone          == other._phone
            && _email          == other._email
            && _books_issue_id == other._books_issue_id
            && _arrears        == other._arrears
            && _ptr_read       == other._ptr_read;
}
  bool Reader::operator != (const Reader & other) const
{
    return !(other == * this);
}
  bool Reader::operator <  (const Reader & other) const
{
    if (other._name           < _name)
        return false;
    if (other._birth_day      < _birth_day)
        return false;
    if (other._phone          < _phone)
        return false;
    if (other._email          < _email)
        return false;
    if (other._books_issue_id < _books_issue_id)
        return false;
    if (other._arrears        < _arrears)
        return false;

    if (_name           < other._name)
        return true;
    if (_birth_day      < other._birth_day)
        return true;
    if (_phone          < other._phone)
        return true;
    if (_email          < other._email)
        return true;
    if (_books_issue_id < other._books_issue_id)
        return true;
    if (_arrears        < other._arrears)
        return true;

    return _ptr_read < other._ptr_read;
}
  bool Reader::operator >  (const Reader & other) const
{
    return other < * this;
}
  bool Reader::operator <= (const Reader & other) const
{
    return !(other < * this);
}
  bool Reader::operator >= (const Reader & other) const
{
    return !(* this < other);
}

std::ostream & operator << (
        std::ostream & out_stream,
        const Reader & reader
    )
{
    std::string answer;

    if(reader.getArriars())
        answer = "Yes! He has.";
    else
        answer = "No";
    
    return
        out_stream 
                << std::setw(LEFT_MARGIN_READER)
                << std::right
                << "Reader Name: "
                << std::left 
                << reader._name
            << std::endl
                << std::setw(LEFT_MARGIN_READER)
                << std::right
                << "Reader Day of Birth: "
                << std::left
                << reader._birth_day
            << std::endl
                << std::setw(LEFT_MARGIN_READER)
                << std::right
                << "Reader Mobile Phone: "
                << std::left << reader._phone
            << std::endl
                << std::setw(LEFT_MARGIN_READER)
                << std::right
                << "Reader e-Mail: "
                << std::left
                << reader._email
            << std::endl
                << std::setw(LEFT_MARGIN_READER)
                << std::right
                << "Reader have arriars: "
                << std::left
                << answer
            << std::endl;
}
