#ifndef LOGIN_H
#define LOGIN_H

/* This file and its related program file deals with the login and authentication
*  aspect of the program
*/

// the only function to be exposed from this module
void runLoginLoop();

// read all user details from the file into the dynamic "users" array
static int readUserDetailsFromFile();

// check a username and password against the "users" array
static int checkLoginDetails(char username[], char password[], int numUsers);

#endif // LOGIN_H