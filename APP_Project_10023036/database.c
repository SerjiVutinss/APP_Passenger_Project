#include "database.h" // this file's header

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "structs.h" // structs and constants

FILE* dbFilePtr = NULL;
FILE* reportFilePtr = NULL;

// LIST FUNCTIONS

// inserts a passenger into the sorted linked list
void insert(struct Passenger** head, struct Passenger* newPassenger) {

	struct Passenger* curr; // create a passenger pointer

	// ensure that the passenger's passport number is not already in the list
	if (passengerPassportExists(*head, newPassenger->passportNumber) == -1) {

		if (DEBUG_ON) {
			printf("\nInserting %d", newPassenger->passportNumber); // debugging
		}
		// if list is empty OR if the new passport number is less than the existing head
		if (*head == NULL || newPassenger->passportNumber <= (*head)->passportNumber) {

			newPassenger->NEXT = *head; // insert at head
			*head = newPassenger; // and point the head to the new passenger
		}
		else {
			curr = *head; // find the node before the insertion point
			// not at end of list AND new passport number bigger than NEXT passport number
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

// deletes a passenger from the sorted linked list
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

// return the number of elements in the list
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

// return a pointer to a passenger at a given index
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

// search the list for a passport number and return the position if found, else return -1
int passengerPassportExists(struct Passenger* head, int passportNumber) {
	int count = 0;
	struct Passenger* curr;
	curr = head;

	if (curr != NULL) {
		while (curr != NULL) {
			if (curr->passportNumber == passportNumber) {
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

	// loop through the list
	if (curr != NULL) {
		while (curr != NULL) {
			// if first and last names match the supplied parameters, return the index
			if (strcmp(curr->lastName, lastName) == 0 && strcmp(curr->firstName, firstName) == 0) {
				// FOUND, return index
				return count;
			}
			curr = curr->NEXT;
			count++;
		}
	}
	// NOT FOUND, return -1
	return -1;
}

// display all passengers in the list - calls displayPassenger() (passenger.h/c)
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

// FILE FUNCTIONS

// backup all passenger information to "database.txt"
void backup(struct Passenger* head) {
	printf("\nOpening DB!!!\n");
	struct Passenger* curr = NULL; // pointer to current passenger

	dbFilePtr = fopen("database.txt", "w"); // open the database file
	if (dbFilePtr != NULL) { // ensure the file pointer was assigned
		printf("\nDatabase File Opened!!!\n");

		curr = head; // set the current equal to the head

		if (curr != NULL) { // 
			while (curr != NULL) { // while we are not at the end of the list

								   // Save one passenger per row:
								   //	print the passenger's details to the file, all on one line
								   //	NOTE: array indexes are used for the multiple-choice question answers
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

				// print to show each passenger saved
				printf("\nPassenger passport# %d backed up", curr->passportNumber);

				if (curr != NULL) { // begin a new line after all but the last passenger
					fprintf(dbFilePtr, "\n");
				}
				curr = curr->NEXT; // move along the list
			}
			printf("\nAll database records saved\n"); // finished displaying
			fclose(dbFilePtr); // close the file
			printf("\nDatabase File Closed!!!\n");
		}
		else { // curr was NULL, i.e. linked list is empty
			printf("The database is empty, nothing to save\n"); // no records found
			fclose(dbFilePtr); // close the file
			printf("\nDatabase File Closed!!!\n");
		}
	}
	else { // file pointer was NULL
		printf("File could not be opened\n"); // no records found
	}
	dbFilePtr = NULL; // set the file pointer to NULL regardless
}

// restore all passenger information from "database.txt"
void restore(struct Passenger** head) {

	int count = 0; // keep a count of records added
	struct Passenger* newPassenger = NULL; // declare new Passenger, which will be inserted to list
	int inputCount = -1;

	dbFilePtr = fopen("database.txt", "r"); // attempt to open the database file

											// TODO: HANDLE EMPTY FILE

	if (dbFilePtr != NULL) { // if file has been opened
		printf("\nDatabase File Opened!!!\n");

		while (!feof(dbFilePtr)) { // while we are not at the end of the file

								   // allocate and assign the new passenger
			newPassenger = (struct Passenger*)malloc(sizeof(struct Passenger));
			// read in one passenger per line
			inputCount = fscanf(dbFilePtr, "%d %s %s %d %s %d %d %d %d\n",
				&newPassenger->passportNumber,
				newPassenger->firstName,
				newPassenger->lastName,
				&newPassenger->yearBorn,
				newPassenger->email,
				&newPassenger->travelledFrom,
				&newPassenger->travelClass,
				&newPassenger->tripsPerYear,
				&newPassenger->tripAvgDuration);

			if (DEBUG_ON) { // used for testing and debugging
				displayPassenger(newPassenger); // print the passenger info to the screen
			}
			// ensure that the correct number of inputs were received
			// TODO: can check types of each input?
			if (inputCount == 9) {
				insert(head, newPassenger); // insert the passenger details into the ordered linked list
				count++; // increment the count
			}
			else {
				// TODO: can check types of each input?
				printf("Unable to read line from file\n");
			}
		}
		printf("\n%d database records read from file\n", count); // finished reading
		fclose(dbFilePtr); // close the file
	}

	else { // file was not opened correctly
		printf("The database file could not be opened, aborting restore!!\n"); // no records found
	}
	dbFilePtr = NULL; // reset the file pointer to NULL regardless
}

// save all passenger details in readable report format to "passenger_details.txt"
void saveDetailsToFile(struct Passenger* head) {
	printf("\nOpening DB!!!\n");
	struct Passenger* curr = NULL; // pointer to current passenger

	reportFilePtr = fopen("passenger_details.txt", "w");
	if (reportFilePtr != NULL) {
		printf("\nDetails File Opened!!!\n");

		curr = head; // set the current equal to the head

		if (curr != NULL) {
			while (curr != NULL) { // while we are not at the end of the list

				// save one passenger
				fprintf(reportFilePtr, "\t|-------------------------------------------------------------------------\n");
				fprintf(reportFilePtr, "\t|    Passport Number: %d\n", curr->passportNumber);
				fprintf(reportFilePtr, "\t|         First Name: %s\n", curr->firstName);
				fprintf(reportFilePtr, "\t|          Last Name: %s\n", curr->lastName);
				fprintf(reportFilePtr, "\t|          Year Born: %d\n", curr->yearBorn);
				fprintf(reportFilePtr, "\t|              Email: %s\n", curr->email);

				// get item and print string from each array using the stored indices
				fprintf(reportFilePtr, "\t|     Travelled From: %s\n", travelAreas[curr->travelledFrom].value);
				fprintf(reportFilePtr, "\t|       Travel Class: %s\n", travelClasses[curr->travelClass].value);
				fprintf(reportFilePtr, "\t|     Trips Per Year: %s\n", tripsPerYear[curr->tripsPerYear].message);
				fprintf(reportFilePtr, "\t| Avg. Trip Duration: %s\n", tripDuration[curr->tripAvgDuration].message);


				printf("\nPassenger passport# %d saved to details file", curr->passportNumber);
				if (curr != NULL) {
					fprintf(reportFilePtr, "\n");
				}
				curr = curr->NEXT; // move along the list
			}
			printf("\nAll details saved to file\n"); // finished displaying
			fclose(reportFilePtr);
			printf("\nDetails File Closed!!!\n");
		}
		else {
			printf("The database is empty, nothing to save to details file\n"); // no records found
			fclose(reportFilePtr);
			printf("\nDetails File Closed!!!\n");
		}
	}
	else {
		printf("File could not be opened\n"); // no records found
	}
	reportFilePtr = NULL;
}

// END FILE FUNCTIONS