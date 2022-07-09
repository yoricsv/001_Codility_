#include "main.h"

#ifdef __GNUC__
    constexpr auto gcc_version = "Gcc compiler\t was detected";
    #if __cplusplus >= 201703L
        constexpr auto std_version = "Standard 2017\t was detected";
        #include <filesystem>
        constexpr auto  filesystem = "Filesystem\t was included";
    #endif
#endif

int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );

    std::cout
        << gcc_version
    << std::endl
        << std_version
    << std::endl
        << filesystem
    << std::endl;

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
