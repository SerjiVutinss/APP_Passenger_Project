/*
	  Title:	Advanced Procedural Programming Project 2018
	 Course:	Software Development Semester 4
	Student:	Justin Servis
		 ID:	10023036
	  Email:	10023036@gmit.ie
*/

/*
 * This file contains the main method for program execution.
 *
 * After variable declaration, the data arrays used by the program are initialised
 * by calling the initialiseArrays() function from structs.h/c
 *
 * The login loop is then run from login.h/c to authneticate the user against the details in login_details.txt
 *
 * Once a user has been authenticated, the main menu loop is run and the user is asked to make a selection:
 *   * The user must enter an integer
 *   * The user make a valid selection from the list of options
 *
*/

// standard libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// custom libraries
#include "structs.h" // the data structures and globals used all across the program
#include "login.h" // the login module handles all login related tasks
#include "database.h" // linked list (database) operations
#include "reports.h" // reporting related functions
#include "passenger.h"
#include "validation.h"

  // will be used to read the login_details.txt file
User* users; // will be used to contain all users read in from the file

int menuDisplayUpdate(struct Passenger* headPtr, int type);

// main function
int main() {
	
	//// BEGIN Variable Declarations
	// head of the linked list
	struct Passenger* headPtr = NULL;

	int i; // loop counter
	int menuSelection = 0; // main menu loop
	int qryPassportNumber, queryResult; // used to perform lookups on passengers

	// used to store user input for menu selections to be validated - 
	// it is most often passed in to the stringToInt() function (structs.h/c)
	char userInput[USERNAME_MAX_LEN];

	// used to perform lookup of a passenger with existing first and last name
	char qryFirstName[50], qryLastName[50];

	// used to store menu choices
	int searchType = 0;
	int reportType = 0;
	int travelClassType = 0;
	//// END Variable Declarations


	// initialise data arrays used for passenger details
	initialiseArrays(); // function in structs.h/c

	// restore any records contained in database.txt
	restore(&headPtr); // function in database.h/c

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
		//scanf("%d", &menuSelection);

		scanf(" %s", userInput);
		menuSelection = stringToInt(userInput);

		printf("\n");
		switch (menuSelection) {
		case 1:
			printf("Add a new passenger - Passport number must be greater than 0\n");
			// ask for the passenger's passport number before continuing
			printf("Please enter the passenger's passport number: ");
			scanf(" %s", userInput); // get the input
			qryPassportNumber = stringToInt(userInput); // returns 0 if cannot convert to int

			if (qryPassportNumber != 0) { // if a valid passport number was entered

				// check to see if this passport number already exists in linked list
				queryResult = passengerPassportExists(headPtr, qryPassportNumber);

				if (queryResult == -1) { // passport number not found
					// proceed with passenger input followed by insertion
					// inputPassenger() in passenger.c/h asks user for input of user details
					// insert() in database.h/c inserts the passenger into the sorted linked list
					insert(&headPtr, inputPassenger(qryPassportNumber));
				}
				else {
					// passport number was found, ask user if they would like to update the existing details
					printf("\nA passenger with passport number %d already exists, would you like to update this user's details?\n", qryPassportNumber);

					do {
						// print options
						printf("1. Yes\n");
						printf("2. No\n");

						printf("Please select: ");
						scanf(" %s", userInput); // get user input
						menuSelection = stringToInt(userInput); // check to see if a number was entered

						switch (menuSelection) // decide what to do
						{
						case 1:
							// get a pointer to the passenger to be updated and update details
							updatePassenger(getPassengerByIndex(headPtr, queryResult));
						default:
							break;
						}

						if (menuSelection < 1 || menuSelection > 2) { // invalid option
							printf("\nThat was not a valid option, please try again\n");
						}

					} while (menuSelection < 1 || menuSelection > 2); // valid option not selected
					menuSelection = 0; // reset this variable to 0

				}
			}
			else { // passport number was not a valid number
				printf("\nAn invalid passport number was entered, aborting\n");
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
			menuDisplayUpdate(headPtr, 0); // function in this file after main()
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
			scanf(" %s", userInput); // get the input
			qryPassportNumber = stringToInt(userInput); // returns 0 if cannot convert to int

			if (qryPassportNumber != 0) { // if a valid passport number was entered
			// set query result to the index of the passenger if found, else it will be -1
				queryResult = passengerPassportExists(headPtr, qryPassportNumber);

				if (queryResult != -1) { // passenger was found
					// passenger found, proceed with deletion, passing in the position in the list, i.e. index
					delete(&headPtr, queryResult);
					printf("Passenger with Passport Number %d was deleted\n", qryPassportNumber);
				}
				else { // passenger not found
					printf("\nA passenger with passport number %d was not found, aborting\n", qryPassportNumber);
				}
			}
			else {
				// passport number was not a valid number
				printf("\nAn invalid passport number was entered, aborting\n");
			}
			break;
		case 6:
			printf("Display Reports\n");

			do { // loop until valid input received
				printf("Which set of reports would you like to see?\n");
				printf("1. Travel Class\n");
				printf("2. Born Before 1980\n");
				printf("Please select: ");
				scanf(" %s", userInput); // get the input
				reportType = stringToInt(userInput); // returns 0 if cannot convert to int

				if (reportType == 1) {
					// by travel class
					do {
						printf("Please select the travel class:\n");
						for (i = 0; i < NUM_TRAVEL_CLASSES; i++) {
							printf("%d. %s\n", i + 1, travelClasses[i].value);
						}
						printf("Please select: ");
						scanf(" %s", userInput); // get the input
						travelClassType = stringToInt(userInput); // returns 0 if cannot convert to int

						// validate input was a list option
						if (travelClassType < 1 || travelClassType > NUM_TRAVEL_CLASSES) {
							printf("That was not a valid selection, please try again\n"); // loop
						}

					} while (travelClassType < 1 || travelClassType > NUM_TRAVEL_CLASSES);

					// valid travel class selected - run report - reports.h/c
					runTravelClassReports(headPtr, travelClassType);
				}
				else if (reportType == 2) { // born before 1980
					runBornBeforeReport(headPtr); // show the relevant report - reports.h/c
				}
				else { // number was neither 1 nor 2, keep looping
					printf("\nAn invalid number was entered, aborting\n");
				}

			} while (reportType < 1 || reportType > 2); // loop condition for 2 options
			break;

		case 7:
			printf("Save all details to file\n");
			saveDetailsToFile(headPtr);
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

// search for and either display or update a passenger based on supplied 'type' parameter
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
		default:
			printf("\nInvalid choice!\n\n");
		}

	} while (searchType < 1 || searchType > 2); // validate the user's choice
	searchType = 0; // reset this variable
}