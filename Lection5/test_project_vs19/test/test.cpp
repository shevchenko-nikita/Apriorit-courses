// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WordsProcessingApi.h"

int main()
{
    try
    {
        api::WordsCount expected1 = {
        { "one", 2 },
        { "two", 1 }
        };
        if (expected1 != api::CountWordsOccurrences("one two one"))
        {
            throw std::exception("CountWordsOccurrences does not increment occurrences count");
        }

        api::WordsCount expected2 = {
            { "one", 1 },
            { "two", 1 }
        };
        if (expected2 != api::CountWordsOccurrences("one       two"))
        {
            throw std::exception("CountWordsOccurrences process many spaces as words");
        }

        std::cout << "SUCCESS" << std::endl << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "FAILED" << std::endl;
        std::cout << "ERROR: " << ex.what() << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
