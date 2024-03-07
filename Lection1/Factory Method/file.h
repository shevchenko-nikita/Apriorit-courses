#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class File {
private:
    std::string name;
    unsigned long long size_;
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
       size_(_sz),
       creation_time(_creation_time),
       access_time(_access_time),
       modification_time(_modification_time) {}

    std::string getName() const;
    unsigned long long getSize() const;
    std::string getCreationTime() const;
    std::string getModificationTime() const;
    std::string getAccessTime() const;
};

enum class TimeTypes {
    CREATION_TIME,
    ACCESS_TIME,
    MODIFICATION_TIME
};

class Folder {
private:
    std::vector<File> files;

    std::vector<File> parseFolder(const std::string& path);
    unsigned long long getFolderSize(const std::string& path);
    std::string getFileInfoTime(const std::string& path, TimeTypes);

public:
    Folder(const std::string& path) : files(parseFolder(path)) {}

    std::vector<File> getFilesList();
};
