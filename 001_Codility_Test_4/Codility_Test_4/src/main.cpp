#include "main.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef _WIN64
#define __NT__
    #include <windows.h>

    #if __cplusplus >= 201703L
        #include <filesystem>
        namespace fs = fs::filesystem;
    #endif
#elif __linux__
    #include <dirent.h>
#endif
#include <dirent.h>
constexpr auto DEFAULT_FILE_PATH = "file.txt";
constexpr auto RESULT_FILE_PATH  = "result_file.txt";
constexpr auto DELIMITER         = " ";
constexpr auto DIRECTORY         = -1;

#ifdef __NT__
typedef void (* LPSEARCHFUNC)(LPCTSTR lpszFileName);    // Function called to each finded folder
std::string convert(LPCSTR str)
{
    return std::string(str);
}
void DoSomething(LPCTSTR lpszFileName)
{
    std::cout << lpszFileName << std::endl;
//    MessageBox(NULL, lpszFileName, "Find File", MB_OK | MB_APPLMODAL);
}
bool getAllFilesNames(
        LPCTSTR      lpszFileName,          // folder and search mask
//        const char * dir,
        LPSEARCHFUNC lpSearchFunc,          // Function to each finded folder
        BOOL         bInnerFolders = TRUE   // TRUE  - serch in subdirectories,
                                            // FALSE - search only in current folder
//static std::vector<std::string> getAllFilesNames(
//        const std::string & dir
    )
{
    LPTSTR                   part;
//    std::vector<std::string> names;
    char                    tmp_search_path[MAX_PATH];   // template array
    char                    search_path[MAX_PATH];
//    std::string              tmp_search_path    {};
//    std::string              search_path        { dir + "/*.*" };
//    bool                     search_in_folders  { true };
    WIN32_FIND_DATA          find_data;

    HANDLE                   handle = NULL;
//    HANDLE                   handle
//    {
//        ::FindFirstFile(
//            search_path,
////            search_path.c_str(),      // for std::string
//            & find_data
//        )
//    };

    memset(
        & find_data,
        0,
        sizeof(WIN32_FIND_DATA)
    );

    if(bInnerFolders)         // First, search in subfolders
//    if(search_in_folders)   // First, search in subfolders
    {
        if (    GetFullPathNameA(
                    lpszFileName,
//                    dir,
                    MAX_PATH,
                    tmp_search_path,
                    & part
                ) == 0
            )
            { return FALSE; }

        strcpy(             // add to string search_path of finded paths
            search_path,
            part
        );
        strcpy(             // add to finded paths of *.* search mask
            part,
            "*.*"
        );

        find_data.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        if (  !(
                    ( handle =
                        FindFirstFile(
                            tmp_search_path,
                            & find_data
                        )
                    ) == INVALID_HANDLE_VALUE
                )
            )
            do
            {
                // miss folders with name "." and ".."
                if (   !strncmp(find_data.cFileName, ".",  2)
                    || !strncmp(find_data.cFileName, "..", 2)
                    )
                { continue; }

                if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // in case, folder found
                {
                    char next[MAX_PATH];
                    if (    GetFullPathName(
                                lpszFileName,
                                MAX_PATH,
                                next,
                                & part
                            ) == 0
                        )
                    { return FALSE; }

                    strcpy(
                        part,
                        find_data.cFileName
                    );

                    strcat(
                        next,
                        "\\"
                    );
                    strcat(
                        next,
                        search_path
                    );

                    // to recursive call
                    getAllFilesNames(
                        next,
                        lpSearchFunc,
                        TRUE
                    );
                }
            }
            while (FindNextFile(handle, & find_data));

        FindClose (handle);

//        if (handle != INVALID_HANDLE_VALUE)
//        {
//            do
//            {
//                if (! (
//                    find_data.dwFileAttributes
//                    //                & FILE_ATTRIBUTE_DIRECTORY
//                    & FILE_ATTRIBUTE_NORMAL
//                ))
//                {
//                    // missed folders with name "." and ".."
//                    if (   !strncmp(find_data.cFileName, ".", 2)
//                        || !strncmp(find_data.cFileName, "..", 2)
//                            ) { continue; }
//                    names.push_back(find_data.cFileName);
//                }
//            }
//            while (::FindNextFileA(handle, &find_data));
//
//            ::FindClose(handle);
//        }
//        return names;
        if ( (handle = FindFirstFile(lpszFileName, &find_data)) == INVALID_HANDLE_VALUE)
        { return TRUE; } // в противном случае выходим
        do
            if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // если мы нашли файл
            {
                char file[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
                strcpy(part, find_data.cFileName);

                lpSearchFunc(file);
            }
        while (FindNextFile(handle, &find_data)); // ищем следующий файл
        FindClose (handle); // заканчиваем поиск

        return TRUE;

    }
}
#endif

#if __cplusplus >= 201703L
std::tuple<fs::path, fs::file_status, size_t> getFileInfo(
        const fs::directory_entry & entry
    )
{
    const auto fs (status(entry));

    return
    {
        entry.path(),
        fs,
        is_regular_file(fs)         ?
            file_size(entry.path()) :
            0u
    };
}


#endif

#ifdef __linux__
bool readDirectory(
        const std::string        & path,
        std::vector<std::string> & values
    )
{
    DIR           * dir_ptr;
    struct dirent * dirent_ptr;

    if((dir_ptr = opendir(path.c_str())) != nullptr)
    {
        while ((dirent_ptr = readdir(dir_ptr)) != nullptr)
        {
            std::string file_name = dirent_ptr -> d_name;

            if (   file_name == "."
                || file_name == ".."
                ) { continue; }

            file_name += DELIMITER;

            is_directory(dirent_ptr -> d_name)  ?
                file_name += "dir"      :
                file_name +=
                    std::to_string(
                        fileSize(
                                dirent_ptr -> d_name
                        )
                    );

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
bool search(
        const std::string & path,
        const std::string & search
    )
{
    DIR           * dir_ptr;
    struct dirent * dirent_ptr;

    if((dir_ptr = opendir(path.c_str())) != nullptr)
    {
        while ((dirent_ptr = readdir(dir_ptr)) != nullptr)
        {
            std::string file_name = dirent_ptr -> d_name;

            if (   file_name == "."
                || file_name == ".."
                ) { continue; }

            file_name += DELIMITER;

            is_directory(dirent_ptr -> d_name)  ?
                file_name += "dir"              :
                file_name +=
                    std::to_string(
                        fileSize(
                            dirent_ptr -> d_name
                        )
                    );

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

void print(const std::vector<std::string> & files)
{
    for ( const auto & entry : files)
    {
        std::cout << entry << std::endl;
    }
}

int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );

#ifdef FILESYSTEM
    #ifdef PATH_NORMALIZE
    /** [OPTIONAL] TO REQUIRE ADDITIONAL PARAMETERS */
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <path>\n";
        return EXIT_FAILURE;
    }

    /** [OPTIONAL] CHECK PASSED PATH OR USE CURRENT DIR */
    const fs::path dir{argc > 1 ? argv[1] : fs::current_path()};

    if (!fs::exists(dir))
    {
        std::cout << "Path " << dir << " doesn't exist.\n";
        return EXIT_FAILURE;
    }

    /** [OPTIONAL] DISPLAY THE PASSED PATH */
    std::cout
            << "The path you passed has been normalized to "
            << canonical(dir).c_str()
        << std::endl;
#endif
#endif

//    getAllFilesNames(".", DoSomething, TRUE);
    getAllFilesNames("./", DoSomething, FALSE);
//    print(getAllFilesNames(".");

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
