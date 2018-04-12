#ifndef DATABASE_H
#define DATABASE_H

//void readFileLines();

void backup(struct Passenger* head);
void restore(struct Passenger** head);


// inserts a passenger into the sorted linked list
void insert(struct Passenger** head, struct Passenger* newPassenger);

// deletes a passenger from the sorted linked list
void delete(struct Passenger** head, int passportNumber);

// print all elements in the list to the screen
void displayList(struct Passenger* head);

// search the list for an element with passportNumber and return index of the element, or -1 if not found
int passengerPassportExists(struct Passenger* head, int passportNumber);

// search the list for an element with full name and return index of the element, or -1 if not found
int passengerNameExists(struct Passenger* head, char firstName[], char lastName[]);

// return the length of the list
int getLength(struct Passenger* head);

// display a single passenger's details
void displayPassenger(struct Passenger* passenger);

// return a passenger by their index in the list
struct Passenger* getPassengerByIndex(struct Passenger* head, int index);

// get the inputs for a new passenger and return a pointer
struct Passenger* inputPassenger(int passportNumber);

#endif // DATABASE_H
