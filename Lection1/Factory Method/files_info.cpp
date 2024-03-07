#include "files_info.h"

#include <windows.h>

std::vector<File> parseFolder(const std::string& _path) {
    std::vector<File> files;

    try {
        for (const auto &entry: std::filesystem::directory_iterator(_path)) {
            auto name = entry.path().filename().string();

            auto file_size = entry.is_directory()
                             ? getFolderSize(entry.path().string())
                             : entry.file_size();

            auto creation_time = getFileInfoTime(entry.path().string(), TimeTypes::CREATION_TIME);
            auto access_time = getFileInfoTime(entry.path().string(), TimeTypes::ACCESS_TIME);
            auto modification_time = getFileInfoTime(entry.path().string(), TimeTypes::MODIFICATION_TIME);

            files.push_back(
                    File(name,file_size, creation_time, access_time, modification_time)
            );
        }
    }
    catch(const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return files;
}

unsigned long long getFolderSize(const std::string& _path) {
    unsigned long long sz = 0;

    try {
        for(const auto& entry : std::filesystem::directory_iterator(_path)) {
            if(entry.is_directory()) {
                sz += getFolderSize(entry.path().string());
            }
            else {
                sz += entry.file_size();
            }
        }
    }
    catch(const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return sz;
}

std::string getFileInfoTime(const std::string& _path, TimeTypes time_type) {
    WIN32_FILE_ATTRIBUTE_DATA ftInfo;

    if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &ftInfo)) {
        FILETIME ftCreate = ftInfo.ftCreationTime;
        FILETIME ftAccess = ftInfo.ftLastAccessTime;
        FILETIME ftWrite = ftInfo.ftLastWriteTime;

        SYSTEMTIME stUTC, stLocal;

        if(time_type == TimeTypes::CREATION_TIME) {
            FileTimeToSystemTime(&ftCreate, &stUTC);
        }
        else if(time_type == TimeTypes::ACCESS_TIME) {
            FileTimeToSystemTime(&ftAccess, &stUTC);
        }
        else {
            FileTimeToSystemTime(&ftWrite, &stUTC);
        }

        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        std::string _time = std::to_string(stLocal.wDay) + '.' +
                            std::to_string(stLocal.wMonth) + '.' +
                            std::to_string(stLocal.wYear) + '\\' +
                            std::to_string(stLocal.wHour) + ':' +
                            std::to_string(stLocal.wMinute) + ':' +
                            std::to_string(stLocal.wSecond);

        return _time;
    }
    else {
        return "Can't get time info";
    }
}
