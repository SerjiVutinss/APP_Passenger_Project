#include "database.h" // this file's header

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "structs.h" // structs and constants

FILE* dbFilePtr = NULL;

void backup(struct Passenger* head) {
	printf("\nOpening DB!!!\n");
	struct Passenger* curr = NULL; // pointer to current passenger
	//curr = (struct Passenger*)malloc(sizeof(struct Passenger*));

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
				printf("\nPassenger passport# %d backed up", curr->passportNumber);
				if (curr != NULL) {
					fprintf(dbFilePtr, "\n");
				}
				curr = curr->NEXT; // move along the list
			}
			printf("\nAll database records saved\n"); // finished displaying
			fclose(dbFilePtr);
			printf("\nDatabase File Closed!!!\n");
		}
		else {
			printf("The database is empty, nothing to save\n"); // no records found
			fclose(dbFilePtr);
			printf("\nDatabase File Closed!!!\n");
		}
	}
	else {
		printf("File could not be opened\n"); // no records found
	}
	dbFilePtr = NULL;
}

void restore(struct Passenger** head) {

	int count = 0; // keep a count of records added

	struct Passenger* newPassenger = NULL; // declare and allocate new Passenger
	//newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger*));
	dbFilePtr = fopen("database.txt", "r");
	if (dbFilePtr != NULL) {
		printf("\nDatabase File Opened!!!\n");

		while (!feof(dbFilePtr)) { // while we are not at the end of the file
			newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
			// read in one passenger per line
			fscanf(dbFilePtr, "%d %s %s %d %s %d %d %d %d\n",
				&newPassenger->passportNumber,
				newPassenger->firstName,
				newPassenger->lastName,
				&newPassenger->yearBorn,
				newPassenger->email,
				&newPassenger->travelledFrom,
				&newPassenger->travelClass,
				&newPassenger->tripsPerYear,
				&newPassenger->tripAvgDuration);

			//displayPassenger(newPassenger); // used for testing and debugging
			insert(head, newPassenger); // insert the passenger details into the ordered linked list
			count++; // increment the count

		}
		printf("\n%d database records read from file\n", count); // finished reading
		fclose(dbFilePtr);
	}

	else {
		printf("The database file is empty, nothing to read\n"); // no records found
	}
	dbFilePtr = NULL;
}

void insert(struct Passenger** head, struct Passenger* newPassenger) {

	struct Passenger* curr;

	if (passengerPassportExists(*head, newPassenger->passportNumber) == -1) {

		if (DEBUG_ON) {
			printf("\nInserting %d", newPassenger->passportNumber); // debugging
		}
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
		if (DEBUG_ON) {
			printf("\n\nPassenger inserted!!!!\n"); // debugging
		}
	}
	else {
		printf("Cannot insert, Passport number (%d) already in database", newPassenger->passportNumber);
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
	int count = 0; // used to display the number in the list
	curr = head; // set the current equal to the head


	if (curr != NULL) { // if list is not empty
		while (curr != NULL) { // while we are not at the ened of the list
			printf("\n\t| #%d\n", count + 1);
			displayPassenger(curr); // display the individual passenger
			curr = curr->NEXT; // move along the list
			count++;	// increment the counter
		}
		printf("\nAll %d database records displayed\n", count); // finished displaying
		printf("----------------------------------------------------------------------------------\n");
	}
	else {
		printf("The database is empty\n"); // no records found
	}
}

// search the list for a passport number and return the position if found, else return -1
int passengerPassportExists(struct Passenger* head, int passportNumber) {
	int count = 0;
	struct Passenger* curr;
	curr = head;

	if (curr != NULL) {
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