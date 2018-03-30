#include "login.h"

#include <stdio.h>
#include <string.h>
#include "structs.h"

static FILE* loginFPtr;  // will be used to read the login_details.txt file
static User* users; // will be used to contain all users read in from the file

void runLoginLoop() {
	// user input username and password to check and use later
	int i, numUsers;

	// user input login details
	char username[USERNAME_MAX_LEN];
	char password[PASSWORD_MAX_LEN];

	char c; // used to mask password input

			// do while loop variables
	int loggedIn = 0; // login loop
	int menuSelection = 0; // main menu loop

						   // read all user details from file, allocate the dynamic users 
						   // array and set numUsers to the user count
	numUsers = readUserDetailsFromFile(users);

	printf("Welcome.  Please log in to continue...\n");
	printf("\n(Note: Password will be automatically entered when 6 characters have been input,\n");
	printf("otherwise just press return to enter shorter password)\n");

	//// start login loop
	do {
		printf("\nUsername: ");
		scanf("%s", &username);
		printf("Password: ");

		i = 0; // ensure that i has been initialised
			   // getch chars until condition is met, room is left for string terminator
		while (i < PASSWORD_MAX_LEN - 1) {
			password[i] = getch(); // add the char to the password string
			c = password[i]; // and assign c to this char

							 // if ENTER has been pressed, break from loop
			if (c == 13) {
				break;
			}
			// otherwise, print the mask char to the screen
			else {
				printf("*");
			}
			i++; // and increment the loop variable
		}
		password[i] = '\0'; // terminate the string
		i = 0; // ensure that i is reset

			   // check if the inputted username and password combination exists in the users array
		loggedIn = checkLoginDetails(username, password, numUsers); // function returns 1 if username+password found

																	// login failed
		if (loggedIn == 0) {
			printf("\nUsername and password combination unknown, please try again...\n");
		}
		// loop until correct username combo entered
	} while (loggedIn == 0);
	//// end login loop

	// some housekeeping
	free(users);
}

static int readUserDetailsFromFile() {
	int count = 0;
	char c;

	// read in the user details
	loginFPtr = fopen("login_details.txt", "r");

	// first get the number of users
	if (loginFPtr != NULL) {
		while (!feof(loginFPtr)) {
			c = fgetc(loginFPtr);
			if (c == '\n') {
				count++;
			}
		}
		count++; // last line does not contain a new line character, so increment once more
	}
	// allocate the dynamic array according to the number of users in the file
	users = (User*)malloc(count * sizeof(User));
	// and then add each user to the array
	rewind(loginFPtr);

	char chkUsername[50];
	char chkPassword[6];

	count = 0; // reset the counter
			   //loginFPtr = fopen("login_details.txt", "r");
	if (loginFPtr != NULL) {
		while (!feof(loginFPtr)) {
			fscanf(loginFPtr, "%s %s", &chkUsername, &chkPassword);
			strcpy((users + count)->username, chkUsername);
			strcpy((users + count)->password, chkPassword);
			count++;
		}
	}
	// close the file
	fclose(loginFPtr);
	// no need to do an extra increment this time, just return the count
	return count;
}

static int checkLoginDetails(char username[], char password[], int numUsers) {

	int i; // local loop variable
		   // check that the users array has been initialised with values
	if (users != NULL) {
		// loop through the users array
		for (i = 0; i < numUsers; i++) {
			// and check if the user and passowrd combo exists
			if (strcmp(username, (users + i)->username) == 0 && strcmp(password, (users + i)->password) == 0) {
				printf("\n\nUsername and password accepted - welcome '%s'\n", (users + i)->username);
				return 1; // return 1 and break out of login do while loop
			}
		}
	}
	return 0; // stay in login do while loop
}