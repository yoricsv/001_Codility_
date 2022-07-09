//
// Created by Yoric on 17-Feb-22.
//

#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>

//#include <boost/filesystem/operations.hpp>
//#ifdef BOOST_FILESYSTEM_OPERATIONS_HPP
//namespace boost_fs = boost::filesystem;
//const boost_fs::path path;
//#endif

/** UNORDERED_SET record
std::unordered_set<std::string> readFileIntoSet(std::fstream & in_stream)
{
    std::unordered_set<std::string> record;

    std::istream_iterator<std::string> it_input_stream{in_stream};
    std::istream_iterator<std::string> end_input_stream;

    std::copy(
            it_input_stream,
            end_input_stream,
            std::inserter(
                    record,
                    record.end()
            )
    );

    for( const auto & record_line : record)
        std::cout << record_line << DELIMITER << "\n";

    std::cout << "\n";

    return record;
}
*/


/** BEFORE isFileOpen
    !out_stream.is_open()                   ?
        std::cout << "File doesn't open\n"  :
        std::cout << "OK!\n\n";
 */


#include "CommandPromptArgValidator.h"


/***********************************************


#include <filesystem>

namespace fs = std::filesystem;

class Report;

bool
isFileOpen          (
        std::fstream            & stream,
        const std::string       & path,
        std::ios_base::openmode   open_mode
);
std::tuple<fs::path, fs::file_status, size_t>
getFileInfo         (
        const fs::directory_entry & entry
);
char
getFileType         (
        const fs::path & path
);
std::string
getFilePermissions  (
        fs::perms permission
);
std::string
cutDotInExtension   (
        const std::string & file_extension
);
std::string
detectGroup         (
        const std::string                       & file_extension,
        const std::map<std::string,std::string> & pairs
);
std::fstream::pos_type
fileSizePrecision   (
        const std::string & file_name
);
std::string
getReadableFileSize (
        size_t file_size
);
std::string
getFileSizeString   (
        const std::string & file_path,
        size_t              file_size
);
std::map<fs::path, std::pair<size_t, size_t>>
getFilesStat        (
        const fs::path & dir
);
std::vector<std::vector<Report>>
groupById           (
        const std::vector<Report> & data_report
);
size_t
getPathHash         (
        const fs::path & path
);
size_t
reduceDuplicates    (
        const fs::path & dir
);

*/

#endif //_MAIN_H
