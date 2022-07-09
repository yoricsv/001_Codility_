//
// Created by Yoric on 20-Feb-22.
//
#include "FileHandler.h"
#include <iostream>
//#include <cstdio>

// DEFINES FOR CONFIGURE AND CHECK //
Book   book;
Reader reader;

/**
char c;
std::string line;

if (!ptrFile)
    perror ("Ошибка открытия файлаn");
else
{
    do
    {
        c = getc(ptrFile);
        if (c == '$') counter++;
    }
    while (c != EOF);

    do
    {
        getline (ptrFile, line);
        if (c == '$') counter++;
    }
    while (c != EOF);

    fclose (ptrFile);
}
*/

       bool isFileOpen (
                   std::fstream & stream,
                     const char * path,
        std::ios_base::openmode   open_mode
    )
{
    stream.exceptions(std::ios::badbit);
    try
    {
        stream.open(
            path,
            open_mode
        );
        return true;
    }
    catch (const std::ios::failure & exception)
    {
        std::cerr
                << "\nERROR CODE: "             << exception.code()
                << "The file can't be opened "  << exception.what()
            << std::endl;
        return false;
    }
}
std::string convertUIntToString(unsigned int number)
{
    return
        static_cast<std::string>
        (
            reinterpret_cast<char *>
            (
                number
            )
        );
}

// WRITING IN FILE //
/** CREATE */
 int FilesHandler::createBookRecord()
{
    char confirm;
    std::fstream file;

    //    file.open(PATH_BOOK, std::ios::out | std::ios::app);

    if ( isFileOpen(
                file,
                PATH_BOOK,
                  std::fstream::out
                | std::fstream::app
            )
        )
    {
        do
        {
            clr_screen();

            Book::createBook();

            file.write(
                (char *) & book,
                sizeof(Book)
            );

            std::cout << "\n\nDo you want to add more (y/n?)";
            std::cin  >> confirm;
        }
        while(confirm == 'y' || confirm == 'Y');

        file.close();
    }

    return 0;
}
void FilesHandler::createReaderRecord()
{
    char confirm;
    std::fstream file;

    //    file.open(PATH_READER, std::ios::out | std::ios::app);

    if ( isFileOpen(
                file,
                PATH_READER,
                  std::fstream::out
                | std::fstream::app
            )
        )
    {
        do
        {
            reader.createReader();

            file.write(
                (char *) & reader,
                sizeof(Reader)
            );

            std::cout << "\n\nDo you want to add more (y/n?)";
            std::cin >> confirm;
        }
        while (confirm == 'y' || confirm == 'Y');

        file.close();
    }
}

