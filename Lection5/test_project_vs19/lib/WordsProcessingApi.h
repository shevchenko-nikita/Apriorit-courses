#pragma once
#include <map>
#include <string>

namespace api
{
    using WordsCount = std::map<std::string, int>;

    WordsCount CountWordsOccurrences(const std::string& str);
}