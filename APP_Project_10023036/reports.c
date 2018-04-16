#include"reports.h"
#include"structs.h"
#include "database.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Spec #6.I - Travel Class Report - takes in the user selected travelClassArray index and passes the 
// calculated data to showReport()
void runTravelClassReports(struct Passenger* head, int travelClassType) {

	int totalCount = 0;
	int countUK = 0;
	int countEurope = 0;
	int countAsia = 0;
	int countAfrica = 0;
	int countAmericas = 0;
	int countAustralasia = 0;
	int countOneDay = 0;
	int countLessThanThreeDays = 0;
	int countLessThanSevenDays = 0;
	int countMoreThanSevenDays = 0;

	travelClassType--;
	struct Passenger* curr; // pointer to current passenger
	curr = head; // set the current equal to the head

	if (curr != NULL) { // if list is not empty
		printf("\n");

		while (curr != NULL) { // while we are not at the ened of the list
			// check for supplied travel class type
			if (curr->travelClass == travelClassType) {
				totalCount++; // increment the total number of passengers with this travel class
				switch (curr->travelledFrom) { // build counts for each area travelled from
				case 0:
					countUK++;
					break;
				case 1:
					countEurope++;
					break;
				case 2:
					countAsia++;
					break;
				case 3:
					countAfrica++;
					break;
				case 4:
					countAmericas++;
					break;
				case 5:
					countAustralasia++;
					break;
				default:
					// should not happen!
					break;
				}

				switch (curr->tripAvgDuration) {
				case 0:
					countOneDay++;
					break;
				case 1:
					countLessThanThreeDays++;
					break;
				case 2:
					countLessThanSevenDays++;
					break;
				case 3:
					countMoreThanSevenDays++;
					break;
				default:
					// should not happen
					break;
				}
			}
			curr = curr->NEXT; // move along the list
		} // end while

		if (totalCount > 0) { // only show report if there are matches

			printf("\n\tShowing Travel Class Report for %s: ", travelClasses[travelClassType].value); // show this report
			printf("%d matches\n", totalCount);
			showReport(
				totalCount,
				countUK,
				countEurope,
				countAsia,
				countAfrica,
				countAmericas,
				countAustralasia,
				countOneDay,
				countLessThanThreeDays,
				countLessThanSevenDays,
				countMoreThanSevenDays
			);
		}
		else { // no matches for this report and criteria
			printf("\nNo matches for these criteria, nothing to display\n");
		}
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// Spec #6.II - Born Before 1980 Report - takes in the year and passes the 
// calculated data to showReport() - NOTE: Year is hardcoded as 1980 in main.c as per spec
void runBornBeforeReport(struct Passenger* head) {

	int totalCount = 0;
	int countUK = 0;
	int countEurope = 0;
	int countAsia = 0;
	int countAfrica = 0;
	int countAmericas = 0;
	int countAustralasia = 0;
	int countOneDay = 0;
	int countLessThanThreeDays = 0;
	int countLessThanSevenDays = 0;
	int countMoreThanSevenDays = 0;

	int bornBefore = 1980;

	//travelClassType--;
	struct Passenger* curr; // pointer to current passenger
	curr = head; // set the current equal to the head

	if (curr != NULL) { // if list is not empty
		printf("\n");

		while (curr != NULL) { // while we are not at the ened of the list
							   // check for supplied travel class type
			if (curr->yearBorn < bornBefore) {
				totalCount++; // increment the total number of passengers with this travel class
				switch (curr->travelledFrom) { // build counts for each area travelled from
				case 0:
					countUK++;
					break;
				case 1:
					countEurope++;
					break;
				case 2:
					countAsia++;
					break;
				case 3:
					countAfrica++;
					break;
				case 4:
					countAmericas++;
					break;
				case 5:
					countAustralasia++;
					break;
				default:
					// should not happen!
					break;
				}

				switch (curr->tripAvgDuration) {
				case 0:
					countOneDay++;
					break;
				case 1:
					countLessThanThreeDays++;
					break;
				case 2:
					countLessThanSevenDays++;
					break;
				case 3:
					countMoreThanSevenDays++;
					break;
				default:
					// should not happen
					break;
				}
			}
			curr = curr->NEXT; // move along the list
		} // end while

		if (totalCount > 0) { // only show report if there were matches

			printf("\n\tShowing Report for passengers born before 1980: "); // show this report
			printf("%d matches\n", totalCount);
			showReport(
				totalCount,
				countUK,
				countEurope,
				countAsia,
				countAfrica,
				countAmericas,
				countAustralasia,
				countOneDay,
				countLessThanThreeDays,
				countLessThanSevenDays,
				countMoreThanSevenDays
			);
		}
		else { // no matches for this report and criteria
			printf("\nNo matches for these criteria, nothing to display\n");
		}
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// SPEC #8 - List all the passengers travelling from the UK in order of year born
// This function calls the static method isAlreadyAdded() (below) and 
// the displayPassenger() function from passenger.h/c
void runOrderedUKYearOfBirthReport(struct Passenger* head) {

	int i = 0; // loop counter
	int year; // used to loop through the years
	int numPassengers = getLength(head); // total length of linked list

	// this will be used to keep track of which passengers have already been caught
	int* alreadyAdded = (int*)malloc(sizeof(int) * numPassengers);
	int numAdded = 0; // number of passport numbers already added to above array

	struct Passenger* curr; // pointer to current passenger
	curr = head; // set the current equal to the head

	if (curr != NULL) { // if list is not empty

		// for each year, loop through the linked list
		// assuming valid years of birth are 1900-2050 to limit number of loops
		for (year = 1900; year <= 2050; year++) {
			curr = head;
			while (curr != NULL) { // while we are not at the end of the list

				// if the year of birth is less than the current year and has travelled from UK
				if (curr->yearBorn < year && curr->travelledFrom == 0) {

					// check the already added array to see if this passportNumber has been added already
					for (i = 0; i < numPassengers; i++) {
						if (!isAlreadyAdded(alreadyAdded, numPassengers, curr->passportNumber)) {
							// passenger not already added
							*(alreadyAdded + numAdded) = curr->passportNumber; // add to array

							// and display the passenger's details (passenger.c)
							displayPassenger(curr);
							numAdded++; // increment so another passenger can be added
						}
					}
				}
				curr = curr->NEXT; // move the pointer along the list
			}
		}
		if (numAdded == 0) {
			printf("\nNothing to display for this report\n");
		}
	}
}

// helper function for above function:  returns 1 if the supplied passportNumber is found in the array
static int isAlreadyAdded(int *alreadyAdded, int numPassengers, int passportNumber) {

	int i = 0; // loop counter
	for (i = 0; i < numPassengers; i++) {
		if (passportNumber == alreadyAdded[i]) {
			return 1; // passport number found
		}
	}
	return 0; // no match found
}

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
) {

	float totalPercent = 100.0f;
	float percentUK = 0;
	float percentEurope = 0;
	float percentAsia = 0;
	float percentAfrica = 0;
	float percentAmericas = 0;
	float percentAustralasia = 0;
	float percentOneDay = 0;
	float percentLessThanThreeDays = 0;
	float percentLessThanSevenDays = 0;
	float percentMoreThanSevenDays = 0;

	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|   All figures shown as percentages (two decimal places)\n");
	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|   Area travelled from:\n");
	printf("\t|            UK: %.2f\n", (float)countUK / (float)totalCount * totalPercent);
	printf("\t|        Europe: %.2f\n", (float)countEurope / (float)totalCount * totalPercent);
	printf("\t|          Asia: %.2f\n", (float)countAsia / (float)totalCount * totalPercent);
	printf("\t|        Africa: %.2f\n", (float)countAfrica / (float)totalCount * totalPercent);
	printf("\t|      Americas: %.2f\n", (float)countAmericas / (float)totalCount * totalPercent);
	printf("\t|   Australasia: %.2f\n", (float)countAustralasia / (float)totalCount * totalPercent);
	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|   Average Trip duration:\n");
	printf("\t|       One Day: %.2f\n", (float)countOneDay / (float)totalCount * totalPercent);
	printf("\t|      < 3 Days: %.2f\n", (float)countLessThanThreeDays / (float)totalCount * totalPercent);
	printf("\t|      < 7 Days: %.2f\n", (float)countLessThanSevenDays / (float)totalCount * totalPercent);
	printf("\t|      > 7 Days: %.2f\n", (float)countMoreThanSevenDays / (float)totalCount * totalPercent);
	printf("\t|-------------------------------------------------------------------------\n");
	printf("\n");

}
