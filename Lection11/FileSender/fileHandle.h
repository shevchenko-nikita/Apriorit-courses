#pragma once

#include <iostream>
#include <windows.h>

HANDLE getFileHandle(const char* file_name, DWORD desired_access);