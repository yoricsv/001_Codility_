#include "main.h"

#include <algorithm>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <functional>       // not use if dirent.h
#include <io.h>
//#include <iomanip>          // not use if dirent.h
#include <iterator>
#include <map>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
//#include <unordered_map>    // not use if dirent.h
//#include <unordered_set>
//#include <utility>          // not use if dirent.h
//#include <unistd.h>
#include <vector>



#if    __cplusplus >= 201703L \
    || _MSVC_LANG  >= 201703L
    #include <filesystem>

/** BLOCK OF SWITCHERS */
#define F_SYS
#define FILE_INFO_FUNCTIONS
#define PATH_NORMALIZE

/** program modes */
#define REPORT_STRUCT
#define EXTENSION_GROUP
#define STAT_GATHERING
#define DUPLICATE_FINDER
/** END BLOCK OF SWITCHERS */

    #ifdef PATH_NORMALIZE
        #include <string>
        #include <sstream>
    #endif

    #ifdef FILE_INFO_FUNCTIONS
        #include <fstream>
        #include <iterator>
    #endif

    #ifdef EXTENSION_GROUP
        #include <cstring>
        #include <iomanip>
        #include <vector>
    #endif

    #ifdef STAT_GATHERING
        #include <utility>
    #endif

    #ifdef DUPLICATE_FINDER
        #include <cstddef>
        #include <unordered_map>
    #endif
#else
/** BLOCK OF SWITCHERS */
#define REPORT_STRUCT_FIRST
#define REPORT_STRUCT_SECOND

#define INFO_FUNCTIONS
#define FILE_INFO_FUNCTIONS
#define UTILITIES

#define CHECK_FILE_OPEN
#define READ_DIRECTORY
#define GET_FILE_EXTENSION
#define DETECT_GROUP_BY_FILE_EXTENSION
#define READ_FILE

//#define WRITE_IN_FILE
//#define READ_FROM_FILE
/** END BLOCK OF SWITCHERS */
#endif


std::map<std::string, std::string> type_group;
constexpr auto DELIMITER  = " ";
constexpr auto NOT_A_FILE = -1;



#ifdef REPORT_STRUCT_FIRST
    #include "ReportStructure.h"
#endif


#ifdef CHECK_FILE_OPEN
bool isFileOpen (
        std::fstream            & stream,
        const std::string       & path,
        std::ios_base::openmode   open_mode
    )
{
    stream.exceptions(std::fstream::badbit);
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
        close(open_mode);
        stream.close();
        return false;
    }
}
#endif


#ifdef INFO_FUNCTIONS
bool doesFileExists(const char * path)/****/
{
    return access(path, F_OK) == 0;
}

long long int getFileSize(const char * path)
{
    struct stat stat_buffer {};

    return
        stat(path, & stat_buffer) != 0  ? // Check exists and get status
            stat_buffer.st_size         :
            NOT_A_FILE;
}


#ifdef CHECK_FILE_OPEN
//#ifdef FILE_INFO_FUNCTIONS

//std::fstream::pos_type fileSizePrecision(const std::string & file_name)
std::fstream::pos_type fileSize(const char * file_name)
{
    std::fstream in_stream;

    isFileOpen(
        in_stream,
        file_name,
         std::fstream::in
        | std::fstream::binary
    );

    in_stream.seekg(0, std::ios_base::end);

    const auto f_pos { in_stream.tellg() };

    in_stream.close();

    return f_pos;
}

bool isDirectory(const char * file_name)
{
    return fileSize(file_name) == NOT_A_FILE;
}
#endif


unsigned short getFileStatus(const char * path)
{
    struct stat stat_buffer {};

    return
        stat(path, & stat_buffer) != 0  ? // Check exists and get status
            stat_buffer.st_mode         :
            0u;
}

char getFileType(const char * path)
{
    unsigned short file_mode;

    if(doesFileExists(path))
    {
        file_mode = getFileStatus(path);

        if      (file_mode & S_IFDIR) { return 'd'; }
        else if (file_mode & S_IFREG) { return 'f'; }

        else if (file_mode & S_IFCHR) { return 'c'; }
        else if (file_mode & S_IFBLK) { return 'b'; }
        else if (file_mode & S_IFIFO) { return 'p'; }
    }

    return '?';
}

std::string getFilePermissions(const char * path)
{
    unsigned short permission = 0;

    if(doesFileExists(path))
        permission = getFileStatus(path);

    auto check (
        [permission](unsigned short bit, char c)
        {
            return (permission & bit) == 0 ? '-' : c;
        }
    );

    return
        {
            /* Check owner permissions */
            check(S_IRUSR, 'r'),    // S_IREAD
            check(S_IWUSR, 'w'),    // S_IWRITE
            check(S_IXUSR, 'x'),    // S_IEXEC

            /* Check group permissions */
            check(S_IRGRP, 'r'),    // S_IREAD
            check(S_IWGRP, 'w'),    // S_IWRITE
            check(S_IXGRP, 'x'),    // S_IEXEC

            /* check other user permissions */
            check(S_IROTH, 'r'),    // S_IREAD
            check(S_IWOTH, 'w'),    // S_IWRITE
            check(S_IXOTH, 'x')     // S_IEXEC
        };
}


