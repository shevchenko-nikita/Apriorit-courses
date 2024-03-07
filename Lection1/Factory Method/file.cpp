#include "file"

#include <windows.h>

std::string File::getName() const {
    return name;
}

unsigned long long File::getSize() const {
    return size_;
}

std::string File::getCreationTime() const {
    return creation_time;
}

std::string File::getModificationTime() const {
    return modification_time;
}

std::string File::getAccessTime() const {
    return access_time;
}

std::vector<File> Folder::parseFolder(const std::string& path) {
    std::vector<File> files;

    try {
        for (const auto &entry: std::filesystem::directory_iterator(path)) {
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

unsigned long long Folder::getFolderSize(const std::string& path) {
    unsigned long long sz = 0;

    try {
        for(const auto& entry : std::filesystem::directory_iterator(path)) {
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

std::string Folder::getFileInfoTime(const std::string& path, TimeTypes time_type) {
    WIN32_FILE_ATTRIBUTE_DATA ft_info;

    if (GetFileAttributesEx(path.c_str(), GetFileExInfoStandard, &ft_info)) {
        FILETIME ft_create = ft_info.ftCreationTime;
        FILETIME ft_access = ft_info.ftLastAccessTime;
        FILETIME ft_write = ft_info.ftLastWriteTime;

        SYSTEMTIME stUTC, stLocal;

        switch(time_type) {
            case(TimeTypes::CREATION_TIME):
                FileTimeToSystemTime(&ft_create, &stUTC);
                break;
            case(TimeTypes::ACCESS_TIME):
                FileTimeToSystemTime(&ft_access, &stUTC);
                break;
            case(TimeTypes::MODIFICATION_TIME):
                FileTimeToSystemTime(&ft_write, &stUTC);
                break;
        }

        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        std::string time_result = std::to_string(stLocal.wDay) + '.' +
                                  std::to_string(stLocal.wMonth) + '.' +
                                  std::to_string(stLocal.wYear) + '\\' +
                                  std::to_string(stLocal.wHour) + ':' +
                                  std::to_string(stLocal.wMinute) + ':' +
                                  std::to_string(stLocal.wSecond);

        return time_result;
    }
    else {
        return "Can't get time info";
    }
}

std::vector<File> Folder::getFilesList() {
    return files;
}
