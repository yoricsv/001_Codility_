//
// Created by Yoric on 20-Feb-22.
//
#pragma once
#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <limits>

#include "CheckEntry.h"
#include "Book.h"
#include "BookCard.h"
#include "Library.h"
#include "Reader.h"


#define SOLID_LINE      std::cout << "======================================================================================================================" << std::endl;
#define SEPARATOR_LINE  std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;

#define MENU_SOLID_LINE std::cout << std::setw(84) << std::right << "===================================================" << std::endl;
#define MENU_SEPARATOR  std::cout << std::setw(84) << std::right << "---------------------------------------------------" << std::endl;

#define CARD_SOLID_LINE std::cout << std::setw(84) << std::right << "***************************************************" << std::endl;
#define CARD_SEPARATOR  std::cout << std::setw(84) << std::right << "* - - - - - - - - - - - - - - - - - - - - - - - - *" << std::endl;
#define CARD_FREE_LINE  std::cout << std::setw(34) << std::right << "*" << std::setw(50) << "*" << std::endl;

#define INDENT_BANNER           std::cout << std::setw(76) <<
#define INDENT_MENU             std::cout << std::setw(38) <<

#define INDENT_CARD_LEFT        std::cout << std::setw(36) << std::right << "*  " << std::setw(15) <<
#define INDENT_CARD_CENTER      << std::setw(32) << std::left <<
#define INDENT_CARD_RIGHT       << "*" << std::endl;

#define INDENT_HEADER_LEFT      std::cout << "|" << std::setw(70) <<
#define INDENT_HEADER_RIGHT     << std::setw(47) << "|" << std::endl;

#define INDENT_HEAD_CARD_LEFT   std::cout << std::setw(36) << std::right << "*  " << std::setw(25) <<
#define INDENT_HEAD_CARD_CENTER << std::setw(22) << std::left <<

#define ENDLINE                 << std::endl;


enum PROG_STATE
{
    BOOK_ISSUE = 1,
    BOOK_STORAGE,
    READERS_LIST,
    LIBRARY_MANAGE,
    EXIT_LIBRARY = 0
};
enum SELECTOR
{
    SORT_AUTHOR = 1,
    SORT_TITLE,
    SORT_READER_NAME,
    SORT_RETURN_DATE,

    RETURN_PREV_MENU,

    SORT_YEAR = 3,
    SORT_NAME = 1,
    SORT_PHONE,
    SORT_EMAIL,
    SORT_DOB
};

enum ACTION
{
    MAIN_MENU,
    ADD_BOOK = 11,
    REMOVE_BOOK,
    SHOW_NUMBER_OF_BOOKS,
    SHOW_INFO_OF_BOOK,
    SHOW_LIST_OF_BOOKS,

    EXIT = 0
};

// UTILITES //
inline void wait_enter        ();             // PROGRAM DELAY //
void clr_screen        ();             // CLEAR COMMAND PROMP SCREEN //


void welcome_banner           ();             // HELLO BANNER //

void menuMain_Actions         ();             // MAIN MENU //

int mainMenu_switcher        (int select);   // MAIN MENU SELECTOR //


void menu_BookIssueTable      ();             // BOOK INTO THE ISSUE TABLE BRANCH MENUS //
void ptrn_BookIssueTable      ();
void menu_BookIssueActions    ();

int bookIssueMenu_switcher   (int select);   // MAIN MENU SELECTOR //

void menu_BookStorageTable    ();             // BOOK STORAGE TABLE MENUS //
void ptrn_BookStorageTable    ();
void menu_BookStorageActions  ();

int bookStorageMenu_switcher (int select);   // BOOK STORAGE MENU SELECTOR //

void menu_ReadersTable        (Reader &readObj);             // ALL READERS TABLE MENUS //
void ptrn_ReadersTable        (Reader &readObj);
void menu_ReadersActions      ();

int readersMenu_switcher     (int select, Reader &readObj);   // READER MENU SELECTOR //

void menu_ReaderCard          ();             // READER CARD MENUS //
void ptrn_ReaderCard          ();
void menu_ReaderCardAction    ();

int readerCardMenu_switcher  (int select);    // READER CARD MENU SELECTOR //

void menu_BookCard            ();             // BOOK CARD MENUS //
void ptrn_BookCard            ();
void menu_BookCardAction      ();

void menu_Management          ();             // MANAGEMENT MENUS //
void ptrn_Management          ();
void menu_ManagementAction    ();


int mainMenu                 ();
bool menu_Handler             (int option, Library & libObj);
void addBookInformation       (Library &libObj);
void removeBook               (Library &libObj);
void displayBook              (Library &libObj);


#endif //MENU_H
