#pragma once

#include "file.h"
#include "txt_report.h"
#include "csv_report.h"

class ReportCreator {
public:
    virtual std::shared_ptr<FileReport> createReport(const std::vector<File>&) const = 0;
};

class TxtReportCreator: public ReportCreator {
public:
    std::shared_ptr<FileReport> createReport(const std::vector<File>& _files) const override {
        return std::make_shared<TxtFileReport>(_files);
    }
};

class CsvReportCreator: public ReportCreator {
    std::shared_ptr<FileReport> createReport(const std::vector<File>& _files) const override {
        return std::make_shared<CsvFileReport>(_files);
    }
};