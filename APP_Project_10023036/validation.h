#ifndef VALIDATION_H
#define VALIDATION_H

// minimum year of birth
#define MIN_YEAR 1900

// return 0 if string cannot be converted to int, else return converted value:
// the function can accept strings with a minus sign as first character, needed for
// the main menu exit option.
int stringToInt(char *s);

//must be greater than 2 chars and NOT contain any numbers
int isValidName(char name[50]);

// returns 1 if year is valid, i.e. greater than MIN_YEAR and less than or equal to current year
int isValidYear(int year);

// returns the current year as an int, e.g. 2018
int getCurrentYear();

#endif // VALIDATION_H
