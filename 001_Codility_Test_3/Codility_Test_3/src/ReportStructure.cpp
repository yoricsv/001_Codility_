#include "ReportStructure.h"

struct ReportStructure
{
    std::string name;
    std::string type;
    std::string path;
    std::string group;
    std::string date;
    unsigned long size{};
};
std::istream & operator >> (
        std::istream & input_stream,
        ReportStructure & report_structure
    )
{
    return
        input_stream
            >> report_structure.name
            >> report_structure.type
            >> report_structure.path
            >> report_structure.group
            >> report_structure.date
            >> report_structure.size;
}
std::ostream & operator << (
        std::ostream & output_stream,
        ReportStructure & report_structure
    )
{
    return
        output_stream
            << report_structure.name
            << report_structure.type
            << report_structure.path
            << report_structure.group
            << report_structure.date
            << report_structure.size
        << std::endl;
}
