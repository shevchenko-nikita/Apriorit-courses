#include <iostream>

#include "file.h"
#include "report.h"
#include "report_creator.h"


int main(int argc, char** argv) {

    if(argc < 2) {
        std::cout << "not enough arguments";
        exit(1);
    }

    std::string path = argv[1];
    std::string output_path = argv[2];

    Folder main_directory(path);

    std::shared_ptr<FileReport> report = std::make_shared<TxtFileReport>(main_directory.getFilesList());
//    std::shared_ptr<FileReport> report = std::make_shared<CsvFileReport>(main_directory.getFilesList());

    report->generate(output_path);


}