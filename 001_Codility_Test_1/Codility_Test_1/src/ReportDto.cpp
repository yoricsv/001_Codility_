//
// Created by Yoric on 22-Feb-22.
//
#include "ReportDto.h"

ReportDto::ReportDto(
        const std::string & fileName,
        const std::string & fileType,
        const std::string & filePath,
        const std::string & fileGroup,
        const std::string & fileDate,
            unsigned long   fileSize
   ) noexcept :
   _file_name (fileName),
   _file_type (fileType),
   _file_path (filePath),
   _file_group(fileGroup),
   _file_date (fileDate),
   _file_size (fileSize)
{
    this -> _file_name  = fileName;
    this -> _file_type  = fileType;
    this -> _file_path  = filePath;
    this -> _file_group = fileGroup;
    this -> _file_date  = fileDate;
    this -> _file_size  = fileSize;
}


const std::string & ReportDto::getFileName()  const
{
    return _file_name;
}
const std::string & ReportDto::getFileType()  const
{
    return _file_type;
}
const std::string & ReportDto::getFilePath()  const
{
    return _file_path;
}
const std::string & ReportDto::getFileGroup() const
{
    return _file_group;
}
const std::string & ReportDto::getFileDate()  const
{
    return _file_date;
}
unsigned long       ReportDto::getFileSize()  const
{
    return _file_size;
}


void ReportDto::setFileName (const std::string & fileName)
{
    _file_name = fileName;
}
void ReportDto::setFileType (const std::string & fileType)
{
    _file_type = fileType;
}
void ReportDto::setFilePath (const std::string & filePath)
{
    _file_path = filePath;
}
void ReportDto::setFileGroup(const std::string & fileGroup)
{
    _file_path = fileGroup;
}
void ReportDto::setFileDate (const std::string & fileDate)
{
    _file_path = fileDate;
}
void ReportDto::setFileSize (    unsigned long   fileSize)
{
    _file_size = fileSize;
}


bool ReportDto::operator == (const ReportDto & other) const
{
    return
          _file_name  == other._file_name
       && _file_type  == other._file_type
       && _file_path  == other._file_path
       && _file_group == other._file_group
       && _file_date  == other._file_date
       && _file_size  == other._file_size;
}
bool ReportDto::operator != (const ReportDto & other) const
{
    return !(other == *this);
}
bool ReportDto::operator <  (const ReportDto & other) const
{
    if (_file_name  < other._file_name)
        return true;
    if (_file_type  < other._file_type)
        return true;
    if (_file_path  < other._file_path)
        return true;
    if (_file_group < other._file_group)
        return true;
    if (_file_date  < other._file_date)
        return true;

    if (other._file_name  < _file_name)
        return false;
    if (other._file_type  < _file_type)
        return false;
    if (other._file_path  < _file_path)
        return false;
    if (other._file_group < _file_group)
        return false;
    if (other._file_date  < _file_date)
        return false;

    return _file_size < other._file_size;
}
bool ReportDto::operator >  (const ReportDto & other) const
{
    return other < *this;
}
bool ReportDto::operator <= (const ReportDto & other) const
{
    return !(other < *this);
}
bool ReportDto::operator >= (const ReportDto & other) const
{
    return !(*this < other);
}

std::ostream & operator << (
           std::ostream & outStream,
        const ReportDto & report
    )
{
    return
        outStream
            << "File Name: "     << report._file_name
            << " Type: "         << report._file_type
            << " Path: "         << report._file_path
            << " Group: "        << report._file_group
            << " Modify Date: "  << report._file_date
            << " Size (bytes): " << report._file_size;
}

ReportDto::~ReportDto() = default;