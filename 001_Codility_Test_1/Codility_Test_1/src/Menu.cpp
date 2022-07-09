//
// Created by Yoric on 20-Feb-22.
//
#include "Menu.h"


int prog_state      = 0;
int action          = 0;
int selector        = 0;
int selected_action = 0;
bool quit_lib        = false;

// TEMP FOR CONFIGURATE Begin //
size_t readerID        = 23252463635;// READER CARD MENUS //
bool arrears         = true;       // READER CARD MENUS //

size_t bookID          = 2325;       // BOOK CARD MENUS //
bool onStock         = true;       // BOOK CARD MENUS //
int returnDay       = 5;          // BOOK CARD MENUS //
int currentDay      = 6;          // BOOK CARD MENUS //

bool file_BookIssue  = true;       // BOOK INTO THE ISSUE TABLE MENUS //
// TEMP FOR CONFIGURATE End //

// HELLO BANNER //
void welcome_banner()
{
    static int banner_counter = 0;
    if(!banner_counter)
    {
        std::cout                                           ENDLINE
        INDENT_BANNER "********************************"    ENDLINE
        INDENT_BANNER "***  WELCOME TO THE LIBRARY  ***"    ENDLINE
        INDENT_BANNER "********************************"    ENDLINE
        std::cout                                           ENDLINE
    }
    banner_counter++;

    if(quit_lib)
    {
        std::cout                                           ENDLINE
        INDENT_BANNER "********************************"    ENDLINE
        INDENT_BANNER "***     HAVE A NICE DAY!     ***"    ENDLINE
        INDENT_BANNER "********************************"    ENDLINE
        std::cout                                           ENDLINE
    }
}

// MAIN MENU //
void menuMain_Actions()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  BOOKS INTO THE ISSUE"            ENDLINE
    INDENT_MENU "2:" << "  BOOKS IN THE STORAGE"            ENDLINE
    INDENT_MENU "3:" << "  LIST OF THE READERS"             ENDLINE
    INDENT_MENU "4:" << "  LIBRARY MANAGEMENT"              ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "0:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}
// MAIN MENU SELECTOR //
int mainMenu_switcher(int select)
{
    switch(select)
    {
        case(BOOK_ISSUE):     prog_state = BOOK_ISSUE;     return prog_state; break;
        case(BOOK_STORAGE):   prog_state = BOOK_STORAGE;   return prog_state; break;
        case(READERS_LIST):   prog_state = READERS_LIST;   return prog_state; break;
        case(LIBRARY_MANAGE): prog_state = LIBRARY_MANAGE; return prog_state; break;
        case(EXIT_LIBRARY):   prog_state = EXIT_LIBRARY;   return prog_state; break;
        default:              mainMenu();                  return prog_state; break;
    }
}

// BOOK INTO THE ISSUE TABLE MENUS //
void menu_BookIssueTable()
{
    clr_screen();
    SOLID_LINE INDENT_HEADER_LEFT " *** BOOKS INTO THE ISSUE ***" INDENT_HEADER_RIGHT SOLID_LINE

    std::cout   << "|" << std::setw(3)  << " No."
                << "|" << std::setw(19) << ""
                << "|" << std::setw(40) << ""
                << "|" << std::setw(5)  << "No. "
                << "|" << std::setw(24) << ""
                << "|" << std::setw(9)  << "Return  "
                << "|" << std::setw(9)  << ""
                << "|" << std::endl;
    std::cout   << "|" << std::setw(4)  << "Book"
                << "|" << std::setw(13) << "Author"      << std::setw(7)
                << "|" << std::setw(26) << "Book Title"  << std::setw(15)
                << "|" << std::setw(5)  << "Read."
                << "|" << std::setw(17) << "Reader Name" << std::setw(8)
                << "|" << std::setw(9)  << "Date  "
                << "|" << std::setw(9)  << "Overdue?"
                << "|" << std::endl;

    ptrn_BookIssueTable();  // PATTERN for book issue table
    SOLID_LINE

    menu_BookIssueActions();
}
void ptrn_BookIssueTable()    // OUTPUT PATTERN FOR BOOK ISSUE TABLE //
{
    SEPARATOR_LINE
    std::cout   << "|" << std::setw(5)    // Book No.
                << "|" << std::setw(20)   // Author
                << "|" << std::setw(41)   // Book Title
                << "|" << std::setw(6)    // Reader No.
                << "|" << std::setw(25)   // Reader Name
                << "|" << std::setw(10)   // Return Date
                << "|" << std::setw(10)   // Overdue Debt
                << "|" << std::endl;
}
void menu_BookIssueActions()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  Sort by Author"                  ENDLINE
    INDENT_MENU "2:" << "  Sort by Title"                   ENDLINE
    INDENT_MENU "3:" << "  Sort by Reader Name"             ENDLINE
    INDENT_MENU "4:" << "  Sort by The Day Of Return"       ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "5:" << "  Return to the previous menu"     ENDLINE
    INDENT_MENU "6:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}
