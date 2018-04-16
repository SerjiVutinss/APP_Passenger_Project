#include "validation.h"

#include<string.h>
#include<time.h>

// return 0 if string cannot be converted to int, else return converted value:
// the function can accept strings with a minus sign as first character, needed for
// the main menu exit option.
int stringToInt(char *s) {
	int i = 0, isNumeric = -1;
	// check if first character is a minus sign
	if (s[i] == '-') {
		i += 1; // if minus sign found, move to next char
	}
	// loop from current char
	while (s[i] != '\0') {
		if (isdigit(s[i])) {
			// if each char is a digit, keep looping
			i += 1;
		}
		else {
			// non-digit char found, return 0 from function
			return 0;
		}
	}
	// only get out of loop if entire string is numeric
	return atoi(s); // return the converted string to int
}

//must be greater than 2 chars and NOT contain any numbers
int isValidName(char name[50]) {

	int i, j; // loop counters
	int nameLength = strlen(name);
	// only validating for 2 chars in length at least and no numbers
	if (nameLength >= 2) {
		// loop through the string
		for (i = 0; i < nameLength; i++) {
			// and loop within to check for each number
			for (j = 0; j < 10; j++) {
				// if any number found, simply return 0
				if (name[i] == j + '0') {
					return 0;
				}
			}
		}
	}
	else { // length test failed
		return 0;
	}
	// all passed
	return 1;
}

// returns 1 if year is valid, i.e. greater than MIN_YEAR and less than or equal to current year
int isValidYear(int year) {
	return year > MIN_YEAR && year <= getCurrentYear();
}

// returns the current year as an int, e.g. 2018
int getCurrentYear() {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return timeinfo->tm_year + 1900;
}