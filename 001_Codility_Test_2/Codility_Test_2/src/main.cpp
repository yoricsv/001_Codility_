#include "main.h"

#include <functional>
#include <map>

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
        #include <unordered_map>
    #endif
#endif


std::map<std::string, std::string> type_group;
constexpr auto DELIMITER = " ";


#ifdef F_SYS
namespace fs = std::filesystem;
#else
using namespace std::filesystem;
#endif


#ifdef REPORT_STRUCT
class Report
{
public:
    Report(
            int          id,
            std::string  info
        ) :
        _id(id),
        _info(std::move(info))
    {}

    [[nodiscard]] int getId() const
    {
        return _id;
    }
    [[nodiscard]] const std::string & getInfo() const
    {
        return _info;
    }

    [[maybe_unused]] void setId(int id)
    {
        Report::_id = id;
    }
    [[maybe_unused]] void setInfo(const std::string & info)
    {
        Report::_info = info;
    }

    bool operator < (const Report & r_other) const
    {
        return _id < r_other._id;
    }
private:
            int _id;
    std::string _info;
};

std::vector<Report> data {};
#endif


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
        return false;
    }
}

#ifdef FILE_INFO_FUNCTIONS
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

/** TO DETECT TYPE OF FILE */
char getFileType(const fs::path & path)
{
    const fs::file_status tag { fs::status(path) };

    if      (is_directory(tag))      { return 'd'; }
    else if (is_regular_file(tag))   { return 'f'; }
    else if (is_symlink(tag))        { return 'l'; }

    else if (is_character_file(tag)) { return 'c'; }
    else if (is_block_file(tag))     { return 'b'; }
    else if (is_fifo(tag))           { return 'p'; }
    else if (is_socket(tag))         { return 's'; }
    else if (is_other(tag))          { return 'o'; }

    return '?';
}

