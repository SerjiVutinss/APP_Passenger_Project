#include "passenger.h"

#include<stdlib.h>
#include "structs.h"

// get all the passenger related data from the user and return a passenger pointer
struct Passenger* inputPassenger(int passportNumber) {
	int i;
	int userChoice = -1;
	struct Passenger* passenger;
	passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
	passenger->passportNumber = passportNumber;

	printf("Please enter the new Passenger's details:");

	// first name
	printf("\nFirst Name: ");
	scanf("%s", passenger->firstName);
	// last name
	printf("Last Name: ");
	scanf("%s", passenger->lastName);
	// year born
	printf("Year Born: ");
	scanf("%d", &passenger->yearBorn);
	
	getPassengerEditableInfo(passenger);

	return passenger;
}

static void getPassengerEditableInfo(struct Passenger* passenger) {

	int userChoice = -1;
	int i = 0;

	// email
	printf("Email address: ");
	scanf("%s", passenger->email);

	// select travel area
	do {
		printf("Which of the following areas did you travel from?");
		for (i = 0; i < NUM_TRAVEL_AREAS; i++) {
			printf("\n\t%d. %s", i + 1, travelAreas[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > NUM_TRAVEL_AREAS) {
			printf("\nThat was not a valid selection, please try again");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->travelledFrom = userChoice - 1; // offset since we need the array index
	userChoice = -1; // reset this variable for reuse

					 // select travel class
	do {
		printf("\nWhich travel class did you use to travel to Ireland?");
		for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
			printf("\n\t%d. %s", i + 1, travelClasses[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > NUM_TRAVEL_CLASSES) {
			printf("\nThat was not a valid selection, please try again");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->travelClass = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

					 // select number of trips
	do {
		printf("\nHow many trips to Ireland do you make per year?");
		for (i = 0; i < NUM_TRIPS_PER_YEAR; i++) {
			printf("\n\t%d. %s", i + 1, tripsPerYear[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > NUM_TRIPS_PER_YEAR) {
			printf("\nThat was not a valid selection, please try again");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->tripsPerYear = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

					 // select trip duration
	do {
		printf("\nOn average, how long is the duration of your trip?");
		for (i = 0; i < NUM_TRIP_DURATION; i++) {
			printf("\n\t%d. %s", i + 1, tripDuration[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > NUM_TRIP_DURATION) {
			printf("\nThat was not a valid selection, please try again");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->tripAvgDuration = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

}

// update the supplied passenger's details
void updatePassenger(struct Passenger* passenger) {
	int i; // for loop variable
	int userChoice = -1; // do while loop variable
	printf("Please enter the updated Passenger details:");

	getPassengerEditableInfo(passenger);
}

// display the supplied passenger's details
void displayPassenger(struct Passenger* passenger) {

	int padLen = 35;
	const char *padding = "                                                                     ";

	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|    Passport Number: %d\n", passenger->passportNumber, padLen);
	printf("\t|         First Name: %s\n", passenger->firstName, padLen);
	printf("\t|          Last Name: %s\n", passenger->lastName, padLen);
	printf("\t|          Year Born: %d\n", passenger->yearBorn, padLen);
	printf("\t|              Email: %s\n", passenger->email, padLen);

	// get item and print string from each array using the stored indices
	printf("\t|     Travelled From: %s\n", travelAreas[passenger->travelledFrom].value, padLen);
	printf("\t|       Travel Class: %s\n", travelClasses[passenger->travelClass].value, padLen);
	printf("\t|     Trips Per Year: %s\n", tripsPerYear[passenger->tripsPerYear].message, padLen);
	printf("\t| Avg. Trip Duration: %s\n", tripDuration[passenger->tripAvgDuration].message, padLen);
	printf("\t|-------------------------------------------------------------------------\n");
}

// return 1 if supplied string is a valid email format, else return 0
int isValidEmail(char emailAddress[]) {

	int l = strlen(emailAddress); // get length of supplied string
	if (emailAddress[l - 1] == ' ')
	{
		emailAddress[l - 1] = 0;
		--l;
	}
	int flag1 = 0, flag2 = 0;
	for (int i = 1; i < l; i++)
	{
		if (emailAddress[i] == '@')
			flag1 = 1;
		if (emailAddress[i] == '.') {
			flag2 = 1;
		}
	}
	if (flag1&&flag2) {
		return 1;
	}
	else {
		return 0;
	}
}