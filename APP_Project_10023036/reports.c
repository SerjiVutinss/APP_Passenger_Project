#include"reports.h"
#include"structs.h"

#include<stdio.h>
#include<string.h>

// method only run from this file
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
	printf("\t|   All figures shown as percentages\n");
	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|            UK: %.2f\n", (float)countUK / (float)totalCount * totalPercent);
	printf("\t|        Europe: %.2f\n", (float)countEurope / (float)totalCount * totalPercent);
	printf("\t|          Asia: %.2f\n", (float)countAsia / (float)totalCount * totalPercent);
	printf("\t|        Africa: %.2f\n", (float)countAfrica / (float)totalCount * totalPercent);
	printf("\t|      Americas: %.2f\n", (float)countAmericas / (float)totalCount * totalPercent);
	printf("\t|   Australasia: %.2f\n", (float)countAustralasia / (float)totalCount * totalPercent);
	printf("\t|       One Day: %.2f\n", (float)countOneDay / (float)totalCount * totalPercent);
	printf("\t|      < 3 Days: %.2f\n", (float)countLessThanThreeDays / (float)totalCount * totalPercent);
	printf("\t|      < 7 Days: %.2f\n", (float)countLessThanSevenDays / (float)totalCount * totalPercent);
	printf("\t|      > 7 Days: %.2f\n", (float)countMoreThanSevenDays / (float)totalCount * totalPercent);
	printf("\t|-------------------------------------------------------------------------\n");
	printf("\n");

}

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

				// perform the calculations
			}


			curr = curr->NEXT; // move along the list
		} // end while

		printf("%d %d %d %d %d %d %d %d %d %d", totalCount,
			countUK,
			countEurope,
			countAsia,
			countAfrica,
			countAmericas,
			countAustralasia,
			countOneDay,
			countLessThanThreeDays,
			countLessThanSevenDays,
			countMoreThanSevenDays);

		printf("\nShowing Travel Class Report:\n"); // finished displaying
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
	else {
		printf("The database is empty\n"); // no records found
	}
}

