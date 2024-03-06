#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class File {
private:
    std::string name;
    unsigned long long _size;
    std::string creation_time;
    std::string access_time;
    std::string modification_time;

public:
    File(const std::string& _name,
         const unsigned long long _sz,
         const std::string& _creation_time,
         const std::string& _access_time,
         const std::string& _modification_time
    ): name(_name),
       _size(_sz),
       creation_time(_creation_time),
       access_time(_access_time),
       modification_time(_modification_time) {}

    std::string get_name() const {
        return name;
    }

    unsigned long long get_size() const {
        return _size;
    }

    std::string get_creation_time() const {
        return creation_time;
    }

    std::string get_modification_time() const {
        return modification_time;
    }

    std::string get_access_time() const {
        return access_time;
    }
};

enum class TimeTypes {
    CREATION_TIME,
    ACCESS_TIME,
    MODIFICATION_TIME
};

std::vector<File> parseFolder(const std::string& _path);
unsigned long long getFolderSize(const std::string& _path);
std::string getFileInfoTime(const std::string& path, TimeTypes);
