#include "guard.h"

FileHandle::FileHandle(const std::string& path,
                       DWORD access_type,
                       DWORD share_mode,
                       LPSECURITY_ATTRIBUTES security_attributes,
                       DWORD creation_disposition,
                       DWORD flags_and_attributes,
                       HANDLE template_file)
{
    handle = CreateFile(path.c_str(),
                        access_type,
                        share_mode,
                        security_attributes,
                        creation_disposition,
                        flags_and_attributes,
                        template_file);

    if(handle == INVALID_HANDLE_VALUE) {
        std::cerr << "file is not opened" << std::endl;
        exit(1);
    }
}

FileHandle::~FileHandle() {
    if(handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
    }
}

HANDLE FileHandle::get() const {
    return handle;
}