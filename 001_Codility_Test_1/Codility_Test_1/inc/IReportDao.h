//
// Created by Yoric on 22-Feb-22.
//
#pragma once
#ifndef I_REPORT_DAO_H
#define I_REPORT_DAO_H

class IReportDao
{
public:
    virtual void createReport() = 0;
    virtual void readReport()   = 0;
    virtual void updateReport() = 0;
    virtual void deleteReport() = 0;
};

#endif //I_REPORT_DAO_H
