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

	int userChoice = -1;
	int emailIsValid = -1;
	int i = 0;

	// validate email address
	do {
		// email
		printf("Email address: ");
		scanf("%s", passenger->email);

		emailIsValid = isValidEmail(passenger->email);
		if (!emailIsValid) {
			printf("That is not a valid email address, please try again\n");
		}
		else {
			printf("Email address accepted\n");
		}
	}
	while (emailIsValid != 1);

	// select travel area - loop until valid choice entered
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

	// select travel class- loop until valid choice entered
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

	// select number of trips - loop until valid choice entered
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

	// select trip duration - loop until valid choice entered
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

int Check_Email_Addr(char *EM_Addr) {
	int count = 0;
	int i = 0;
	char conv_buf[50];
	char *c, *domain;
	char *special_chars = "()<>@,;:\"[]";

	/* The input is in EBCDIC so convert to ASCII first */
	//strcpy(conv_buf, EM_Addr);
	//EtoA(conv_buf);
	///* convert the special chars to ASCII */
	//EtoA(special_chars);

	for (c = conv_buf; *c; c++) {
		/* if '"' and beginning or previous is a '.' or '"' */
		if (*c == 34 && (c == conv_buf || *(c - 1) == 46 || *(c - 1) == 34)) {
			while (*++c) {
				/* if '"' break, End of name */
				if (*c == 34)
					break;
				/* if '' and ' ' */
				if (*c == 92 && (*++c == 32))
					continue;
				/* if not between ' ' & '~' */
				if (*c <= 32 || *c > 127)
					return 0;
			}
			/* if no more characters error */
			if (!*c++)
				return 0;
			/* found '@' */
			if (*c == 64)
				break;
			/* '.' required */
			if (*c != 46)
				return 0;
			continue;
		}
		if (*c == 64) {
			break;
		}
		/* make sure between ' ' && '~' */
		if (*c <= 32 || *c > 127) {
			return 0;
		}
		/* check special chars */
		if (strchr(special_chars, *c)) {
			return 0;
		}
	} /* end of for loop */
	  /* found '@' */
	  /* if at beginning or previous = '.' */
	if (c == conv_buf || *(c - 1) == 46)
		return 0;
	/* next we validate the domain portion */
	/* if the next character is NULL */
	/* need domain ! */
	if (!*(domain = ++c))
		return 0;
	do {
		/* if '.' */
		if (*c == 46) {
			/* if beginning or previous = '.' */
			if (c == domain || *(c - 1) == 46)
				return 0;
			/* count '.' need at least 1 */
			count++;
		}
		/* make sure between ' ' and '~' */
		if (*c <= 32 || *c >= 127)
			return 0;
		if (strchr(special_chars, *c))
			return 0;
	} while (*++c); /* while valid char */
	return (count >= 1); /* return true if more than 1 '.' */
}