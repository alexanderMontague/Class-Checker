// Library Decleration
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function Decleration
void removeNewline(char inputString[50]);

// Main
int main(void)
{

	// Variable Decleration
	char menuInput[100];
	char timetableFN[100];
	char enterCode[100];

	FILE* timetableFP = NULL;

	bool validClasses = false;
	bool loopMenu = true;

	printf("Welcome to the Guelph Class Checker!\n");
	printf("This program will determine if you have any classes with a peer!\n");
	printf("Please have a picture of your timetable saved in the same directory as this program!\n\n");
	
	while(loopMenu == true) {

		printf("\n'Import' - Import a picture of your timetable (Needs to be done in order to generate code)\n");
		printf("'Generate' - Generate a shareable code that you can give to others to check classes you have together\n");
		printf("'Enter' - Enter a friend's generated code to see what classes you have!\n");
		printf("'Exit' - Exit the program\n");
		printf("Would you like to: ");
		fgets(menuInput, sizeof(menuInput), stdin);
		removeNewline(menuInput);

		if(strcmp(menuInput, "Import") == 0) {
			printf("\nPlease make sure the picture of your timetable is in the same directory as this program!\n");
			printf("What is the name of the photo file containing your timetable?\n");
			printf("File Name: ");
			fgets(timetableFN, sizeof(timetableFN), stdin);
			removeNewline(timetableFN);
			// Use openCV stuff to open timetable and process it

		}
		else if(strcmp(menuInput, "Generate") == 0) {
			if(validClasses == false) {
				printf("You must import your timetable before generating a code!\n");
			}
			else {
				// Do code generation stuffs with some fancy algorithm
			}
		}
		else if(strcmp(menuInput, "Enter") == 0) {
			printf("Enter friend's code: ");
			fgets(enterCode, sizeof(enterCode), stdin);
			removeNewline(enterCode);

			// Process code and then tell if there are classes together
		}
		else if(strcmp(menuInput, "Exit") == 0) {
			loopMenu = false;
		}
		else {
			printf("Invalid Option! Try Again.\n");
		}
	}

return 0;
}

void removeNewline(char inputString[50]) {
	int strLength = 0;

	strLength = strlen(inputString) - 1;
	if(inputString[strLength] == '\n') {
		inputString[strLength] = '\0';
	}
}