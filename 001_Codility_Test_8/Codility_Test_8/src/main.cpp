#include "main.h"

int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );



    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
