#include "pch.h"
#include "IsLeapYear.h"


bool IsLeapYear(unsigned int year) {
	if (year == 0) {
		return false;
	}

	if (year % 400 == 0) {
		return true;
	}

	if (year % 4 == 0 && year % 100) {
		return true;
	}

	return false;
}