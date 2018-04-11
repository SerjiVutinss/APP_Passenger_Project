#ifndef REPORTS
#define REPORTS

void runTravelClassReports(struct Passenger* head, int travelClassType);
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
#endif
