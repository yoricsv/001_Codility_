//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include <iostream>
#include <fstream>
#include <cstdio>

#include "Book.h"
#include "CheckEntry.h"
#include "Reader.h"
#include "Menu.h"

const int DAYS = 15;

class FilesHandler
{
public:
    FilesHandler() = default;
    ~FilesHandler() = default;

    /** CREATE */
     int createBookRecord();
    void createReaderRecord();

    /** READ */
    // Display books //
    void displayAllBooks();
    void displayBook(unsigned int number);
    void displayBookDeposit();
    void displayBookIssue();

    // Display readers //
    void displayAllReaders();
    void displayReader(unsigned int number);

    /** UPDATE */
    void editBook       ();
    void editReader     ();

    /** DELETE */
    void deleteBook();
    void deleteReader();


private:
    std::string _path = "";
};


/**
// WRITTING IN FILE HANDLER //
int write_book()
{
    char confirm;
    std::fstream file;

    file.open(PATH_BOOK, std::ios::out | std::ios::app);
    if (!file)
        perror ("The file was not open!");
    else
    {
        do
        {
            clr_screen();

            book.createBook();

            file.write((char *) & book, sizeof(Book));
            std::cout << "\n\nDo you want to add more record..(y/n?)";
            std::cin  >> confirm;
        }
        while(confirm == 'y' || confirm == 'Y');

        file.close();
    }
    return 0;
}
void write_reader()
{
    char confirm;
    std::fstream file;

    file.open(PATH_READER, std::ios::out | std::ios::app);
    do
    {
        readR.createReader();

        file.write((char*) & readR, sizeof(Reader));
        std::cout << "\n\ndo you want to add more record..(y/n?)";
        std::cin  >> confirm;
    }
    while(confirm == 'y' || confirm == 'Y');

    file.close();
}

// READING FROM FILE HANDLER //
void display_spb(unsigned number)
{
    std::cout << "\nBOOK DETAILS\n";
    std::fstream file;
    int flag = 0;

    file.open(PATH_BOOK, std::ios::in);

    while(file.read((char*) & book, sizeof(Book)))
    {
        if(!compareString(book.getBookID(), number))
        {
            book.showBook(book);
            flag = 1;
        }
    }

    file.close();

    if(!flag)
        std::cout << "\n\nBook does not exist";
    wait_enter();
}
void display_sps(unsigned number)
{
    std::fstream file;
    std::cout << "\nreader DETAILS\n";

    int flag = 0;

    file.open("ReaderDB.dat", std::ios::in);
    while(file.read((char*) & readR, sizeof(Reader)))
    {
        if(!compareString(readR.getReaderID(), number))
        {
            readR.showReader(readR);
            flag = 1;
        }
    }

    file.close();

    if(!flag)
        std::cout << "\n\nreader does not exist";

//    getch();
}

// MODIFIER RECORDS IN FILE //
void modify_book()
{
    unsigned number;
    int found = 0;
    std::fstream file;

    clr_screen();
    std::cout << "\n\n\tMODIFY BOOK REORD.... ";
    std::cout << "\n\n\tEnter The book no. of The book";
    std::cin  >> number;

    file.open("book.dat", std::ios::in | std::ios::out);
    while(file.read((char*) & book, sizeof(Book)) && found == 0)
    {
        if(!compareString(book.getBookID(), number))
        {
            book.showBook(book);

            std::cout << "\nEnter The New Details of book" << std::endl;
            book.editBook(book);

            int pos = (-1) * static_cast<int>(sizeof(book));
            file.seekp(pos, std::ios::cur);
            file.write((char*) & book, sizeof(Book));

            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    file.close();

    if(!found)
        std::cout << "\n\n Record Not Found ";

//	getch();
}
void editReader()
{
    unsigned number;
    int  found = 0;
    std::fstream file;

    clr_screen();

    std::cout << "\n\n\tMODIFY READER RECORD... ";
    std::cout << "\n\n\tEnter The Reader No.";
    std::cin  >> number;

    file.open(PATH_READER, std::ios::in | std::ios::out);
    while(file.read((char*) & readR, sizeof(Reader)) && found == 0)
    {
        if(!compareString(readR.getReaderID(), number))
        {
            readR.showReader(readR);

            std::cout<<"\nEnter The New Details of reader"<<std::endl;

            readR.editReader(readR);

            int pos = (-1) * static_cast<int>(sizeof(readR));
            file.seekp(pos, std::ios::cur);
            file.write((char*) & readR, sizeof(Reader));

            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    file.close();

    if(found == 0)
        std::cout << "\n\n Record Not Found ";

//    getch();
}

// DELETER RECORDS IN FILE //
void delete_reader()
{
    unsigned number;
    int  flag = 0;
    std::fstream file,file2;

    clr_screen();

    std::cout << "\n\n\n\tDELETE Reader...";
    std::cout << "\n\nEnter The Reader No. You Want To Delete : ";
    std::cin  >> number;

    file.open(PATH_READER, std::ios::in | std::ios::out);

    file2.open("Temp.dat",std::ios::out);
    file.seekg(0, std::ios::beg);

    while(file.read((char*) & readR, sizeof(Reader)))
    {
        if(!compareString(readR.getReaderID(), number))
            file2.write((char*) & readR, sizeof(Reader));
        else
            flag = 1;
    }

    file2.close();
    file.close();

    if(remove("ReaderDB.dat"))
        perror("Error deleting file");
    else
        puts("File successfully deleted");

    if(rename("Temp.dat", "ReaderDB.dat"))
        perror("Error while renaming file");
    else
        puts( "File successfully renamed!" );

    if(flag == 1)
        std::cout << "\n\n\tRecord Deleted ..";
    else
        std::cout << "\n\nRecord not found";
//	getch();
}
void delete_book()
{
    unsigned  number;
    std::fstream file, file2;

    clr_screen();

    std::cout << "\n\n\n\tDELETE BOOK ...";
    std::cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    std::cin  >> number;

    file.open("book.dat", std::ios::in | std::ios::out);


    file2.open("Temp.dat", std::ios::out);
    file.seekg(0, std::ios::beg);

    while(file.read((char*) & book,sizeof(Book)))
    {
        if(!compareString(book.getBookID(), number))
        {
            file2.write((char*) & book, sizeof(Book));
        }
    }

    file2.close();
    file.close();

    remove("book.dat");
    rename("Temp.dat", "book.dat");

    std::cout << "\n\n\tRecord Deleted ..";
//	getch();
}

// DISPLAY ALL readerS LIST HANDLER //
void display_alls()
{
    std::fstream file;
    clr_screen();

    file.open("reader.dat", std::ios::in);
    if(!file)
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPEN ";
//		getch();
        return;
    }

    std::cout << "==================================================================\n";
    std::cout << "\tReader No." << std::setw(10) << "Name" << std::setw(20) << "Book Issued\n";
    std::cout << "==================================================================\n";

    while(file.read((char*) & readR, sizeof(Reader)))
    {
        readR.showReader(readR);
    }

    file.close();
    //   getch();
}

// DISPLAY BOOKS LIST HANDLER //
void display_allb()
{
    clr_screen();
    std::fstream file;

    file.open("book.dat", std::ios::in);
    if(!file)
    {
        std::cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        wait_enter();
        return;
    }

    std::cout << "\n\n\t\tBook LIST\n\n";
    std::cout << "=========================================================================\n";
    std::cout << "Book Number" << std::setw(20) << "Book Name" << std::setw(25) << "Author \n";
    std::cout << "=========================================================================\n";

    while(file.read((char*) & book, sizeof(Book)))
    {
        book.showBook(book);
    }
    file.close();
//	getch();
}

// HANDLER OF DISPLAY ISSUE BOOK //
void book_issue()
{
    unsigned read_number,
            book_number;
    int  found = 0,
            flag = 0;
    std::fstream file, file1;
    clr_screen();

    std::cout << "\n\nBOOK ISSUE ...";
    std::cout << "\n\n\tEnter The reader's admission no.";
    std::cin  >> read_number;

    file.open ("reader.dat", std::ios::in | std::ios::out);
    file1.open("book.dat",    std::ios::in | std::ios::out);

    while(file.read((char*) & readR, sizeof(Reader)) && found == 0)
    {
        if(!compareString(readR.getReaderID(), read_number))
        {
            found = 1;
            if(readR.getArriars() == 0)
            {
                std::cout << "\n\n\tEnter the book no. ";
                std::cin >> book_number;

                while(file1.read((char*) & book, sizeof(Book)) && flag == 0)
                {
                    if(!compareString(book.getBookID(), book_number))
                    {
                        book.showBook(book);
                        flag = 1;
                        readR.setArriars();
//                        readR.setArriars(book.getBookID());
                        int pos = (-1) * static_cast<int>(sizeof(book));
                        file.seekp(pos, std::ios::cur);
                        file.write((char*) & readR, sizeof(Reader));

                        std::cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write the current date 						in backside of your book and submit within 15 days fine Rs. 1 for each day 							after 15 days period";
                    }
                }
                if(flag == 0)
                    std::cout << "Book no does not exist";
            }
        }
        else
            std::cout << "You have not returned the last book ";
    }
    if(found == 0)
        std::cout << "reader record not exist...";
//	getch();
    file.close();
    file1.close();
}

// HANDLER OF DEPOSIT BOOK //
void book_deposit()
{
    unsigned read_number;
    int  found = 0,
            flag  = 0,
            day,
            fine;
    std::fstream file, file1;

    clr_screen();

    std::cout << "\n\nBOOK STORAGE ...";
    std::cout << "\n\n\tEnter The reader's admission no.";
    std::cin  >> read_number;

    file.open (PATH_READER, std::ios::in | std::ios::out);
    file1.open(PATH_BOOK,   std::ios::in | std::ios::out);
    while(file.read((char*) & readR, sizeof(Reader)) && found == 0)
    {
        if(!compareString(readR.getReaderID(), read_number))
        {
            found = 1;
            if(readR.getArriars() == 1)
            {
                while(file1.read((char*) & book, sizeof(Book)) && flag == 0)
                {
                    if(!compareString(book.getBookID(), readR.getReaderID()))
                    {
                        book.showBook(book);
                        flag = 1;
                        std::cout << "\n\nBook storage in no. of days";
                        std::cin  >> day;
                        if(day > DAYS)
                        {
                            fine=(day - DAYS)*1;
                            std::cout<<"\n\nFine has to store. "<<fine;
                        }
                        readR.getArriars();
                        int pos = (-1) * static_cast<int>(sizeof(readR));
                        file.seekp(pos, std::ios::cur);
                        file.write((char*) & readR, sizeof(Reader));

                        std::cout << "\n\n\t Book stored successfully";
                    }
                }
                if(flag == 0)
                    std::cout << "Book no does not exist";
            }
            else
                std::cout << "No book is Issued!!";
        }
    }
    if(found == 0)
        std::cout << "Reader record Not exist...";
    wait_enter();
    file.close();
    file1.close();
}
*/

#endif //FILE_HANDLER_H