// READING FROM FILE //
/** READ */
// Display books //
void FilesHandler::displayAllBooks()
{
    clr_screen();

    std::fstream file;

    if (    isFileOpen(
                file,
                "book.dat",
                std::fstream::in
            )
        )
    {
        std::cout
            << "\n\n\t\tBook LIST\n\n"
            << "===================================="
            << "====================================\n"
            << "Book Number"
            << std::setw(20)
            << "Book Name"
            << std::setw(25)
            << "Author \n"
            << "===================================="
            << "====================================\n";

        while ( file.read(
                    (char *) & book,
                    sizeof(Book)
                )
            )
            Book::showBook(book);

        file.close();
    }
}
void FilesHandler::displayBook(unsigned int number)
{
    std::cout << "\nBOOK DETAILS\n";
    std::fstream file;

    int flag = false;

    if (    isFileOpen(
                file,
                PATH_BOOK,
                std::fstream::in
            )
        )
    {
        while ( file.read(
                (char *) & book,
                sizeof(Book)
        )
                )
        {
            if ( !isStringTheSame(
                    convertUIntToString(Book::getBookID()),
                    convertUIntToString(number)
            )
                    )
            {
                Book::showBook(book);

                flag = true;
            }
        }

        file.close();

        if(!flag)
            std::cout << "\n\nBook does not exist";

        wait_enter();
    }
}
// Display book deposit  //
void FilesHandler::displayBookDeposit()
{
    unsigned int read_number;
    bool found = false,
            flag  = false;
    int day,
            fine;
    std::fstream file,
            file1;

    clr_screen();

    std::cout << "\n\nBOOK STORAGE ..."
              << "\n\n\tEnter The reader's admission no.";
    std::cin  >> read_number;

    file.open (PATH_READER, std::ios::in | std::ios::out);
    file1.open(PATH_BOOK,   std::ios::in | std::ios::out);

    while ( file.read(
            (char *) & reader,
            sizeof(Reader)
    )
            )
    {
        if (    !isStringTheSame(
                convertUIntToString(Reader::getReaderID()),
                convertUIntToString(read_number)
        )
                )
        {
            found = false;

            if(reader.getArriars() == 1)
            {
                while ( file1.read(
                        (char*) & book,
                        sizeof(Book)
                )
                        )
                {
                    if (    !isStringTheSame(
                            convertUIntToString(Book::getBookID()),
                            convertUIntToString(Reader::getReaderID())
                    )
                            )
                    {
                        Book::showBook(book);

                        flag = true;

                        std::cout << "\n\nBook storage in no. of days";
                        std::cin  >> day;

                        if(day > DAYS)
                        {
                            fine = (day - DAYS) * 1;

                            std::cout
                                    <<"\n\nFine has to store. "
                                    << fine;
                        }
                        reader.getArriars();

                        int pos = (-1) * static_cast<int>(sizeof(reader));

                        file.seekp(
                                pos,
                                std::ios::cur
                        );

                        file.write(
                                (char*) & reader,
                                sizeof(Reader)
                        );

                        std::cout << "\n\n\t Book stored successfully";
                    }
                }
                if(!flag)
                    std::cout << "Book no does not exist";
            }
            else
                std::cout << "No book is Issued!!";
        }
    }
    if(!found)
        std::cout << "Reader record Not exist...";

    file.close();
    file1.close();
    wait_enter();
}
// Display book issue  //
void FilesHandler::displayBookIssue()
{
    unsigned int read_number,
                 book_number;
            bool found = false,
                 flag  = false;
    std::fstream file,
                 file1;

    clr_screen();

    std::cout << "\n\nBOOK ISSUE ...";
    std::cout << "\n\n\tEnter The reader's admission no.";
    std::cin  >> read_number;

    file.open ("reader.dat", std::ios::in | std::ios::out);
    file1.open("book.dat",   std::ios::in | std::ios::out);

    while(file.read((char*) & reader, sizeof(Reader)) && found == 0)
    {
        if (    !isStringTheSame(
                convertUIntToString(Reader::getReaderID()),
                convertUIntToString(read_number)
        )
                )
        {
            found = true;
            if(reader.getArriars() == 0)
            {
                std::cout << "\n\n\tEnter the book no. ";
                std::cin >> book_number;

                while ( file1.read(
                            (char*) & book,
                            sizeof(Book)
                        )
                    )
                {
                    if (    !isStringTheSame(
                                convertUIntToString(Book::getBookID()),
                                convertUIntToString(book_number)
                            )
                        )
                    {
                        Book::showBook(book);

                        flag = true;

                        reader.setArrears();
//                        reader.setArrears(book.getBookID());

                        int pos = (-1) * static_cast<int>(sizeof(book));

                        file.seekp(pos, std::ios::cur);

                        file.write(
                                (char*) & reader,
                                sizeof(Reader)
                        );

                        std::cout
                            << "\n\n\t Book issued successfully\n\n"
                            << "Please Note: Write the current date"
                            << "\t\t\t\t"
                            << "in backside of your book and submit "
                            << "within 15 days fine Rs. 1 for each day"
                            << "\t\t\t\t"
                            << "after 15 days period";
                    }
                }
                if(!flag)
                    std::cout << "Book no does not exist";
            }
        }
        else
            std::cout << "You have not returned the last book ";
    }
    if(!found)
        std::cout << "reader record not exist";
    file.close();
    file1.close();
}
// Display readers //
void FilesHandler::displayAllReaders()
{
    std::fstream file;

    clr_screen();

    if (    isFileOpen(
                file,
                "reader.dat",
                std::fstream::in
            )
        )
    {
        std::cout
            << "================================="
            << "=================================\n"
            << "\tReader No."
            << std::setw(10)
            << "Name"
            << std::setw(20)
            << "Book Issued\n"
            << "================================="
            << "=================================\n";

        while ( file.read(
                    (char *) & reader,
                    sizeof(Reader)
                )
            )
            reader.showReader(reader);

        file.close();
    }
}
void FilesHandler::displayReader(unsigned int number)
{
    std::fstream file;
    std::cout << "\nReader details\n";

    int flag = false;

    if (    isFileOpen(
                file,
                PATH_READER,
                std::fstream::in
            )
        )
    {
        while ( file.read(
                    (char *) & reader,
                    sizeof(Reader)
                )
            )
        {
            if (    !isStringTheSame(
                        convertUIntToString(Reader::getReaderID()),
                        convertUIntToString(number)
                    )
                )
            {
                reader.showReader(reader);

                flag = true;
            }
        }
        file.close();

        if (!flag)
            std::cout << "\n\nReader does not exist";
    }
}

