/*
	  Title:	Advanced Procedural Programming Project 2018
	 Course:	Software Development Semester 4
	Student:	Justin Servis
		 ID:	10023036
	  Email:	10023036@gmit.ie
*/

// standard libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// custom libraries
#include "structs.h" // the data structures and globals used all across the program
#include "login.h" // the login module handles all login related tasks
#include "database.h" // linked list (database) operations
#include "reports.h" // reporting related functions
#include "passenger.h"

  // will be used to read the login_details.txt file
User* users; // will be used to contain all users read in from the file

int menuDisplayUpdate(struct Passenger* headPtr, int type);

// main function
int main() {


	struct Passenger* headPtr = NULL;

	int i;
	int menuSelection = 0; // main menu loop
	int qryPassportNumber, queryResult; // used to perform lookups
	char qryFirstName[50], qryLastName[50];
	int searchType = 0;
	int reportType = 0;
	int travelClassType = 0;

	initialiseArrays();

	/*char email1[25] = "jservis";
	char email2[25] = "a.com@gmail";
	char email3[25] = "asdd@l.com";

	printf("\n%s is %d\n\n", email1, isValidEmail(email1));
	printf("\n%s is %d\n\n", email2, isValidEmail(email2));
	printf("\n%s is %d\n\n", email3, isValidEmail(email3));*/

	restore(&headPtr);

	////// start login loop
	//runLoginLoop();
	////// end login loop

	//// start main menu
	do {
		// display all menu options
		printf("\nMain Menu\n");
		printf("1. Add a new passenger\n");
		printf("2. Display all passengers\n");
		printf("3. Display a passenger's details\n");
		printf("4. Update a passenger\n");
		printf("5. Delete a passenger\n");
		printf("6. Display Reports\n");
		printf("7. Save all details to file\n");
		printf("8. List all passengers travelling from the U.K. in order of their birth year\n");
		printf("-1 to exit the application\n");

		// get the user's choice
		printf("\nPlease choose an option: ");
		scanf("%d", &menuSelection);
		printf("\n");
		switch (menuSelection) {
		case 1:
			printf("Add a new passenger\n");
			// ask for the passenger's passport number before continuing
			printf("Please enter the passenger's passport number: ");
			scanf("%d", &qryPassportNumber);
			queryResult = passengerPassportExists(headPtr, qryPassportNumber);
			if (queryResult == -1) {
				// passport number not found, proceed with insertion, passing in the passport number
				insert(&headPtr, inputPassenger(qryPassportNumber));
			}
			else {
				// passport number was found, cannot insert
				printf("\nA passenger with passport number %d already exists, aborting\n", qryPassportNumber);
			}
			break;
		case 2:
			printf("Display all passengers:\n");
			// print out all passenger details
			displayList(headPtr);
			break;
		case 3:
			printf("Display a passenger's details\n");
			// get input and display passenger
			menuDisplayUpdate(headPtr, 0);
			break;
		case 4:
			printf("Update a passenger\n");
			// get input and update passenger
			menuDisplayUpdate(headPtr, 1);
			break;
		case 5:
			printf("Delete a passenger\n");
			// ask for the passenger's passport number before continuing
			printf("Please enter the passenger's passport number: ");
			scanf("%d", &qryPassportNumber);
			queryResult = passengerPassportExists(headPtr, qryPassportNumber);
			if (queryResult != -1) {
				// passenger found, proceed with deletion, passing in the passport number
				delete(&headPtr, queryResult);
			}
			else {
				printf("\nA passenger with passport number %d was not found, aborting\n", qryPassportNumber);
			}
			break;
		case 6:
			printf("Display Reports\n");

			do {
				printf("Which set of reports would you like to see?\n");
				printf("1. Travel Class\n");
				printf("2. Born Before 1980\n");
				printf("Please select: ");
				scanf("%d", &reportType);

				if (reportType == 1) {
					// by travel class
					do {
						printf("Please select the travel class:\n");
						for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
							printf("%d. %s\n", i + 1, travelClasses[i].value);
						}
						printf("Please select: ");
						scanf("%d", &travelClassType);

						if (travelClassType < 1 || travelClassType > NUM_TRAVEL_CLASSES) {
							printf("That was not a valid selection, please try again\n");
						}

					} while (travelClassType < 1 || travelClassType > NUM_TRAVEL_CLASSES);

					// valid travel class selected - run report
					runTravelClassReports(headPtr, travelClassType);
				}
				else if (reportType == 2) {
					// born before 1980
					runBornBeforeReport(headPtr, 1980);
				}

			} while (reportType < 1 && reportType>2);
			break;
		case 7:
			printf("Save all details to file\n");
			break;
		case 8:
			printf("List all passengers travelling from the U.K. in order of their birth year\n");
			runOrderedUKYearOfBirthReport(headPtr);
			break;
		case -1:
			printf("Exiting\n");
			break;
		default:
			printf("That was not a valid choice, please try again");
		}

		// open to editing
	} while (menuSelection != -1);

	//// end main menu

	backup(headPtr); // write the database contents to file

	// exit program
	printf("\n\nProgram Terminating...\n\n");
	return 0;
}

// search for and either display or update a passenger
int menuDisplayUpdate(struct Passenger* headPtr, int type) {
	// if(type==0) display
	// if(type==1) update

	int searchType = -1;
	int qryPassportNumber, qryResult;
	char qryFirstName[50], qryLastName[50];

	do {
		printf("How would you like to search:\n");
		printf("1. Passport Number\n");
		printf("2. Full Name\n");
		printf("Please select: ");
		scanf("%d", &searchType);

		switch (searchType) {
		case 1:
			// find by Passport Number
			printf("Please enter the passenger's passport number: ");
			scanf("%d", &qryPassportNumber);
			qryResult = passengerPassportExists(headPtr, qryPassportNumber);
			if (qryResult != -1) {
				// passenger found, proceed with update or display, passing in the passport number
				if (type == 1) {
					updatePassenger(getPassengerByIndex(headPtr, qryResult));
				}
				else {
					displayPassenger(getPassengerByIndex(headPtr, qryResult));
				}
			}
			else {
				printf("\nA passenger with passport number %d was not found, aborting\n", qryPassportNumber);
			}
			break;
		case 2:
			// find by Full Name
			printf("Please enter the passenger's first name: ");
			scanf("%s", &qryFirstName);
			printf("Please enter the passenger's last name: ");
			scanf("%s", &qryLastName);
			qryResult = passengerNameExists(headPtr, qryFirstName, qryLastName);
			if (qryResult != -1) {
				// passenger found, proceed with update, passing in the passport number
				if (type == 1) {
					updatePassenger(getPassengerByIndex(headPtr, qryResult));
				}
				else {
					displayPassenger(getPassengerByIndex(headPtr, qryResult));
				}
			}
			else {
				printf("\nA passenger with passport number %d was not found, aborting\n", qryPassportNumber);
			}
			break;
		}

	} while (searchType < 1 || searchType > 2);
	searchType = 0; // reset this variable
}