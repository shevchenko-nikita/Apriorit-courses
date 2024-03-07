#pragma once

#include <memory>

#include "file"

class FileReport {
public:
    virtual void generate() const = 0;
};

class TxtFileReport: public FileReport {
private:
    std::vector<File> files;

public:
    TxtFileReport(const std::vector<File>& _files) : files(_files) {}

    void generate() const override;
};

class CsvFileReport: public FileReport {
private:
    std::vector<File> files;

public:
    CsvFileReport(const std::vector<File>& _files) : files(_files) {}

    void generate() const override;
};
