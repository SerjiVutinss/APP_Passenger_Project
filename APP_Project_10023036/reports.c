#include "reports.h"
#include "structs.h"
#include "passenger.h"
#include "database.h"
#include "validation.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Spec #6.I - Travel Class Report - takes in the user selected travelClassArray index and passes the 
// calculated data to showReport()
void runTravelClassReport(struct Passenger* head, int travelClassType, int saveToFile) {

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

	char reportTitle[100];

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

		//if (totalCount > 0) { // only show report if there are matches


		sprintf(reportTitle, "Showing Travel Class Report for %s: ", travelClasses[travelClassType].value); // show this report

		showSaveReport(
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
			countMoreThanSevenDays,
			reportTitle,
			saveToFile
		);
		//}
		//else { // no matches for this report and criteria
		//	printf("\nNo matches for these criteria, nothing to display\n");
		//}
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// Spec #6.II - Born Before 1980 Report - takes in the year and passes the 
// calculated data to showReport() - NOTE: Year is hardcoded as 1980 in main.c as per spec
void runBornBeforeReport(struct Passenger* head, int saveToFile) {

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

	char reportTitle[100];

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

		//if (totalCount > 0) { // only show report if there were matches
			//printf("\n\tShowing Report for passengers born before 1980: "); // show this report

		sprintf(reportTitle, "Showing Report for passengers born before 1980: ");

		showSaveReport(
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
			countMoreThanSevenDays,
			reportTitle,
			saveToFile
		);
		//}
		//else { // no matches for this report and criteria
		//	printf("\nNo matches for these criteria, nothing to display\n");
		//}
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// SPEC #8 - List all the passengers travelling from the UK in order of year born
// This function calls the static method isAlreadyAdded() (below) and 
// the displayPassenger() function from passenger.h/c
void runOrderedUKYearOfBirthReport(struct Passenger* head, int saveToFile) {

	int i = 0; // loop counter
	int year; // used to loop through the years
	int numPassengers = getLength(head); // total length of linked list

	// this will be used to keep track of which passengers have already been caught
	int* alreadyAdded = (int*)malloc(sizeof(int) * numPassengers);
	int numAdded = 0; // number of passport numbers already added to above array

	struct Passenger* curr; // pointer to current passenger
	curr = head; // set the current equal to the head

	//FILE* reportFilePtr = NULL;
	char lineBreak[100] = "\n\t|-------------------------------------------------------------------------\n";
	char reportTitle[100] = "All passengers travelling from the UK in order of year born (ASC): ";

	printf("%s", lineBreak);
	printf("\n\t| %s", reportTitle);
	printf("%s", lineBreak);

	/*if (saveToFile == 1) {
		reportFilePtr = fopen("report.txt", "w");
		if (reportFilePtr != NULL) {
			fprintf(reportFilePtr, "%s", lineBreak);
			fprintf(reportFilePtr, "\n\t| %s", reportTitle);
			fprintf(reportFilePtr, "%s", lineBreak);
		}
	}*/

	if (curr != NULL) { // if list is not empty

		// for each year, loop through the linked list
		// assuming valid years of birth are 1900-2050 to limit number of loops
		for (year = MIN_YEAR; year <= getCurrentYear() + 1; year++) {
			curr = head;
			while (curr != NULL) { // while we are not at the end of the list

				// if the year of birth is less than the current year and has travelled from UK
				if (curr->yearBorn < year && curr->travelledFrom == 0) {

					// check the already added array to see if this passportNumber has been added already
					for (i = 0; i < numPassengers; i++) {
						if (!isAlreadyAdded(alreadyAdded, numPassengers, curr->passportNumber)) {
							// passenger not already added
							*(alreadyAdded + numAdded) = curr->passportNumber; // add to array

							//// and save or display the passenger's details (passenger.c)
							//if (saveToFile == 1) { // don't display, only save
							//	if (reportFilePtr != NULL) {
							//		fprintf(reportFilePtr, "\t|    Passport Number: %d\n", curr->passportNumber);
							//		fprintf(reportFilePtr, "\t|         First Name: %s\n", curr->firstName);
							//		fprintf(reportFilePtr, "\t|          Last Name: %s\n", curr->lastName);
							//		fprintf(reportFilePtr, "\t|          Year Born: %d\n", curr->yearBorn);
							//		fprintf(reportFilePtr, "\t|              Email: %s\n", curr->email);

							//		// get item and print string from each array using the stored indices
							//		fprintf(reportFilePtr, "\t|     Travelled From: %s\n", travelAreas[curr->travelledFrom].value);
							//		fprintf(reportFilePtr, "\t|       Travel Class: %s\n", travelClasses[curr->travelClass].value);
							//		fprintf(reportFilePtr, "\t|     Trips Per Year: %s\n", tripsPerYear[curr->tripsPerYear].message);
							//		fprintf(reportFilePtr, "\t| Avg. Trip Duration: %s", tripDuration[curr->tripAvgDuration].message);
							//		fprintf(reportFilePtr, "%s", lineBreak);
							//		numAdded++; // increment so another passenger can be added
							//	}
							//}
							//else {
							printf("\n\t| Year: %d\n", curr->yearBorn);
								displayPassenger(curr);
								numAdded++; // increment so another passenger can be added
							//}
						}
					}
				}
				curr = curr->NEXT; // move the pointer along the list
			}
		}
		if (numAdded == 0) { // if no records match, inform user
			/*if (saveToFile == 1) {
				fprintf(reportFilePtr, "\nNothing to display for this report\n");
			}
			else {*/
				printf("\nNothing to display for this report\n");
			//}
		}
		//if (reportFilePtr != NULL) { // close file if open
		//	fclose(reportFilePtr);
		//}
		//reportFilePtr = NULL;
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
static void showSaveReport(
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
	int countMoreThanSevenDays,
	char reportTitle[100],
	int saveToFile // if 1, also save report to file
) {
	FILE* reportFilePtr = NULL;

	// calculate the report statistics
	float percentUK = calculatePercentage(countUK, totalCount);
	float percentEurope = calculatePercentage(countEurope, totalCount);
	float percentAsia = calculatePercentage(countAsia, totalCount);
	float percentAfrica = calculatePercentage(countAfrica, totalCount);
	float percentAmericas = calculatePercentage(countAmericas, totalCount);
	float percentAustralasia = calculatePercentage(countAustralasia, totalCount);
	float percentOneDay = calculatePercentage(countOneDay, totalCount);
	float percentLessThanThreeDays = calculatePercentage(countLessThanThreeDays, totalCount);
	float percentLessThanSevenDays = calculatePercentage(countLessThanSevenDays, totalCount);
	float percentMoreThanSevenDays = calculatePercentage(countMoreThanSevenDays, totalCount);

	char lineBreak[100] = "\n\t|-------------------------------------------------------------------------\n";

	// only save to file
	if (saveToFile == 1) {
		reportFilePtr = fopen("report.txt", "w");

		// make sure the file was opened correctly
		if (reportFilePtr != NULL) {

			// if there were no matches for the criteria
			if (totalCount == 0) { 
				// print message to file
				fprintf(reportFilePtr, "Nothing to display for this report\n");
			}
			// print report to file
			else {
				
				fprintf(reportFilePtr, "%s", lineBreak);
				fprintf(reportFilePtr, "\t| %s", reportTitle);
				fprintf(reportFilePtr, "%d matches", totalCount);
				fprintf(reportFilePtr, "%s", lineBreak);
				fprintf(reportFilePtr, "\t|   Area travelled from:\n");
				fprintf(reportFilePtr, "\t|            UK: %.2f\n", percentUK);
				fprintf(reportFilePtr, "\t|        Europe: %.2f\n", percentEurope);
				fprintf(reportFilePtr, "\t|          Asia: %.2f\n", percentAsia);
				fprintf(reportFilePtr, "\t|        Africa: %.2f\n", percentAfrica);
				fprintf(reportFilePtr, "\t|      Americas: %.2f\n", percentAmericas);
				fprintf(reportFilePtr, "\t|   Australasia: %.2f", percentAustralasia);
				fprintf(reportFilePtr, "%s", lineBreak);
				fprintf(reportFilePtr, "\t|   Average Trip duration:\n");
				fprintf(reportFilePtr, "\t|       One Day: %.2f\n", percentOneDay);
				fprintf(reportFilePtr, "\t|      < 3 Days: %.2f\n", percentLessThanThreeDays);
				fprintf(reportFilePtr, "\t|      < 7 Days: %.2f\n", percentLessThanSevenDays);
				fprintf(reportFilePtr, "\t|      > 7 Days: %.2f", percentMoreThanSevenDays);
				fprintf(reportFilePtr, "%s", lineBreak);
				fprintf(reportFilePtr, "\n");
				fclose(reportFilePtr);
			}

			// inform the user that something was saved to the output file
			printf("\nData saved to 'report.txt'\n");
		}
		// file not opened
		else {
			printf("\nThere was a problem openeing the output file!\n");
		}
		reportFilePtr = NULL; // set to NULL regardless
	}
	// only print the report to screen
	else {
		// if there were no matches for the criteria
		if (totalCount == 0) {
			// print message to screen
			printf("Nothing to display for this report\n");
		}
		// print report to screen
		else {
			printf("%s", lineBreak);
			printf("\t| %s", reportTitle);
			printf("%d matches", totalCount);
			printf("%s", lineBreak);
			printf("\t|   Area travelled from:\n");
			printf("\t|            UK: %.2f\n", percentUK);
			printf("\t|        Europe: %.2f\n", percentEurope);
			printf("\t|          Asia: %.2f\n", percentAsia);
			printf("\t|        Africa: %.2f\n", percentAfrica);
			printf("\t|      Americas: %.2f\n", percentAmericas);
			printf("\t|   Australasia: %.2f", percentAustralasia);
			printf("%s", lineBreak);
			printf("\t|   Average Trip duration:\n");
			printf("\t|       One Day: %.2f\n", percentOneDay);
			printf("\t|      < 3 Days: %.2f\n", percentLessThanThreeDays);
			printf("\t|      < 7 Days: %.2f\n", percentLessThanSevenDays);
			printf("\t|      > 7 Days: %.2f", percentMoreThanSevenDays);
			printf("%s", lineBreak);
			printf("\n");
		}
	}
}

static float calculatePercentage(int count, int totalCount) {
	return (float)count / (float)totalCount * TOTAL_PERCENT;
}
