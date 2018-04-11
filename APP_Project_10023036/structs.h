#ifndef STRUCTS
#define STRUCTS

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 7 // includes room for termination character

#define NUM_TRAVEL_AREAS 6
#define NUM_TRAVEL_CLASSES 4
#define NUM_TRIPS_PER_YEAR 3
#define NUM_TRIP_DURATION 4

// initialise and populate the helper arrays with data
void initialiseArrays();
int isValidEmail(char emailAddress[]);

typedef struct User {
	char username[USERNAME_MAX_LEN];
	char password[PASSWORD_MAX_LEN];
} User;

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


struct TravelArea travelAreas[NUM_TRAVEL_AREAS];
struct TravelClass travelClasses[NUM_TRAVEL_CLASSES];
struct TripsPerYear tripsPerYear[NUM_TRIPS_PER_YEAR];
struct TripDuration tripDuration[NUM_TRIP_DURATION];

#endif