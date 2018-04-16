#ifndef DATABASE_H
#define DATABASE_H

/*  This file and its associated program file contain methods related to the
*   sorted linked list.
*
*  Functions in these files interact with the sorted linked - insertions, deletions, length,
*  getting elements by index, passport number or name
*
*/

// LIST FUNCTIONS

// inserts a passenger into the sorted linked list
void insert(struct Passenger** head, struct Passenger* newPassenger);
// deletes a passenger from the sorted linked list at a given index
void delete(struct Passenger** head, int index);
// return the number of elements in the list
int getLength(struct Passenger* head);

// return a pointer to a passenger at a given index
struct Passenger* getPassengerByIndex(struct Passenger* head, int index);
// search the list for an element with passportNumber and return index of the element, or -1 if not found
int passengerPassportExists(struct Passenger* head, int passportNumber);
// search the list for an element with full name and return index of the element, or -1 if not found
int passengerNameExists(struct Passenger* head, char firstName[], char lastName[]);
// display all passengers and details in the list - calls displayPassenger() (passenger.h/c)
void displayList(struct Passenger* head);

// END LIST FUNCTIONS


// FILE FUNCTIONS

// backup all passenger information to "database.txt"
void backup(struct Passenger* head);
// restore all passenger information from "database.txt"
void restore(struct Passenger** head);
// save all passenger details in readable report format to "passenger_details.txt"
void saveDetailsToFile(struct Passenger* head);

// END FILE FUNCTIONS

#endif // DATABASE_H
