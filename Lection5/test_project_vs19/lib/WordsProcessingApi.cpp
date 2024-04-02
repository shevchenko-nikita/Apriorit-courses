#include "pch.h"
#include "WordsProcessingApi.h"

api::WordsCount api::CountWordsOccurrences(const std::string & str)
{
    if (str.empty())
    {
        
        throw std::exception("empty value passed");
    }

    api::WordsCount result;
    std::istringstream fullStr(str);
    std::string word;

    while (std::getline(fullStr, word, ' '))
    {
        if (!word.empty())
        {
            ++result[word];
        }
    }

    return result;
}
