#pragma once

#include "report.h"

class CsvFileReport: public FileReport {
private:
    std::vector<File> files;

public:
    CsvFileReport(const std::vector<File>& _files) : files(_files) {}

    void generate(const std::string& path) const override;

    ~CsvFileReport() = default;
};