std::tuple<std::string, char, size_t> getFileInfo(
        const char * path
    )
{
    /**
     * 1 - normalize path;
     * 2 - file type,
     * 3 - file size (if not a dir)
     */
    return
        doesFileExists(path)                        ?
            std::tuple<std::string, char, size_t>
            {
                path,
                getFileType(path),
                getFileType(path) == 'f' ?
                    getFileSize(path)    :
                    0u
            }                                       :
            std::tuple<std::string, char, size_t> {};
}
#endif





#ifdef UTILITIES
inline constexpr auto separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

std::string convertWinSlashesToUnix(std::string & path)
{
    std::replace(
        path.begin(),
        path.end(),
        '\\',
        '/'
    );

    return path;
}
std::string convertCharToString(char * in_stream)
{
    return static_cast<std::string>(in_stream);
}
#endif


#ifdef READ_DIRECTORY
bool readDirectory(
        const std::string        & path,
        std::vector<std::string> & values
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

            file_name += DELIMITER;

#ifdef CHECK_FILE_OPEN
            file_name +=
                isDirectory(dp -> d_name)     ?
                    "dir"                      :
                    std::to_string(
                        fileSize(dp -> d_name)
                    );
#else
            file_name +=
                getFileSize(dp -> d_name) != NOT_A_FILE     ?
                    "dir"                                   :
                    std::to_string(
                        getFileSize(dp -> d_name)
                    );
#endif

            values.emplace_back(file_name);
        }
        (void) closedir(dir_ptr);
        return EXIT_SUCCESS;
    }
    else
    {
        std::cerr << "Couldn't open directory!\n";
        return EXIT_FAILURE;
    }
}
#endif


#ifdef READ_FILE
/** READ FILE */
std::vector<std::string> readFile(std::fstream & in_stream)
{
    std::string              line;
    std::vector<std::string> input_data;

//    in_stream.ignore (
//        std::numeric_limits<std::streamsize>::max(),
//        '\n'
//    );
/**    std::vector<std::string> input_data
 *    {
 *        std::istream_iterator<std::string>(in_stream),
 *        std::istream_iterator<std::string>()
 *    };
 */

/**    copy( std::istream_iterator<std::string>(in_stream),
 *          std::istream_iterator<std::string>(),
 *          back_inserter(input_data)
 *    );
 */

    while ( std::getline(
                in_stream,
                line
            )
        )
    {
        input_data.push_back(line);
    }

    return input_data;
}
#endif



#ifdef GET_FILE_EXTENSION
std::string extractExtension(const std::string & path_or_name)
{
    const size_t dot_pos = path_or_name.rfind('.');

    return
        std::string::npos != dot_pos    ?
            path_or_name.substr (
                0,
                dot_pos
            )                           :
            "" ;
}
std::string cutDotInExtension (const std::string & file_extension)
{
    const auto next_symbol {1};
    const auto find_last_dot_pos { file_extension.rfind('.') + next_symbol };

    return
        std::string::npos != find_last_dot_pos  ?
            file_extension.substr (
                find_last_dot_pos,
                std::string::npos
            )                                   :
        file_extension ;
}
#endif


#ifdef DETECT_GROUP_BY_FILE_EXTENSION
std::string detectGroup(
        const std::string                       & file_extension,
        const std::map<std::string,std::string> & pairs
    )
{
    auto it = pairs.find(cutDotInExtension(file_extension));

    return it != pairs.end() ? it -> second : "other";
}
#endif

/** GET NAME FROM PATH */
std::string extractName(const std::string & path)
{
    auto slash_pos = path.find_last_of("\\/");

    return
        std::string::npos != slash_pos  ?
            path.substr (
                0,
                slash_pos
            )                           :
        path ;
}


std::string test_path = "c:\\";
/**********************************/
std::vector<std::string> generatePaths() {
    std::vector<std::string> paths;

    paths.emplace_back(R"(C:\Users\xxxx\\)");
    paths.emplace_back("C:\\");
    paths.emplace_back("C:");
    paths.emplace_back("C:\\\\");
    paths.emplace_back("C://");
    paths.emplace_back("C:/");
    paths.emplace_back("test\\test1\\tmp2");
    paths.emplace_back(R"(C:\Users\xxxxx\projects\\\play_ground\\\)");    // "C:\\Users\\xxxxx\\projects\\\\\\play_ground\\\\\\"
    paths.emplace_back("C:/Users/xxxxxx/projects/////play_ground////");

    return paths;
}
std::string getParentDir(const std::string& dir_path) {

    std::string forward_slash = "/";
    std::string backward_slash = "\\";

    std::string delimiter;

    if (dir_path.find(forward_slash) != std::string::npos) {
        delimiter = forward_slash;
    }
    else if (dir_path.find(backward_slash) != std::string::npos) {
        delimiter = backward_slash;
    }
    else {
        return dir_path;
    }
    std::string parent_path;

    for (int index = dir_path.size()-1; index > 0 ; --index) {

        int first_delimeter_pos = index;
        size_t second_delimeter_pos = (int)dir_path.find_last_of(delimiter, first_delimeter_pos);
        int diff = first_delimeter_pos - second_delimeter_pos;

        if (second_delimeter_pos == std::string::npos) {
            parent_path = dir_path.substr(0, first_delimeter_pos+1);
            break;
        }
        if (diff > 1) {
            parent_path = dir_path.substr(0, second_delimeter_pos);
            break;
        }
        index -= diff;
    }

    return parent_path;
}
/*********************************************/
std::string root_name(std::string & path)
{
    auto slash_pos = path.find_first_of("\\/" || ":");  // "\\/" || ":" --> simplify to true

    while (std::string::npos != slash_pos)
        path.substr(

        );
    return

}

