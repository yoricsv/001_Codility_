//
// Created by Yoric on 19-Feb-22.
//

#include "CommandPromptArgValidator.h"

void command_prompt_validator(
        int    argc,
        char * argv[]
    )
{
    if ( argc < 2)
    {
        std::cout << "\t|The app runs in command prompt mode|\n"
            << std::endl;

        if( !std::cout.good())
            std::cerr << "When running the app without arguments, "
                      << "the CommandPromptArgValidator returns: "
                      << EXIT_FAILURE
                      << " code."
                << std::endl;
    }


#ifdef USE_CONFIGURATION_FILE
    if (     argc == 2
        &&
            (
                   std::string(argv[1]) == "-v"
                || std::string(argv[1]) == "--version"
            )
        )
    {
        std::cout << "v." << Codility_Test_4_VERSION_MAJOR
                  << "."  << Codility_Test_4_VERSION_MINOR
            << std::endl;

        if( !std::cout.good())
            std::cerr << "When calling VERSION, the CommandPromptArgValidator returns: "
                      << EXIT_FAILURE
                      << " code."
                << std::endl;
    }
#endif


    if (   argc == 2
        && std::string(argv[1]).empty()
        )
    {
        std::cout << "\t\tWARNING!\n"
                  << "You are trying to pass an empty value.\n"
                  << "The app will close.\n"
                  << "Please, run it again with correct arguments."
            << std::endl;

        if( !std::cout.good())
            std::cerr << "When running the app with an empty argument, "
                      << "the CommandPromptArgValidator returns: "
                      << EXIT_FAILURE
                      << " code."
                << std::endl;
    }
}
