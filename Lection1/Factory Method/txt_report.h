#pragma once

#include "report.h"

class TxtFileReport: public FileReport {
private:
    std::vector<File> files;

public:
    TxtFileReport(const std::vector<File>& _files) : files(_files) {}

    void generate(const std::string& path) const override;

    ~TxtFileReport() = default;
};