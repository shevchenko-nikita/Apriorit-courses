#pragma once
#include <windows.h>

class FileHandle {
private:
    HANDLE handle;

public:
    FileHandle(const std::string& path,
               DWORD access_type = GENERIC_READ,
               DWORD share_mode = 0,
               LPSECURITY_ATTRIBUTES security_attributes = nullptr,
               DWORD creation_disposition = CREATE_ALWAYS,
               DWORD flags_and_attributes = FILE_ATTRIBUTE_NORMAL,
               HANDLE template_file = nullptr);

    ~FileHandle();

    FileHandle(const FileHandle&) = delete;

    FileHandle& operator=(const FileHandle&) = delete;


    HANDLE get() const;

};

