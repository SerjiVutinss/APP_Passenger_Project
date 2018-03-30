#include"reports.h"
#include"structs.h"

#include<stdio.h>
#include<string.h>

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

				// perform the calculations
			}


			curr = curr->NEXT; // move along the list
		}
		printf("\nAll database records displayed\n"); // finished displaying
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}