/** TO VISUALISE FILE PERMISSIONS (as in Linux)) */
std::string getFilePermissions(fs::perms permission)
{
    auto check (
        [permission](fs::perms bit, char c)
        {
            return (permission & bit) == fs::perms::none ? '-' : c;
        }
    );

    return
        {
            check(fs::perms::owner_read,   'r'),
            check(fs::perms::owner_write,  'w'),
            check(fs::perms::owner_exec,   'x'),

            check(fs::perms::group_read,   'r'),
            check(fs::perms::group_write,  'w'),
            check(fs::perms::group_exec,   'x'),

            check(fs::perms::others_read,  'r'),
            check(fs::perms::others_write, 'w'),
            check(fs::perms::others_exec,  'x')
        };
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

std::string detectGroup(
        const std::string                       & file_extension,
        const std::map<std::string,std::string> & pairs
    )
{
    auto it = pairs.find(cutDotInExtension(file_extension));

    return it != pairs.end() ? it -> second : "other";
}

/** TO VISUALISE FILE SIZE  */
std::fstream::pos_type fileSizePrecision(const std::string & file_name)
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
std::string getReadableFileSize(size_t file_size)
{
    std::stringstream string_stream;

    if (file_size >= 1000000000)
        string_stream
            << (file_size / 1000000000)
            << DELIMITER << 'G' << 'b';
    else if (file_size >= 1000000)
        string_stream
            << (file_size / 1000000)
            << DELIMITER << 'M' << 'b';
    else if (file_size >= 1000)
        string_stream
            << (file_size / 1000)
            << DELIMITER << 'K' << 'b';
    else
        string_stream
            << file_size
            << DELIMITER << 'b' << DELIMITER;

    return string_stream.str();
}
std::string getFileSizeString(
        const std::string & file_path,
        size_t              file_size
    )
{
    std::string wee_size;

    if (    file_size < 1000
        && !fs::is_directory(file_path)
        )
    {
        wee_size =
            std::to_string(
                fileSizePrecision(file_path)
            );
        wee_size += " b";
    }
    else if (1000 < file_size)
        wee_size = getReadableFileSize(file_size);
    else if(fs::is_directory(file_path))
        wee_size = "folder";

    return wee_size;
}
#endif


#ifdef STAT_GATHERING
std::map<fs::path, std::pair<size_t, size_t>> getFilesStat (const fs::path & dir)
{
    std::map<fs::path, std::pair<size_t, size_t>> tmp;

    for (const auto & entry : fs::recursive_directory_iterator{dir})
    {
        const fs::path path {entry.path()};
        if (getFileType(path) == 'd') continue;

        const std::string extension { path.extension().string() };
        if (extension.length() == 0) continue;

        const size_t file_size {fs::file_size(path)};

        auto & [occupied_place, pieces] = tmp[extension];

        occupied_place += file_size;
        pieces++;
    }

    return tmp;
}
#endif


#ifdef REPORT_STRUCT
std::vector<std::vector<Report>> groupById(const std::vector<Report> & data_report)
{
    std::vector<std::vector<Report>> groups;

    decltype(data.end()) upper;

    for ( auto lower =  data.begin();
               lower != data.end();
               lower =  upper
       )
    {
        upper =
            std::upper_bound(
                data.begin(),
                data.end(),
                * lower
            );

        groups.emplace_back(
            lower,
            upper
        );
    }

    return groups;
}
//auto MapByIDs(const std::vector<Report> & input_data)
//{
//    std::map<std::vector<Report>> result {};
//
//    for(auto &x: input_data)
//        result[x.id].emplace_back(std::move(x));
//    return result;
//}
//auto GroupByIDs(const std::vector<Report> & input_data)
//{
//    auto map = MapByIDs(std::move(input_data));
//
//    std::vector<std::vector<Report>> result;
//
//    for(auto & x: map)
//        result.emplace_back(std::move(x.second));
//
//    return result;
//}
//
//auto outputData = GroupByIDs(std::move(input_data));
#endif


#ifdef DUPLICATE_FINDER
size_t getPathHash(const fs::path & path)
{
    std::fstream in_stream;

    isFileOpen(
        in_stream,
        path.string(),
          std::fstream::in
        | std::fstream::binary
    );

    std::string tmp_stream_buffer;
    
    in_stream.seekg(0, std::ios::end);
    tmp_stream_buffer.reserve(in_stream.tellg());
    
    in_stream.seekg(0, std::ios::beg);
    tmp_stream_buffer.assign(std::istreambuf_iterator<char>{in_stream}, {});

    in_stream.close();

    return std::hash<std::string>{}(tmp_stream_buffer);
}

size_t reduceDuplicates(const fs::path & dir)
{
    std::unordered_map<std::size_t, fs::path> files;
    size_t removed_files_counter {0};

    for ( const auto & entry :
            fs::recursive_directory_iterator{dir}
        )
    {
        const fs::path path {entry.path()};

        if(fs::is_directory(path)) { continue;}

        const auto & [it, success] =
            files.try_emplace(
                getPathHash(path),
                path
            );
        if (!success)
        {
            std::cout
                << "The "
                << path.string()
                << " file is a duplicate of "
                << it -> second.string()
            << std::endl;

            remove(path);

            fs::create_symlink(absolute(it-> second), path);

            removed_files_counter++;
        }
    }
    return removed_files_counter;
}
#endif


int main(
        int    argc,
        char * argv[]
    )
{
    command_prompt_validator( argc, argv );


#ifdef PATH_NORMALIZE
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
        << canonical(dir).string()
    << std::endl;
#endif


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

    type_group.emplace("dir","folder");


#ifdef REPORT_STRUCT
    data.emplace_back(2, "Documents");

    data.emplace_back(5, "Programs");

    data.emplace_back(1, "music");
    data.emplace_back(3, "image");
    data.emplace_back(4, "movie");
    data.emplace_back(6, "other");
#endif


#ifdef EXTENSION_GROUP
    std::vector<std::tuple<fs::path, fs::file_status, size_t>> files;

    std::transform(
        fs::directory_iterator{dir},
        {},
        std::back_inserter(files),
        getFileInfo
    );

    for (   const auto & [
                file_path,
                file_status,
                file_size
            ] : files
        )
    {
        std::cout
            /** FILE TYPE */
            << getFileType(file_path)
        << DELIMITER

            /** PERMISSIONS */
            << getFilePermissions(file_status.permissions())
        << DELIMITER

            /** FILE NAME */
            << std::setw(20)
            << std::left
            << file_path.filename().string()
        << DELIMITER

            /** FILE EXTENSION */
            << std::setw(6)
            << std::left
            << file_path.extension().string()//.erase(0,1)
        << DELIMITER

            /** FILE GROUP ERROR */
            << std::setw(9)
            << std::left
            << detectGroup(
                    file_path.extension().string(),
                    type_group
                )
        << DELIMITER

            /** FILE SIZE */
            << std::setw(6)
            << std::right
            << getFileSizeString(
                    file_path.string(),
                    file_size
                )
//        << DELIMITER

            /** ABSOLUTE PATH */
//            << std::left
//            << file_path.string()
//        << DELIMITER

        << std::endl;
    }
#endif


#ifdef STAT_GATHERING
    for (const auto & [extension, status] : getFilesStat(dir))
    {
        const auto & [occupied_place, pieces] = status;

        std::cout

            /** FILE GROUP */
            << std::setw(9)
            << std::left
            << detectGroup(
                    cutDotInExtension(extension.string()),
                    type_group
            )
        << DELIMITER

            /** FILE EXTENSION DOESN'T WORK */
            << std::setw(12)
            << std::left
            << cutDotInExtension(extension.string())
        << DELIMITER


            /** NUMBER OF THE SAME FILES */
            << std::setw(8)
            << std::right
            << pieces
            << " pcs"
        << DELIMITER

            /** FILE SIZE */
            << std::setw(10)
            << getReadableFileSize(
                    occupied_place
            )
        << std::endl;
    }
#endif


#ifdef REPORT_STRUCT
    std::sort(
        data.begin(),
        data.end()
    );

    std::vector<std::vector<Report>> groups { groupById(data) };

    for(auto const & group: groups)
    {
        if(!group.empty())
            std::cout << "group: " << group.front().getId() << '\n';

        for(auto const& d: group)
            std::cout << "     : " << d.getInfo() << '\n';

        std::cout << '\n';
    }
#endif


#ifdef DUPLICATE_FINDER
    const auto number_of_duplicates = "Number of deleted duplicates: ";
    const auto duplicates_not_found = "No duplicates found.";

    const size_t duplicates { reduceDuplicates(dir) };

    duplicates                                                          ?
        std::cout << number_of_duplicates << duplicates << std::endl    :
        std::cout << duplicates_not_found << std::endl;
#endif


    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
