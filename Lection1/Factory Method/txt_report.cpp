#include "report.h"

#include <string>
#include <fstream>
#include <iostream>

void TxtFileReport::generate() const {
    const std::string path = "report.txt";
    std::ofstream report(path);

    try {
        if(report.is_open()) {
            for(const auto& entry : files) {
                report << "File: " << entry.get_name() << '\n'
                       << "Size: " << entry.get_size() << " bytes \n"
                       << "Creation time: " << entry.get_creation_time() << "\n"
                       << "Modification time: " << entry.get_modification_time() << "\n"
                       << "Access time: " << entry.get_access_time() << "\n";

                report << std::endl;
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
