#ifndef STRUCTS
#define STRUCTS_H

/* This file and its associated program file contain program constants, definitions of 
 * all structs used in the program and the initialisation of the struct arrays which 
 * are hold the data used in the passenger detail questions e.g. Travel Class, Travel Area, etc
 */


#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 7 // includes room for termination character

/* these constants are used to define the struct array sizes, easily loop through these arrays,
 * and also to validate that user input is within bounds of the array, e.g. the inputPassenger()
 * function in passenger.h
 */
#define NUM_TRAVEL_AREAS 6
#define NUM_TRAVEL_CLASSES 4
#define NUM_TRIPS_PER_YEAR 3
#define NUM_TRIP_DURATION 4

// this can be changed to 1 to display more verbose messages, e.g. when data is being
// backed up or restored to/from the database.txt file
#define DEBUG_ON 0

// initialise and populate the helper arrays with data
void initialiseArrays();


// user struct used for login purposes
typedef struct User {
	char username[USERNAME_MAX_LEN];
	char password[PASSWORD_MAX_LEN];
} User;

// passenger struct which populate the sorted linked list
struct Passenger {
	int passportNumber; // this will be unique within the linked list
	char firstName[50];
	char lastName[50];
	int yearBorn;
	char email[50]; // this needs to be validated as email address format
	// additional info, saved as indexed values
	int travelledFrom;
	int travelClass;
	int tripsPerYear;
	int tripAvgDuration;
	struct Passenger* NEXT;
};


struct TravelArea {
	int key;
	char value[50];
};

struct TravelClass {
	int key;
	char value[50];
};

struct TripDuration {
	int key;
	int minVal;
	int maxVal;
	char message[50];
};

struct TripsPerYear {
	int key;
	int minVal;
	int maxVal;
	char message[50];
};

// define the struct arrays of data for use in passenger details
struct TravelArea travelAreas[NUM_TRAVEL_AREAS];
struct TravelClass travelClasses[NUM_TRAVEL_CLASSES];
struct TripsPerYear tripsPerYear[NUM_TRIPS_PER_YEAR];
struct TripDuration tripDuration[NUM_TRIP_DURATION];

#endif // STRUCTS_H