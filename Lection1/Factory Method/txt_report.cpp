#include "txt_report.h"

#include <string>
#include <fstream>
#include <iostream>

void TxtFileReport::generate(const std::string& path) const {
    std::ofstream report(path);

    try {
        if(report.is_open()) {
            for(const auto& entry : files) {
                report << "File: " << entry.getName() << '\n'
                       << "Size: " << entry.getSize() << " bytes \n"
                       << "Creation time: " << entry.getCreationTime() << "\n"
                       << "Modification time: " << entry.getModificationTime() << "\n"
                       << "Access time: " << entry.getAccessTime() << "\n";

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