// MAIN MENU SELECTOR //
int bookIssueMenu_switcher(int select)
{
    switch(select)
    {
        case(SORT_AUTHOR):      prog_state = SORT_AUTHOR;      return prog_state; break;
        case(SORT_TITLE):       prog_state = SORT_TITLE;       return prog_state; break;
        case(SORT_READER_NAME): prog_state = SORT_READER_NAME; return prog_state; break;
        case(SORT_RETURN_DATE): prog_state = SORT_RETURN_DATE; return prog_state; break;
        case(RETURN_PREV_MENU): prog_state = RETURN_PREV_MENU; return prog_state; break;
        case(EXIT_LIBRARY):     prog_state = EXIT_LIBRARY;     return prog_state; break;
        default:                menu_BookIssueTable();         return prog_state; break;
    }
}
// BOOK STORAGE TABLE MENUS //
void menu_BookStorageTable()
{
    clr_screen();
    SOLID_LINE INDENT_HEADER_LEFT " *** BOOKS IN THE STORAGE ***" INDENT_HEADER_RIGHT SOLID_LINE

    std::cout   << "|" << std::setw(3)  << " No."
                << "|" << std::setw(19) << ""
                << "|" << std::setw(81) << ""
                << "|" << std::setw(9) << "Published"
                << "|" << std::endl;
    std::cout   << "|" << std::setw(4)  << "Book"
                << "|" << std::setw(13) << "Author"      << std::setw(7)
                << "|" << std::setw(44) << "Book Title"  << std::setw(38)
                << "|" << std::setw(9)  << "year  "
                << "|" << std::endl;

    ptrn_BookStorageTable();  // PATTERN for book storage table
    SOLID_LINE

    menu_BookStorageActions();
}
void ptrn_BookStorageTable() // OUTPUT PATTERN FOR BOOK STORAGE TABLE //
{
    SEPARATOR_LINE
    std::cout   << "|" << std::setw(5)    // Book No.
                << "|" << std::setw(20)   // Author
                << "|" << std::setw(82)   // Book Title
                << "|" << std::setw(10)   // Published in
                << "|" << std::endl;
}
void menu_BookStorageActions()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  Sort by Author"                  ENDLINE
    INDENT_MENU "2:" << "  Sort by Title"                   ENDLINE
    INDENT_MENU "3:" << "  Sort by Published"               ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "5:" << "  Return to the previous menu"     ENDLINE
    INDENT_MENU "0:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}
// BOOK STORAGE MENU SELECTOR //
int bookStorageMenu_switcher(int select)
{
    switch(select)
    {
        case(SORT_AUTHOR):      prog_state = SORT_AUTHOR;      return prog_state; break;
        case(SORT_TITLE):       prog_state = SORT_TITLE;       return prog_state; break;
        case(SORT_YEAR):        prog_state = SORT_YEAR;        return prog_state; break;
        case(RETURN_PREV_MENU): prog_state = RETURN_PREV_MENU; return prog_state; break;
        case(EXIT_LIBRARY):     prog_state = RETURN_PREV_MENU; return prog_state; break;
        default:                menu_BookStorageTable();       return prog_state; break;
    }
}

