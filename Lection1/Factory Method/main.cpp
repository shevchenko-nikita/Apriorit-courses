#include <iostream>

#include "files_info.h"
#include "report.h"
#include "report_creator.h"


int main() {

    std::string path = "C:\\Users\\Shevchenko\\Documents\\1";

    std::vector<File> files = parseFolder(path);
    std::shared_ptr<FileReport> report = std::make_shared<TxtFileReport>(files);
    //std::shared_ptr<FileReport> report = std::make_shared<CsvFileReport>(files);

    report->generate();


}