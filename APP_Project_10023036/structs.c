#include<string.h>
#include<limits.h>

#include "structs.h"

void initialiseArrays() {

	// travel areas
	travelAreas[0].key = 0;
	strcpy(travelAreas[0].value, "U.K.");

	travelAreas[1].key = 1;
	strcpy(travelAreas[1].value, "Rest of Europe");

	travelAreas[2].key = 2;
	strcpy(travelAreas[2].value, "Asia");

	travelAreas[3].key = 3;
	strcpy(travelAreas[3].value, "Africa");

	travelAreas[4].key = 4;
	strcpy(travelAreas[4].value, "Americas");

	travelAreas[5].key = 5;
	strcpy(travelAreas[5].value, "Australasia");

	// travel areas
	travelClasses[0].key = 0;
	strcpy(travelClasses[0].value, "Economy");

	travelClasses[1].key = 1;
	strcpy(travelClasses[1].value, "Premium Economy");

	travelClasses[2].key = 2;
	strcpy(travelClasses[2].value, "Business Class");

	travelClasses[3].key = 3;
	strcpy(travelClasses[3].value, "First Class");

	// trips per year
	tripsPerYear[0].key = 0;
	tripsPerYear[0].minVal = 0;
	tripsPerYear[0].maxVal = 2;
	strcpy(tripsPerYear[0].message, "Less than 3 times");

	tripsPerYear[1].key = 1;
	tripsPerYear[1].minVal = 3;
	tripsPerYear[1].maxVal = 5;
	strcpy(tripsPerYear[1].message, "Less than 5 times");

	tripsPerYear[2].key = 2;
	tripsPerYear[2].minVal = 5;
	tripsPerYear[2].maxVal = INT_MAX;
	strcpy(tripsPerYear[2].message, "More than 5 times");

	// trip duration
	tripDuration[0].key = 0;
	tripDuration[0].minVal = 1;
	tripDuration[0].maxVal = 1;
	strcpy(tripDuration[0].message, "One day");

	tripDuration[1].key = 1;
	tripDuration[1].minVal = 2;
	tripDuration[1].maxVal = 2;
	strcpy(tripDuration[1].message, "Less than 3 days");

	tripDuration[2].key = 2;
	tripDuration[2].minVal = 3;
	tripDuration[2].maxVal = 7;
	strcpy(tripDuration[2].message, "Less than 7 days");

	tripDuration[3].key = 3;
	tripDuration[3].minVal = 7;
	tripDuration[3].maxVal = INT_MAX;
	strcpy(tripDuration[3].message, "More than 7 days");
}

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