int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );
    /*******************************************************************/
    std::vector<std::string> test_paths = generatePaths();
    for (int i = 0; i < test_paths.size(); ++i) {
        std::string my_dir = test_paths[i];
        std::string parent_dir = getParentDir(my_dir);

        std::cout << "dir =  " << my_dir << " :: parent dir = " << parent_dir << std::endl;

    }
    /*******************************************************************/
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
//            << canonical(dir).c_str()
        << std::endl;
#endif
#endif

#ifdef FILESYSTEM
    std::vector<std::tuple<fs::path, fs::file_status, size_t>> files;

    std::transform(
        fs::directory_iterator{dir},
        {},
        std::back_inserter(files),
        file_info
    );

    for (   const auto & [
                file_path,
                file_status,
                file_size
            ] : files
        )
    {
        std::cout
            << type_char(file_status)
            << rwx(file_status.permissions())    << DELIMITER
            << file_path.filename().c_str()         << DELIMITER
            << file_path.extension().c_str();
    }
#endif
    /** MAP type-group */
    std::string type;
    std::string group;

    type_group.emplace("ogg","music");
    type_group.emplace("mp3","music");
    type_group.emplace("wav","music");
    type_group.emplace("acc","music");
    type_group.emplace("flat","music");

    type_group.emplace("doc","documents");
    type_group.emplace("pdf","documents");
    type_group.emplace("docx","documents");
    type_group.emplace("xls","documents");
    type_group.emplace("txt","documents");

    type_group.emplace("bmp","pictures");
    type_group.emplace("png","pictures");
    type_group.emplace("jpg","pictures");
    type_group.emplace("tiff","pictures");
    type_group.emplace("gif","pictures");

    type_group.emplace("avi","movies");
    type_group.emplace("mpg","movies");
    type_group.emplace("vob","movies");
    type_group.emplace("mp4","movies");
    type_group.emplace("h265","movies");

    type_group.emplace("com","programs");
    type_group.emplace("exe","programs");
    type_group.emplace("bin","programs");
    type_group.emplace("dll","programs");
    type_group.emplace("sys","programs");

    type_group.emplace("dir","directories");
    /** MAP type-group */







#ifdef WRITE_IN_FILE
    std::fstream out_stream;

    isFileOpen(
        out_stream,
        ".",
        std::fstream::out
    );

    for ( int i = 0;
              i < 10;
              i++
        )
    {
        out_stream
            << "FileName:"     << i << DELIMITER
            << "Type:"         << i << DELIMITER
            << "Path:"         << i << DELIMITER
            << "Group:"        << i << DELIMITER
            << "Modify Date:"  << i << DELIMITER
            << "Size(bytes):"  << i << std::endl;
    }
    out_stream.close();
#endif

#ifdef READ_FROM_FILE
    std::fstream get_result_file_input;

    isFileOpen(
        get_result_file_input,
        ".",
        std::fstream::in
    );

    for(const auto & i : readFile(get_result_file_input))
    {
        std::cout <<  i << std::endl;
    }

    std::fstream file_move_out;

    isFileOpen(
        file_move_out,
        "newMoved_file.txt",
          std::fstream::out
        | std::ofstream::app
    );

    /** WRITE INPUT STREAM TO A FILE */
    std::string s;

    for(const auto & i : readFile(get_result_file_input))
    {
        file_move_out <<  i << std::endl;
    }

    get_result_file_input.close();
    file_move_out.close();

#ifdef REPORT_STRUCT_SECOND
    /** VECTOR report_data */
    std::vector<ReportStructure> report_data;

    std::copy(
        std::istream_iterator<std::vector<ReportStructure>>{get_result_file_input},
        {} ,
        std::back_inserter(report_data)
    );

    std::copy(
        report_data.begin(),
        report_data.end(),
        std::ostream_iterator<ReportStructure>{std::cout, " "}
    );

//    for (const auto & i : report_data)
//    {
//        std::cout
//            << i.name
//            << i.type
//            << i.path
//            << i.group
//            << i.date
//            << i.size
//        << std::endl;
//    }
#endif
#endif



    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
