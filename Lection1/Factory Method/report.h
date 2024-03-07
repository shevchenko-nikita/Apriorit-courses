#pragma once

#include <memory>

#include "file.h"

class FileReport {
public:
    virtual void generate(const std::string& path) const = 0;
    virtual ~FileReport() = default;
};

