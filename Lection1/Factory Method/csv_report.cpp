#include "csv_report.h"

#include <string>
#include <fstream>
#include <iostream>

void CsvFileReport::generate(const std::string& path) const {
    std::ofstream report(path);

    try {
        if(report.is_open()) {
            report << "Name,Size,Creation_Time,Modification_Time,Access_Time\n";

            for(const auto& entry : files) {
                report << entry.getName() << ','
                       << entry.getSize() << ','
                       << entry.getCreationTime() << ','
                       << entry.getModificationTime() << ','
                       << entry.getAccessTime() << '\n';
            }

            report.close();
        }
        else {
            throw std::runtime_error("File is not opened");
        }
    }
    catch(const std::exception& ex) {
        std::cout << "Report is not created: " << ex.what() << std::endl;
        exit(1);
    }
}