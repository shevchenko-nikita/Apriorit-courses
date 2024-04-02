#include "pch.h"

#include "IsLeapYear.h"

TEST(TestIsLeapYear, IncorrectValue) {
	EXPECT_FALSE(IsLeapYear(0));
}

TEST(TestIsLeapYear, LeapYear) {
	EXPECT_TRUE(IsLeapYear(12));
	EXPECT_TRUE(IsLeapYear(400));
	EXPECT_TRUE(IsLeapYear(2000));
	EXPECT_TRUE(IsLeapYear(2140));
	EXPECT_TRUE(IsLeapYear(2004));
}

TEST(TestIsLeapYear, NotLeapYear) {
	EXPECT_FALSE(IsLeapYear(15));
	EXPECT_FALSE(IsLeapYear(100));
	EXPECT_FALSE(IsLeapYear(1000));
	EXPECT_FALSE(IsLeapYear(2023));
}