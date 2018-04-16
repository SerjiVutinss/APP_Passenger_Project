#ifndef REPORTS_H
#define REPORTS_H

/*  This file and its associated program file contain methods related to the
*   reports within the application.
*
*   The three report functions in these files read from the sorted linked list and 
*   pass the relevant data to the showReport() function based on their input parameters
*/

// Spec #6.I - Travel Class Report - takes in the user selected travelClassArray index and passes the 
// calculated data to showReport()
void runTravelClassReports(struct Passenger* head, int travelClassType);
// Spec #6.II - Born Before 1980 Report - passes the calculated data to showReport() 
// NOTE: Year is hardcoded in function as 1980 as per spec
void runBornBeforeReport(struct Passenger* head);
// SPEC #8 - List all the passengers travelling from the UK in order of year born
// This function calls the static method isAlreadyAdded() (below) and 
// the displayPassenger() function from passenger.h/c
void runOrderedUKYearOfBirthReport(struct Passenger* head);

// helper function for above function:  returns 1 if the supplied passportNumber is found in the array
static int isAlreadyAdded(int *alreadyAdded, int numPassengers, int passportNumber);

// method only run from this file: shows the report using the supplied data
// Called from TravelClass and BornBefore Report functions
static void showReport(
	int totalCount,
	int countUK,
	int countEurope,
	int countAsia,
	int countAfrica,
	int countAmericas,
	int countAustralasia,
	int countOneDay,
	int countLessThanThreeDays,
	int countLessThanSevenDays,
	int countMoreThanSevenDays
);

#endif // REPORTS_H