/** UPDATE */
void FilesHandler::editBook()
{
        unsigned number;
            bool found = false;
    std::fstream file;

    clr_screen();

    std::cout << "\n\n\tMODIFY BOOK RECORD.... "
              << "\n\n\tEnter Book no. :";

    std::cin  >> number;

    if (    isFileOpen(
                file,
                "book.dat",
                  std::fstream::in
                | std::fstream::out
            )
        )
    {
        while ( file.read(
                    (char *) & book,
                    sizeof(Book)
                )
            )
        {
            if (    !isStringTheSame(
                        convertUIntToString(Book::getBookID()),
                        convertUIntToString(number)
                    )
                )
            {
                Book::showBook(book);

                std::cout << "\nEnter The New Details of book\n";

                Book::editBook(book);

                int pos = (-1) * static_cast<int>(sizeof(book));

                file.seekp(
                    pos,
                    std::ios::cur
                );

                file.write(
                    (char *) & book,
                    sizeof(Book)
                );

                std::cout << "\n\n\t Record Updated";

                found = true;
            }
        }

        file.close();

        if (!found)
            std::cout << "\n\n Record Not Found ";
    }
}
void FilesHandler::editReader()
{
    unsigned int number;
            bool found = false;
    std::fstream file;

    clr_screen();

    std::cout << "\n\n\tMODIFY READER RECORD "
              << "\n\n\tEnter Reader No.";

    std::cin  >> number;

    if (    isFileOpen(
                file,
                PATH_READER,
                  std::fstream::in
                | std::fstream::out
            )
        )
    {
        while ( file.read(
                    (char *) & reader,
                    sizeof(Reader)
                )
            )
        {
            if (    !isStringTheSame(
                        convertUIntToString(Reader::getReaderID()),
                        convertUIntToString(number)
                    )
                )
            {
                reader.showReader(reader);

                std::cout << "\nEnter The New Details of reader\n";

                reader.editReader(reader);

                int pos = (-1) * static_cast<int>(sizeof(reader));

                file.seekp(pos, std::ios::cur);

                file.write((char *) &reader, sizeof(Reader));

                std::cout << "\n\n\t Record Updated";

                found = true;
            }
        }
        file.close();

        if (!found)
            std::cout << "\n\n Record Not Found ";
    }
}

/** DELETE */
void FilesHandler::deleteBook()
{
    unsigned int number;
    std::fstream file,
                 file2;

    clr_screen();

    std::cout << "\n\n\n\tDELETE BOOK ..."
              << "\n\nEnter The Book no. of the Book You Want To Delete : ";

    std::cin  >> number;

    if (    isFileOpen(
                file,
                "book.dat",
                std::fstream::in
                | std::fstream::out
            )
        &&  isFileOpen(
                file2,
                "Temp.dat",
                std::fstream::out
            )
        )
    {
        file.seekg(
            0,
            std::ios::beg
        );

        while ( file.read(
                    (char *) & book,
                    sizeof(Book)
                )
            )
        {
            if (    !isStringTheSame(
                        convertUIntToString(Book::getBookID()),
                        convertUIntToString(number)
                    )
                )
                file2.write(
                    (char *) & book,
                    sizeof(Book)
                );
        }
        file2.close();
        file.close();
    }

    remove("book.dat");
    rename(
            "Temp.dat",
            "book.dat"
    );

    std::cout << "\n\n\tRecord Deleted ..";
}
void FilesHandler::deleteReader()
{
    unsigned int number;
            bool flag = false;
    std::fstream file,
                 file2;

    clr_screen();

    std::cout << "\n\n\n\tDELETE Reader..."
              << "\n\nEnter The Reader No. You Want To Delete : ";

    std::cin  >> number;

    if (   isFileOpen(
               file,
               PATH_READER,
                 std::fstream::in
               | std::fstream::out
           )
        && isFileOpen(
                file2,
                "Temp.dat",
                std::fstream::out
           )
        )
    {
        file.seekg(
            0,
            std::ios::beg
        );

        while ( file.read(
                    (char *) & reader,
                    sizeof(Reader)
                )
            )
        {
            if (    !isStringTheSame(
                        convertUIntToString(Reader::getReaderID()),
                        convertUIntToString(number)
                    )
                )
                file2.write(
                    (char *) & reader,
                    sizeof(Reader)
                );
            else
                flag = true;
        }

        file2.close();
        file.close();
    }


    if(!remove("ReaderDB.dat"))
        perror("Error deleting file");
    else
        puts("File successfully deleted");


    if(!rename("Temp.dat", "ReaderDB.dat"))
        perror("Error while renaming file");
    else
        puts( "File successfully renamed!" );


    if(!flag)
        std::cout << "\n\nRecord not found";
    else
        std::cout << "\n\n\tRecord Deleted ..";
}








