#ifndef MAIN_H
#define MAIN_H

#include <clocale>
#include <iostream>

#include "CommandPromptArgValidator.h"

#include "HDDScanner.h"
#include "FileSystem.h"
/**********************************/


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


#endif //MAIN_H
