#ifndef VALIDATION_H
#define VALIDATION_H

//#include "structs.h"

/*  This file and its associated program file contain methods related to the
*	validation of passenger details and related constants
*  
*  
*/

// minimum year of birth
#define MIN_YEAR 1900

// return 0 if string cannot be converted to int, else return converted value:
// the function can accept strings with a minus sign as first character, needed for
// the main menu exit option.  I have used a pointer as a parameter here
int stringToInt(char *s);

// must be greater than 2 chars and NOT contain any numbers, I have used a char array as a parameter here
// +1 for terminator - hardcoding this rather than using CONSTANT because had trouble importing
int isValidName(char name[51]);

// returns 1 if year is valid, i.e. greater than MIN_YEAR and less than or equal to current year
int isValidYear(int year);

// returns the current year as an int, e.g. 2018
int getCurrentYear();

#endif // VALIDATION_H