// ALL READERS TABLE MENUS //
void menu_ReadersTable(Reader &readObj)
{
    clr_screen();
    SOLID_LINE INDENT_HEADER_LEFT " *** LIST OF READERS ***" INDENT_HEADER_RIGHT SOLID_LINE

    std::cout   << "|" << std::setw(3)  << "Read"
                << "|" << std::setw(32) << ""
                << "|" << std::setw(9)  << "Day Of"  << std::setw(3)
                << "|" << std::setw(17) << ""
                << "|" << std::setw(48) << ""
                << "|" << std::endl;
    std::cout   << "|" << std::setw(4)  << "No."
                << "|" << std::setw(17) << "Name"   << std::setw(16)
                << "|" << std::setw(8)  << "Birth"  << std::setw(4)
                << "|" << std::setw(12) << "Phone " << std::setw(6)
                << "|" << std::setw(25) << "e-mail" << std::setw(24)
                << "|" << std::endl;
    ptrn_ReadersTable(readObj);  // PATTERN for book storage table
    SOLID_LINE

    menu_ReadersActions();
}
void ptrn_ReadersTable(Reader & readObj) // OUTPUT PATTERN FOR BOOK STORAGE TABLE //
{
    SEPARATOR_LINE
    std::cout << "|" << std::setw(5)  << readObj.getReaderID()// ReaderID
              << "|" << std::setw(33) << readObj.isName()     // Reader Name
              << "|" << std::setw(12) << readObj.isBirthDay() // Day Of Birth
              << "|" << std::setw(18) << readObj.isPhone()    // Phone
              << "|" << std::setw(49) << readObj.isEMail()    // e-Mail
              << "|" << std::endl;
}
void menu_ReadersActions()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  Sort by Name"                    ENDLINE
    INDENT_MENU "2:" << "  Sort by Phone"                   ENDLINE
    INDENT_MENU "3:" << "  Sort by E-mail"                  ENDLINE
    INDENT_MENU "4:" << "  Sort by Day Of Birthday"         ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "5:" << "  Return to the previous menu"     ENDLINE
    INDENT_MENU "6:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}
// BOOK STORAGE MENU SELECTOR //
int readersMenu_switcher(int select, Reader &readObj)
{
    switch(select)
    {
        case(SORT_NAME):        prog_state = SORT_NAME;        return prog_state; break;
        case(SORT_PHONE):       prog_state = SORT_PHONE;       return prog_state; break;
        case(SORT_EMAIL):       prog_state = SORT_EMAIL;       return prog_state; break;
        case(SORT_DOB):         prog_state = SORT_DOB;         return prog_state; break;
        case(RETURN_PREV_MENU): prog_state = RETURN_PREV_MENU; return prog_state; break;
        case(EXIT_LIBRARY):     prog_state = RETURN_PREV_MENU; return prog_state; break;
        default:                menu_ReadersTable(readObj);           return prog_state; break;
    }
}
// READER CARD MENUS //
void menu_ReaderCard()
{
    clr_screen();
    CARD_SOLID_LINE INDENT_HEAD_CARD_LEFT "READER CARD No.: " INDENT_HEAD_CARD_CENTER readerID INDENT_CARD_RIGHT CARD_SOLID_LINE

    CARD_FREE_LINE
    INDENT_CARD_LEFT  "READER NAME:  " INDENT_CARD_CENTER "Ivanov Ivan Stepanovych" INDENT_CARD_RIGHT
    CARD_FREE_LINE
    INDENT_CARD_LEFT "DAY OF BIRTH:  " INDENT_CARD_CENTER "25.07.1995"              INDENT_CARD_RIGHT
    CARD_FREE_LINE
    INDENT_CARD_LEFT        "PHONE:  " INDENT_CARD_CENTER "+7(965)845-17-50"        INDENT_CARD_RIGHT
    CARD_FREE_LINE
    INDENT_CARD_LEFT       "E-MAIL:  " INDENT_CARD_CENTER "anymail35@gmail.com"     INDENT_CARD_RIGHT
    CARD_FREE_LINE
    CARD_SEPARATOR

    ptrn_ReaderCard();  // PATTERN for reader card

    menu_ReaderCardAction();
}
void ptrn_ReaderCard() // OUTPUT PATTERN FOR READER CARD //
{
    if(arrears)
    {
        CARD_FREE_LINE
        INDENT_CARD_LEFT      "Arrears:  " INDENT_CARD_CENTER "YES"                         INDENT_CARD_RIGHT
        INDENT_CARD_LEFT     "Book No.:  " INDENT_CARD_CENTER "56"                          INDENT_CARD_RIGHT
        INDENT_CARD_LEFT  "Return Date:  " INDENT_CARD_CENTER "09.03.2021"                  INDENT_CARD_RIGHT
        INDENT_CARD_LEFT "Is OVERDUE ?:  " INDENT_CARD_CENTER "You should call the reader!" INDENT_CARD_RIGHT
        CARD_FREE_LINE
    }
    else
    {
        CARD_FREE_LINE
        INDENT_CARD_LEFT      "Arrears:  " INDENT_CARD_CENTER "The reader has no debt"      INDENT_CARD_RIGHT
        CARD_FREE_LINE
    }
    CARD_SOLID_LINE
}
void menu_ReaderCardAction()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  Modify Reader Card"              ENDLINE
    INDENT_MENU "2:" << "  Remove Reader Card"              ENDLINE
    INDENT_MENU "3:" << "  Add a book to debt"              ENDLINE
    INDENT_MENU "4:" << "  Remove a book from debt"         ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "5:" << "  Return to the previous menu"     ENDLINE
    INDENT_MENU "6:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}
