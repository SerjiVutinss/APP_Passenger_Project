#ifndef PASSENGER_H
#define PASSENGER_H

/*  This file and its associated program file contain methods related to the
 *  input of passenger details and displaying a single passenger's details.
 *
 *  Functions in these files DO NOT interact with the sorted linked list in any way -
 *	for example, inputPassenger() returns a passenger pointer which is then inserted
 *  into the list using the insert() function in database.h
 */

// get all the passenger related data from the user and return the pointer
// - calls getPassengerEditableInfo()
struct Passenger* inputPassenger(int passportNumber);

// update the supplied passenger's details - calls getPassengerEditableInfo()
void updatePassenger(struct Passenger* passengerToUpdate);

// called by inputPassenger() and updatePassenger() - only used in these files
static void getPassengerEditableInfo(struct Passenger* passenger);

// display the supplied passenger's details
void displayPassenger(struct Passenger* passenger);

// return 1 if supplied string is a valid email format, else return 0
int isValidEmail(char emailAddress[]);

int Check_Email_Addr(char *EM_Addr);

#endif // PASSENGER_H

