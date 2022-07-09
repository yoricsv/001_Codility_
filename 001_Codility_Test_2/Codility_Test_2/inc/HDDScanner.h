//
// Created by Yoric on 21-Feb-22.
//
#pragma once
#ifndef HDD_SCANNER_H
#define HDD_SCANNER_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#ifndef _MSC_VER
    #include <dirent.h>
#endif

#include <fstream>
#include <Windows.h>

constexpr auto HDD_SCANNER_DELIMITER = " ";
constexpr auto HDD_SCANNER_DIRECTORY               = -1;
constexpr auto DEFAULT_FILE_PATH = "file.txt";
constexpr auto RESULT_FILE_PATH  = "result_file.txt";
constexpr auto DIRECTORY         = -1;

/**
 * @NOTE
 * The source file is UTF-8 encoded,
 * use 65001 wCode and <clocale> header
 * to display correctly
 */
//    SetConsoleOutputCP(65001);
//    SetConsoleOutputCP(1049);
//    bool SetThreadLocale(LOCALE_SYSTEM_DEFAULT);

using pos_type = std::ifstream::pos_type; // ALIAS

namespace
{
    constexpr const char * DEFAULT_PATHS[] =
    {
        "",
        "res/",
        "../res/"
    };
}

class HDDScanner
{
public:
    explicit HDDScanner(std::string & path) noexcept;
    virtual ~HDDScanner() = default;

    void scan();

    [[nodiscard]] const std::string & getScanDirectoryPath() const;
    void setScanDirectoryPath(const std::string & scanDirectoryPath);

#ifdef _MCV_VER
    void read_directory(
        const std::string        & name,
        std::vector<std::string> & v
    );
#endif
private:
    std::string _scan_directory_path = "C:\\";
};

   pos_type fileSize      (const char * file_name);
       bool isDirectory   (const char * file_name);
       void printResultSet(const std::vector<std::string> & result_set);
std::string getFilePath   (const std::string & path);

#endif //HDD_SCANNER_H