// READER CARD MENU SELECTOR //
int readerCardMenu_switcher(int select)
{
    switch(select)
    {
        case(SORT_NAME):        prog_state = SORT_NAME;        return prog_state; break;
        case(SORT_PHONE):       prog_state = SORT_PHONE;       return prog_state; break;
        case(SORT_EMAIL):       prog_state = SORT_EMAIL;       return prog_state; break;
        case(SORT_DOB):         prog_state = SORT_DOB;         return prog_state; break;
        case(RETURN_PREV_MENU): prog_state = RETURN_PREV_MENU; return prog_state; break;
        case(EXIT_LIBRARY):     prog_state = RETURN_PREV_MENU; return prog_state; break;
        default:                menu_ReaderCard();             return prog_state; break;
    }
}
// BOOK CARD MENUS //
void menu_BookCard()
{
    clr_screen();
    CARD_SOLID_LINE INDENT_HEAD_CARD_LEFT "BOOK CARD No.: " INDENT_HEAD_CARD_CENTER bookID INDENT_CARD_RIGHT CARD_SOLID_LINE

    CARD_FREE_LINE
    INDENT_CARD_LEFT "WRITTER:  " INDENT_CARD_CENTER "A.S. Griboyedov"              INDENT_CARD_RIGHT
    CARD_FREE_LINE
    INDENT_CARD_LEFT   "TITLE:  " INDENT_CARD_CENTER "Gore ot uma (Wit Works Woe)"  INDENT_CARD_RIGHT
    CARD_FREE_LINE
    INDENT_CARD_LEFT    "YEAR:  " INDENT_CARD_CENTER "1825"                         INDENT_CARD_RIGHT
    CARD_FREE_LINE
    CARD_SEPARATOR

    ptrn_BookCard();  // PATTERN for reader card

    menu_BookCardAction();
}
void ptrn_BookCard() // OUTPUT PATTERN FOR READER CARD //
{
    if(!onStock)
    {
        CARD_FREE_LINE
        INDENT_CARD_LEFT     "Storage:  " INDENT_CARD_CENTER "Lended Out"           INDENT_CARD_RIGHT
        INDENT_CARD_LEFT  "Reader No.:  " INDENT_CARD_CENTER "56"                   INDENT_CARD_RIGHT
        INDENT_CARD_LEFT "Return Date:  " INDENT_CARD_CENTER "09.03.2021"           INDENT_CARD_RIGHT
        if(returnDay < currentDay)
            INDENT_CARD_LEFT "Overdue:  " INDENT_CARD_CENTER "Return time is OVER!" INDENT_CARD_RIGHT
        else
            INDENT_CARD_LEFT "Overdue:  " INDENT_CARD_CENTER "Don't panic)"         INDENT_CARD_RIGHT
        CARD_FREE_LINE
    }
    else
    {
        CARD_FREE_LINE
        INDENT_CARD_LEFT     "Storage:  " INDENT_CARD_CENTER "On Stock"             INDENT_CARD_RIGHT
        CARD_FREE_LINE
    }
    CARD_SOLID_LINE
}
void menu_BookCardAction()
{
    MENU_SOLID_LINE
    INDENT_MENU "1:" << "  Add Book"                        ENDLINE
    INDENT_MENU "2:" << "  Edit Book Card"                  ENDLINE
    INDENT_MENU "3:" << "  Remove Book Card"                ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "4:" << "  Return to the previous menu"     ENDLINE
    INDENT_MENU "5:" << "  Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}

// MANAGEMENT MENUS //
void menu_Management()
{
    clr_screen();
    CARD_SOLID_LINE
    INDENT_HEAD_CARD_LEFT "LIBRARY MANAGEMENT" INDENT_HEAD_CARD_CENTER "" INDENT_CARD_RIGHT
    CARD_SOLID_LINE

    ptrn_Management();  // PATTERN for management

    menu_ManagementAction();
}
void ptrn_Management() // OUTPUT PATTERN FOR MANAGEMENT //
{
    INDENT_CARD_LEFT  "1:  " INDENT_CARD_CENTER "Book Add"            INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "2:  " INDENT_CARD_CENTER "Book Edit"           INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "3:  " INDENT_CARD_CENTER "Book Remove"         INDENT_CARD_RIGHT
    CARD_SEPARATOR
    INDENT_CARD_LEFT  "4:  " INDENT_CARD_CENTER "Reader Add"          INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "5:  " INDENT_CARD_CENTER "Reader Edit"         INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "6:  " INDENT_CARD_CENTER "Reader Remove"       INDENT_CARD_RIGHT
    CARD_SEPARATOR
    INDENT_CARD_LEFT  "7:  " INDENT_CARD_CENTER "Issue Add"           INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "8:  " INDENT_CARD_CENTER "Issue Edit"          INDENT_CARD_RIGHT
    INDENT_CARD_LEFT  "9:  " INDENT_CARD_CENTER "Issue Remove"        INDENT_CARD_RIGHT
    CARD_SEPARATOR
    INDENT_CARD_LEFT "10:  " INDENT_CARD_CENTER "Overdue Debt Edit"   INDENT_CARD_RIGHT
    INDENT_CARD_LEFT "11:  " INDENT_CARD_CENTER "Overdue Debt Remove" INDENT_CARD_RIGHT
    CARD_SOLID_LINE
}
void menu_ManagementAction()
{
    MENU_SOLID_LINE
    INDENT_MENU "12:" << " Get Info about Books"            ENDLINE
    INDENT_MENU "13:" << " Get Info about Readers"          ENDLINE
    INDENT_MENU "14:" << " Get Info about Issue"            ENDLINE
    INDENT_MENU "15:" << " Get Info about Overdue"          ENDLINE
    MENU_SEPARATOR
    INDENT_MENU "16:" << " Return to the previous menu"     ENDLINE
    INDENT_MENU "17:" << " Exiting the library"             ENDLINE
    MENU_SOLID_LINE
}




// UTILITIES BEGIN //
void clr_screen()
{
    if(system("cls")) system("clear"); // clear CMD linux/mac
    else              system("cls");   // clear CMD window
}
void wait_enter()
{
    std::string tmp;
    std::cout << "Press 'Enter' to continue..." ENDLINE
    std::getline(std::cin, tmp);
    clr_screen();
}
// UTILITIES END//



int mainMenu()
{
    welcome_banner();

    menuMain_Actions();
    check_enterNumber();
    mainMenu_switcher(selector);

    return prog_state;
}

//    std::cout << "===================================================="                 << std::endl;
//    std::cout << std::setw(4) << "1:" << " Add a book to the library"                   << std::endl;
//    std::cout << std::setw(4) << "2:" << " Remove book from the library"                << std::endl;
//    std::cout << std::setw(4) << "3:" << " Display the number of books in the library"  << std::endl;
//    std::cout << std::setw(4) << "4:" << " Display a books information"                 << std::endl;
//    std::cout << std::setw(4) << "5:" << " Display the list of all books"               << std::endl;
//    std::cout << std::setw(4) << "6:" << " Return to the previous menu"                 << std::endl;
//    std::cout << std::setw(4) << "7:" << " Exiting the library"                         << std::endl;
//    std::cout << "===================================================="                 << std::endl;

bool menu_Handler(int option, Library & libObj)
{
    switch(option)
    {
        case (BOOK_ISSUE):
        {
            if(file_BookIssue)
                menu_BookIssueTable();
            else
            {
                std::cout << "\nThere are no books into the Issue.\n";
                wait_enter();
                prog_state = 0;
                mainMenu();
            }
        }
            break;
        case (ADD_BOOK):
        {
            addBookInformation(libObj);

            std::cout.flush();   // output symbols from buffer
            clr_screen();

            mainMenu();

            std::cout << "\nYou have entered a book into the libray.\n";
        }
            break;

        case (REMOVE_BOOK):
        {
            if(libObj.totalBooks())
            {
                removeBook(libObj);

                std::cout.flush();   // output symbols from buffer
                clr_screen();

                mainMenu();

                std::cout << "\nYou have removed a book from the library.\n";
            }
            else
                std::cout << "\nThere are no books in library.\n";
        }
            break;

        case (SHOW_NUMBER_OF_BOOKS):
        {
            unsigned numBooks = libObj.totalBooks();
            if(numBooks != 1)
                std::cout << "\nThere are " << numBooks << " books in the library.\n";
            else
                std::cout << "\nThere is 1 book in the library.\n";
        }
            break;

        case (SHOW_INFO_OF_BOOK):
            displayBook(libObj);
            break;

        case (SHOW_LIST_OF_BOOKS):
        {
            unsigned numBooks = libObj.totalBooks();
            if(numBooks)
                libObj.displayLibrary();
            else
                std::cout << "\nThere are no books to display.\n";
        }
            break;

        case 6:
        {
            std::cin.ignore();  // delete '\n' from thread
            std::cout.flush();  // output symbols from buffer
            clr_screen();

            mainMenu();

        }
            break;

        case 7:
            return false;

        default: {
            std::cout << "\nInvalid selection please try again.\n";
            break;
        }
    }
    return true;
}

void addBookInformation(Library &libObj)
{
    unsigned year = 0;
    std::string title, author, bookID;

    std::cin.ignore();  // delete '\n' from thread

    std::cout << "Please enter the books ID: ";
    std::getline(std::cin, bookID);

    std::cout << "Please enter the books title: ";
    std::getline(std::cin, title);

    std::cout << "Please enter the books author: ";
    std::getline(std::cin, author);

    std::cout << "Please enter the books year: ";
    std::cin >> year;

    BookCard book(title, author, static_cast<unsigned>(year));
    libObj.addBook(bookID, book);
}

void removeBook(Library &libObj)
{
    unsigned numBooks = libObj.totalBooks();

    if(!numBooks)
    {
        std::cout << "\nThere are 0 books in library - nothing to remove.\n";
        return;
    }

    std::string id;

    std::cin.ignore(); // delete '\n' from thread

    std::cout << "\nRemove book by ID\n";
    std::cout << "Enter the books ID: ";

    std::getline( std::cin, id );
    libObj.removeBook( id );
}

void displayBook(Library &libObj)
{
    std::string id;
    unsigned numBooks = libObj.totalBooks();

    if(!numBooks)
    {
        std::cout << "\nThere are 0 books in the library - nothing to display.\n";
        return;
    }

    std::cin.ignore();  // delete '\n' from thread
    std::cout << "\nFind book by ID(I)\n";
    std::cout << "Enter the books ID: ";
    std::getline(std::cin, id);

//    Library::LibraryMapConst::const_iterator it = findBook(id);
//    if(it != second.end(), id)

    // BookCard & book = libObj.findBook(id);
    // if(book)
    //     std::cout << book;
    // else
    //     std::cout << "\nBook was not found.\n";
}
