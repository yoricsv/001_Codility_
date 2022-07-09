#pragma once
#ifndef REPORT_STRUCTURE_H
#define REPORT_STRUCTURE_H

#include <iostream>
#include <string>

struct ReportStructure;

std::istream & operator >> (
        std::istream & input_stream,
        ReportStructure & report_structure
    );
std::ostream & operator << (
        std::ostream & output_stream,
        ReportStructure & report_structure
    );

#endif //REPORT_STRUCTURE_H
