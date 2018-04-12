#ifndef LOGIN_H
#define LOGIN_H

void runLoginLoop(); // the only function to be exposed from this module

static int readUserDetailsFromFile();
static int checkLoginDetails(char username[], char password[], int numUsers);

#endif // LOGIN_H