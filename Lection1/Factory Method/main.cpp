#include <iostream>

#include "file"
#include "report.h"
#include "report_creator.h"


int main() {

    std::string path = "C:\\Users\\Shevchenko\\Documents\\1";

    Folder main_directory(path);

    std::shared_ptr<FileReport> report = std::make_shared<TxtFileReport>(main_directory.getFilesList());
    //std::shared_ptr<FileReport> report = std::make_shared<CsvFileReport>(files);

    report->generate();


}