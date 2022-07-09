#include "main.h"

int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );

/** LIBRARY PROJECT */
    Library lib;
    Reader  readR;
       Book book;

//    do
//    {
//        std::cin.get(ch);
//        switch(prog_state)
//        {
//            case (BOOK_ISSUE):
//                book_issue();
//            case (BOOK_ISSUE):
//                book_issue();
//            break;
//            case (BOOK_STORAGE):
//                book_storage();
//            break;
//            case (READERS_LIST):
//                reader_list();
//            break;
//            case (LIBRARY_MANAGE):
//                menu_Management();
//            break;
//            case (EXIT_LIBRARY):
//            break;
//            default :std::cout<<"\a";
//        }
//    }
//	while(prog_state != EXIT_LIBRARY);

    do
    {
        mainMenu();
    }
    while(menu_Handler(prog_state, lib));

    quit_lib = true;
    welcome_banner();
    wait_enter();
/** -------------------------------------- */



    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
