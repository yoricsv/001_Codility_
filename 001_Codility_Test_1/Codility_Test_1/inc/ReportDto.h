//
// Created by Yoric on 22-Feb-22.
//
#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <iomanip>
#include <ostream>
#include <string>

constexpr auto PATH = "report.dat";

class ReportDto
{
public:
    ReportDto()  = default;
    explicit ReportDto(
        const std::string & fileName,
        const std::string & fileType,
        const std::string & filePath,
        const std::string & fileGroup,
        const std::string & fileDate,
            unsigned long   fileSize
    ) noexcept;
    virtual ~ReportDto();

    const std::string & getFileName()  const;
    const std::string & getFileType()  const;
    const std::string & getFilePath()  const;
    const std::string & getFileGroup() const;
    const std::string & getFileDate()  const;
        unsigned long   getFileSize()  const;

    void setFileName  (const std::string & fileName);
    void setFileType  (const std::string & fileType);
    void setFilePath  (const std::string & filePath);
    void setFileGroup (const std::string & fileGroup);
    void setFileDate  (const std::string & fileDate);
    void setFileSize  (    unsigned long   fileSizeByte);

    bool operator == (const ReportDto & other) const;
    bool operator != (const ReportDto & other) const;
    bool operator <  (const ReportDto & other) const;
    bool operator >  (const ReportDto & other) const;
    bool operator <= (const ReportDto & other) const;
    bool operator >= (const ReportDto & other) const;

    friend std::ostream & operator << (
               std::ostream & outStream,
            const ReportDto & report
        );

private:
      std::string _file_name;
      std::string _file_type;
      std::string _file_path;
      std::string _file_group;
      std::string _file_date;
    unsigned long _file_size{};
};

#endif //REPORT_H
