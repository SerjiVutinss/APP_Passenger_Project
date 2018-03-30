#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "database.h"
#include "structs.h"

FILE* dbFilePtr = NULL;

void backup(struct Passenger* head) {
	printf("\nOpening DB!!!\n");
	struct Passenger* curr; // pointer to current passenger
	dbFilePtr = fopen("database.txt", "w");
	if (dbFilePtr != NULL) {
		printf("\nDatabase File Opened!!!\n");

		curr = head; // set the current equal to the head

		if (curr != NULL) {
			while (curr != NULL) { // while we are not at the end of the list
				// save one passenger per row

				//if (curr->passportNumber > 0) {
				fprintf(dbFilePtr, "%d %s %s %d %s %d %d %d %d",
					curr->passportNumber,
					curr->firstName,
					curr->lastName,
					curr->yearBorn,
					curr->email,
					curr->travelledFrom,
					curr->travelClass,
					curr->tripsPerYear,
					curr->tripAvgDuration
				);
				if (curr->NEXT != NULL) {
					fprintf(dbFilePtr, "\n");
				}
				curr = curr->NEXT; // move along the list
			}
			printf("\nAll database records saved\n"); // finished displaying
		}
		else {
			printf("The database is empty, nothing to save\n"); // no records found
		}
	}
	else {
		printf("File could not be opened\n"); // no records found
	}
	fclose(dbFilePtr);
	dbFilePtr = NULL;
}

void restore(struct Passenger** head) {

	char line[100];

	struct Passenger* newPassenger; // declare and allocate new Passenger
	newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger*));

	dbFilePtr = fopen("database.txt", "r");
	if (dbFilePtr != NULL) {
		printf("\nDatabase File Opened!!!\n");

		while (!feof(dbFilePtr)) { // while we are not at the end of the file
			// read in one passenger per line

			//fgets(line, sizeof(line), dbFilePtr);
			//printf("%s", line);

			printf("FOUND PASSENGER");
			fscanf(dbFilePtr, " %d %s %s %d %s %d %d %d %d\n",
				&newPassenger->passportNumber,
				newPassenger->firstName,
				newPassenger->lastName,
				&newPassenger->yearBorn,
				newPassenger->email,
				&newPassenger->travelledFrom,
				&newPassenger->travelClass,
				&newPassenger->tripsPerYear,
				&newPassenger->tripAvgDuration);

			displayPassenger(newPassenger);
			insert(head, newPassenger);

			newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger*));
		}
		printf("\nAll database records read from file\n"); // finished reading
	}

	else {
		printf("The database file is empty, nothing to read\n"); // no records found
	}
	fclose(dbFilePtr);
	dbFilePtr = NULL;
}

void insert(struct Passenger** head, struct Passenger* passengerToInsert) {

	struct Passenger* newPassenger; // declare and allocate new Passenger
	newPassenger = passengerToInsert;

	if (passengerPassportExists(*head, newPassenger->passportNumber) == -1) {

		printf("\nInserting %d", newPassenger->passportNumber);
		struct Passenger* curr;
		// if list is empty OR if the new passport number is less than the existing head
		if (*head == NULL || newPassenger->passportNumber <= (*head)->passportNumber) {
			// insert at head
			newPassenger->NEXT = *head;
			*head = newPassenger;
		}
		else {
			curr = *head; // find the node before the insertion point
			// not at end of list AND new passport number bigger than current
			while (curr->NEXT != NULL && newPassenger->passportNumber > curr->NEXT->passportNumber) {
				// move along the list
				curr = curr->NEXT;
			}
			// we must be at the right point, link the new passenger in to the next position
			newPassenger->NEXT = curr->NEXT;
			curr->NEXT = newPassenger;
		}
		printf("\n\nPassenger inserted!!!!");
	}
	else {
		printf("Cannot insert, Passport number already in database");
	}
}

void delete(struct Passenger** head, int index) {
	int i;
	struct Passenger* curr;
	struct Passenger* prev;
	curr = *head;
	// at head of list
	if (index == 0) {
		*head = curr->NEXT;
		free(curr);
	}
	else {
		// anywhere else
		for (i = 0; i < index; i++) {
			prev = curr;
			curr = curr->NEXT;
		}
		prev->NEXT = curr->NEXT;
		free(curr);
	}
}

struct Passenger* inputPassenger(int passportNumber) {
	int i;
	int userChoice = -1;
	struct Passenger* newPassenger;
	newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
	newPassenger->passportNumber = passportNumber;

	printf("Please enter the new Passenger's details:");

	// first name
	printf("\nFirst Name: ");
	scanf("%s", newPassenger->firstName);
	// last name
	printf("Last Name: ");
	scanf("%s", newPassenger->lastName);
	// year born
	printf("Year Born: ");
	scanf("%d", &newPassenger->yearBorn);
	// email
	printf("Email address: ");
	scanf("%s", newPassenger->email);

