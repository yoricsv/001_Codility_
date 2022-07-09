//
// Created by Yoric on 21-Feb-22.
//
#include "HDDScanner.h"

HDDScanner::HDDScanner(std::string & scanDirectoryPath) noexcept :
    _scan_directory_path(std::move(scanDirectoryPath))
{

}
const std::string & HDDScanner::getScanDirectoryPath() const
{
    return _scan_directory_path;
}
void HDDScanner::setScanDirectoryPath(const std::string & scanDirectoryPath)
{
    _scan_directory_path = scanDirectoryPath;
}
void HDDScanner::scan()
{

}
#ifdef _MCV_VER
void HDDScanner::read_directory(
        const std::string        & name,
        std::vector<std::string> & v
    )
{
    DIR           * dir_ptr;
    struct dirent * dp;

    if((dir_ptr = opendir(path.c_str())) != nullptr)
    {
        while ((dp = readdir(dir_ptr)) != nullptr)
        {
            std::string file_name = dp -> d_name;

            if (   file_name == "."
                || file_name == ".."
                )
                continue;

            file_name += HDD_SCANNER_DELIMITER;

            isDirectory(dp -> d_name)  ?
                file_name += "dir"     :
                file_name += std::to_string(fileSize(dp -> d_name));

            values.emplace_back(file_name);
        }
        closedir(dir_ptr);
        return EXIT_SUCCESS;
    }
    else
    {
        std::cerr << "Couldn't open directory!\n";
        return EXIT_FAILURE;
    }
}
#endif

// TODO: Add it into a class as methods
pos_type fileSize(const char * file_name)/** ADDED */
{
    std::ifstream in(
        file_name,
          std::ifstream::ate
        | std::ifstream::binary
    );
    return in.tellg();
}
bool isDirectory(const char * file_name)/** ADDED */
{
    return fileSize(file_name) == HDD_SCANNER_DIRECTORY;
}
void printResultSet(const std::vector<std::string> & result_set)
{
    for (const std::string & i : result_set)
        std::cout << i << std::endl;
}
std::string getFilePath(const std::string & path)/** ADDED */
{
    auto path_end = path.find_last_of("/\\");
    auto path_name = path_end == std::string::npos ? path : path.substr(0, path_end);

    return path_name;
}
/***************************************************************************************/


/** ALL FROM MAIN FUNCTION
// TODO: Add it into a class as method to check the operation
std::string test_file_path   = "C:\\Users\\Сергей Владимирович\\";
std::string test_file_path_2 = "c:";

std::vector<std::string> result_set;

     char *  test_file = "C:\\Users\\Сергей Владимирович\\ntuser_21022021.reg";
    DWORD    return_value = 0;
     BOOL    success;
const int    BUFFER_SIZE = 4096;
    TCHAR    buffer[BUFFER_SIZE] = TEXT("");
    TCHAR ** lppPart = { nullptr };

    if( argc != 2 )
        printf(
            TEXT("Usage: %s [file]\n"),
            argv[0]
        );

    return_value =
        GetFullPathName(
//            argv[1],
            test_file,
            BUFFER_SIZE,
            buffer,
            lppPart
        );

        if (return_value == 0)
            printf (
                "GetFullPathName failed (%d)\n",
                GetLastError()
            ); // Handle an error condition.
        else
        {
            printf(
                TEXT(
                    "The full path name is:  %s\n"),
                    buffer
                );

            if (     lppPart != nullptr
                && * lppPart != 0
                )
                printf(
                    TEXT(
                        "The final component in the path name is:  %s\n"
                    ),
                    * lppPart
                );
    }

    read_directory(test_file_path, result_set);

    printResultSet(result_set);

    std::cout << get_file_path(test_file_path) << std::endl;
*/