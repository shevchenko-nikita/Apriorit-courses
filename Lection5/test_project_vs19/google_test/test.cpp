#include "pch.h"
#include "WordsProcessingApi.h"

TEST(WordsProcessingApi, CountWordsOccurrences_ReturnsNothingIfEmptyStringPassed)
{
    EXPECT_THROW(api::CountWordsOccurrences(""), std::exception);
}

TEST(WordsProcessingApi, CountWordsOccurrences_IncrementsOccurrencesCount)
{
    api::WordsCount expected = {
        { "one", 2 },
        { "two", 1 }
    };
    EXPECT_EQ(expected, api::CountWordsOccurrences("one two one"));

}

TEST(WordsProcessingApi, CountWordsOccurrences_DoesNotProcessManySpacesAsWords)
{
    api::WordsCount expected = {
        { "one", 1 },
        { "two", 1 }
    };
    EXPECT_EQ(expected, api::CountWordsOccurrences("one       two"));
}
