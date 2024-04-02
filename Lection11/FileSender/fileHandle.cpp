#include "fileHandle.h"

HANDLE getFileHandle(const char* file_name, DWORD flag) {
    auto handle = CreateFile(file_name,
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             NULL,
                             flag,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);

    if(handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Fail during opening file" << std::endl;
        exit(1);
    }

    return handle;
}