#include "report.h"

#include <string>
#include <fstream>
#include <iostream>

void CsvFileReport::generate() const {
    const std::string path = "report.csv";
    std::ofstream report(path);

    try {
        if(report.is_open()) {
            report << "Name,Size,Creation_Time,Modification_Time,Access_Time\n";

            for(const auto& entry : files) {
                report << entry.get_name() << ','
                       << entry.get_size() << ','
                       << entry.get_creation_time() << ','
                       << entry.get_modification_time() << ','
                       << entry.get_access_time() << '\n';
            }

            report.close();
        }
        else {
            throw std::runtime_error("File is not opened");
        }
    }
    catch(const std::exception& ex) {
        std::cout << "Report is not created: " << ex.what() << std::endl;
    }
}