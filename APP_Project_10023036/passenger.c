#include "passenger.h"

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "structs.h"
#include "validation.h"


// get all the passenger related data from the user and return a passenger pointer
struct Passenger* inputPassenger(int passportNumber) {
	int i;
	int userChoice = -1;
	char userInput[USERNAME_MAX_LEN]; // use this to validate year of birth
	int yearOfBirth = 0;
	int nameLength = 0;
	int nameIsValid = 0;
	struct Passenger* passenger;
	passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
	passenger->passportNumber = passportNumber;

	printf("Please enter the new Passenger's details:");

	// first name validation
	do {
		printf("\nFirst Name: ");
		scanf("%s", userInput);
		//nameLength = strlen(userInput);
		nameIsValid = isValidName(userInput);

		if (nameIsValid) {
			strcpy(passenger->firstName, userInput);
		}
		else {
			printf("\nInvalid input: names must be at least 2 characters long and cannot contain numbers\n");
		}
	} while (!nameIsValid);

	// last name validation
	do {
		printf("\nLast Name: ");
		scanf("%s", userInput);
		//nameLength = strlen(userInput);
		nameIsValid = isValidName(userInput);

		if (nameIsValid) {
			strcpy(passenger->lastName, userInput);
		}
		else {
			printf("\nInvalid input: names must be at least 2 characters long and cannot contain numbers\n");
		}
	} while (!nameIsValid);


	// year born validation
	do {
		printf("Year Born: ");
		scanf(" %s", userInput);
		yearOfBirth = stringToInt(userInput);
		if (isValidYear(yearOfBirth)) {
			passenger->yearBorn = yearOfBirth;
		}
		else {
			printf("\nThat was not a valid year of birth, valid years \n");
			printf("are years between %d and %d inclusive.\n", MIN_YEAR, getCurrentYear());
		}
	} while (!isValidYear(yearOfBirth));

	// call the static method in this file
	getPassengerEditableInfo(passenger);

	// return the new passenger
	return passenger;
}

// update the supplied passenger's details
void updatePassenger(struct Passenger* passenger) {
	int i; // for loop variable
	int userChoice = -1; // do while loop variable
	printf("Please enter the updated Passenger details:");

	// call the static method in this file
	getPassengerEditableInfo(passenger);
}

// function to set the user's editable details
// only called from this file so static - no return type since struct is updated
static void getPassengerEditableInfo(struct Passenger* passenger) {

	char userInput[USERNAME_MAX_LEN + 1];
	int userChoice = -1;
	int emailIsValid = -1;
	int i = 0;

	// validate email address
	do {
		// email
		printf("\nEmail address: ");
		scanf("%s", passenger->email);

		emailIsValid = isValidEmail(passenger->email);
		if (!emailIsValid) {
			printf("That is not a valid email address, please try again\n");
		}
		else {
			printf("Email address accepted\n");
		}
	} while (emailIsValid != 1);

	// select travel area - loop until valid choice entered
	do {
		printf("Which of the following areas did you travel from?");
		for (i = 0; i < NUM_TRAVEL_AREAS; i++) {
			printf("\n\t%d. %s", i + 1, travelAreas[i].value);
		}
		printf("\nPlease select: ");
		scanf(" %s", userInput); // get the input
		userChoice = stringToInt(userInput); // validate as integer

		if (userChoice <= 0 || userChoice > NUM_TRAVEL_AREAS) {
			printf("\n\nThat was not a valid selection, please try again!\n");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->travelledFrom = userChoice - 1; // offset since we need the array index
	userChoice = -1; // reset this variable for reuse

	// select travel class- loop until valid choice entered
	do {
		printf("\nWhich travel class did you use to travel to Ireland?");
		for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
			printf("\n\t%d. %s", i + 1, travelClasses[i].value);
		}
		printf("\nPlease select: ");
		scanf(" %s", userInput); // get the input
		userChoice = stringToInt(userInput); // validate as integer

		if (userChoice <= 0 || userChoice > NUM_TRAVEL_CLASSES) {
			printf("\n\nThat was not a valid selection, please try again!\n");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->travelClass = userChoice - 1; // offset since we need the array index
	userChoice = -1; // reset this variable for reuse

	// select number of trips - loop until valid choice entered
	do {
		printf("\nHow many trips to Ireland do you make per year?");
		for (i = 0; i < NUM_TRIPS_PER_YEAR; i++) {
			printf("\n\t%d. %s", i + 1, tripsPerYear[i].message);
		}
		printf("\nPlease select: ");
		scanf(" %s", userInput); // get the input
		userChoice = stringToInt(userInput); // validate as integer

		if (userChoice <= 0 || userChoice > NUM_TRIPS_PER_YEAR) {
			printf("\n\nThat was not a valid selection, please try again!\n");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->tripsPerYear = userChoice - 1; // offset since we need the array index
	userChoice = -1; // reset this variable for reuse

	// select trip duration - loop until valid choice entered
	do {
		printf("\nOn average, how long is the duration of your trip?");
		for (i = 0; i < NUM_TRIP_DURATION; i++) {
			printf("\n\t%d. %s", i + 1, tripDuration[i].message);
		}
		printf("\nPlease select: ");
		scanf(" %s", userInput); // get the input
		userChoice = stringToInt(userInput); // validate as integer

		if (userChoice <= 0 || userChoice > NUM_TRIP_DURATION) {
			printf("\n\nThat was not a valid selection, please try again!\n");
			userChoice = -1;
		}

	} while (userChoice == -1);
	passenger->tripAvgDuration = userChoice - 1; // offset since we need the array index
	userChoice = -1; // reset this variable for reuse
}

// display the supplied passenger's details
void displayPassenger(struct Passenger* passenger) {

	printf("\t|-------------------------------------------------------------------------\n");
	printf("\t|    Passport Number: %d\n", passenger->passportNumber);
	printf("\t|         First Name: %s\n", passenger->firstName);
	printf("\t|          Last Name: %s\n", passenger->lastName);
	printf("\t|          Year Born: %d\n", passenger->yearBorn);
	printf("\t|              Email: %s\n", passenger->email);

	// get item and print string from each array using the stored indices
	printf("\t|     Travelled From: %s\n", travelAreas[passenger->travelledFrom].value);
	printf("\t|       Travel Class: %s\n", travelClasses[passenger->travelClass].value);
	printf("\t|     Trips Per Year: %s\n", tripsPerYear[passenger->tripsPerYear].message);
	printf("\t| Avg. Trip Duration: %s\n", tripDuration[passenger->tripAvgDuration].message);
	printf("\t|-------------------------------------------------------------------------\n");
}

// return 1 if supplied string is a valid email format, else return 0
int isValidEmail(char emailAddress[]) {

	int retVal = 0;

	int hasSpace = 0;
	int atPos = -1;
	int dotPos = -1;
	int l = strlen(emailAddress); // get length of supplied string

	if (emailAddress[l - 1] == ' ')
	{
		emailAddress[l - 1] = 0;
		--l;
	}
	for (int i = 1; i < l; i++)
	{
		if (emailAddress[i] == ' ') {
			hasSpace = 1;
		}

		if (emailAddress[i] == '@') {
			atPos = i;
		}
		if (emailAddress[i] == '.') {
			dotPos = i;
		}
	}

	if ((hasSpace != 1) && (dotPos > (atPos + 1))) {
		return 1;
	}
	return 0;
}