//
// Created by Yoric on 22-Feb-22.
//
#pragma once
#ifndef REPORT_DAO_H
#define REPORT_DAO_H
#include <vector>
#include <unordered_set>

#include "IReportDao.h"
#include "ReportDto.h"

class ReportDao :
    protected IReportDao
{
public:
    ReportDao() = default;
    virtual ~ReportDao() = default;

    /** CREATE */
    void createReport() override
    {

    }

    /** READ */
    void readReport()   override
    {

    }
    //std::unordered_set<ReportDto> readAllReports() override ;
    //List<Ticket> findByPersonId(Set<Long> ids) override {return null;}
    //Ticket getTicketByNumber(String licensePlateNumber) override {return ticket;}

    /** UPDATE */
    //void saveNewTicket(Ticket ticket) override {}
    void updateReport() override
    {

    }

    /** DELETE */
    void deleteReport() override
    {

    }
    //void deleteAll() override {}
    //void removeByNumber(String number) override {}
private:

};
#endif //REPORT_DAO_H