	// select travel area
	do {
		printf("Which of the following areas did you travel from?");
		for (i = 0; i < NUM_TRAVEL_AREAS; i++) {
			printf("\n\t%d. %s", i + 1, travelAreas[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRAVEL_AREAS)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	newPassenger->travelledFrom = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

	// select travel class
	do {
		printf("\nWhich travel class did you use to travel to Ireland?");
		for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
			printf("\n\t%d. %s", i + 1, travelClasses[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRAVEL_CLASSES)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	newPassenger->travelClass = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

	// select number of trips
	do {
		printf("\nHow many trips to Ireland do you make per year?");
		for (i = 0; i < NUM_TRIPS_PER_YEAR; i++) {
			printf("\n\t%d. %s", i + 1, tripsPerYear[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRIPS_PER_YEAR)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	newPassenger->tripsPerYear = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

	// select trip duration
	do {
		printf("\nOn average, how long is the duration of your trip?");
		for (i = 0; i < NUM_TRIP_DURATION; i++) {
			printf("\n\t%d. %s", i + 1, tripDuration[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRIP_DURATION)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	newPassenger->tripAvgDuration = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

	return newPassenger;
}

void update(struct Passenger* passengerToUpdate) {
	int i; // for loop variable
	int userChoice = -1; // do while loop variable
	printf("Please enter the updated Passenger details:");

	// email
	printf("Email address: ");
	scanf("%s", passengerToUpdate->email);

	// select travel area
	do {
		printf("Which of the following areas did you travel from?");
		for (i = 0; i < NUM_TRAVEL_AREAS; i++) {
			printf("\n\t%d. %s", i + 1, travelAreas[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRAVEL_AREAS)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	passengerToUpdate->travelledFrom = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

					 // select travel class
	do {
		printf("\nWhich travel class did you use to travel to Ireland?");
		for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
			printf("\n\t%d. %s", i + 1, travelClasses[i].value);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRAVEL_CLASSES)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	passengerToUpdate->travelClass = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

					 // select number of trips
	do {
		printf("\nHow many trips to Ireland do you make per year?");
		for (i = 0; i < NUM_TRIPS_PER_YEAR; i++) {
			printf("\n\t%d. %s", i + 1, tripsPerYear[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRIPS_PER_YEAR)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	passengerToUpdate->tripsPerYear = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

					 // select trip duration
	do {
		printf("\nOn average, how long is the duration of your trip?");
		for (i = 0; i < NUM_TRIP_DURATION; i++) {
			printf("\n\t%d. %s", i + 1, tripDuration[i].message);
		}
		printf("\nPlease select: ");
		scanf("%d", &userChoice);

		if (!(userChoice > 0 && userChoice <= NUM_TRIP_DURATION)) {
			printf("\nThat was not a valid selection, please try again");
		}
		else {
			userChoice == -1;
		}

	} while (userChoice == -1);
	passengerToUpdate->tripAvgDuration = userChoice - 1;
	userChoice = -1; // reset this variable for reuse

}

struct Passenger* getPassengerByIndex(struct Passenger* head, int index) {

	int i;
	struct Passenger* curr;
	curr = head;

	// anywhere else
	for (i = 0; i < index; i++) {
		curr = curr->NEXT;
	}
	return curr;
}

// display all passengers in the list
void displayList(struct Passenger* head) {

	struct Passenger* curr; // pointer to current passenger
	curr = head; // set the current equal to the head

	if (curr != NULL) { // if list is not empty
		printf("\n");
		while (curr != NULL) { // while we are not at the ened of the list
			displayPassenger(curr); // display the individual passenger
			curr = curr->NEXT; // move along the list
		}
		printf("\nAll database records displayed\n"); // finished displaying
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// display the supplied passenger's details
void displayPassenger(struct Passenger* passenger) {
	printf("\tPassport Number: %d\n", passenger->passportNumber);
	printf("\tFirst Name: %s\n", passenger->firstName);
	printf("\tLast Name: %s\n", passenger->lastName);
	printf("\tYear Born: %d\n", passenger->yearBorn);
	printf("\tLast Name: %s\n", passenger->email);

	// get item and print string from each array using the stored indices
	printf("\tTravelled From: %s\n", travelAreas[passenger->travelledFrom].value);
	printf("\tTravel Class: %s\n", travelClasses[passenger->travelClass].value);
	printf("\tTrips Per Year: %s\n", tripsPerYear[passenger->tripsPerYear].message);
	printf("\tAvg. Trip Duration: %s\n", tripDuration[passenger->tripAvgDuration].message);
}


// search the list for a passport number and return the position if found, else return -1
int passengerPassportExists(struct Passenger* head, int passportNumber) {
	int count = 0;
	struct Passenger* curr;
	curr = head;

	if (curr != NULL) {
		printf("\n");
		while (curr != NULL) {
			if (curr->passportNumber == passportNumber) {
				// FOUND
				printf("\n\nFOUND\n\n");
				return count;
			}
			curr = curr->NEXT;
			count++;
		}
	}
	// NOT FOUND
	return -1;
}

// search the list for a passenger full name and return the position if found, else return -1
int passengerNameExists(struct Passenger* head, char firstName[], char lastName[]) {
	int count = 0;
	struct Passenger* curr;
	curr = head;

	if (curr != NULL) {
		printf("\n");
		while (curr != NULL) {
			if (strcmp(curr->lastName, lastName) == 0 && strcmp(curr->firstName, firstName) == 0) {
				// FOUND
				return count;
			}
			curr = curr->NEXT;
			count++;
		}
	}
	// NOT FOUND
	return -1;
}

int getLength(struct Passenger* head) {
	int count = 0;
	struct Passenger* curr;
	curr = head;

	if (curr != NULL) {
		while (curr != NULL) {
			curr = curr->NEXT;
			count++;
		}
	}
	return count;
}