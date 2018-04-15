#ifndef REPORTS_H
#define REPORTS_H

void runTravelClassReports(struct Passenger* head, int travelClassType);
void runBornBeforeReport(struct Passenger* head, int bornBefore);
void runOrderedUKYearOfBirthReport(struct Passenger* head);

static int isAlreadyAdded(int *alreadyAdded, int numPassengers, int passportNumber);

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
