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
	char enterCode[100];
	char importMenu[100];

	FILE *timetableDataFP = NULL;

	bool validClasses = false;
	bool loopMenu = true;
	bool loopMenu2 = true;

	printf("Welcome to the Guelph Class Checker!\n");
	printf("This program will determine if you have any classes with a peer!\n");
	
	while(loopMenu == true) {

		printf("'Import' - Import your timetable classes (Needs to be done in order to generate code)\n");
		printf("'Generate' - Generate a shareable code that you can give to others to check classes you have together\n");
		printf("'Enter' - Enter a friend's generated code to see what classes you have!\n");
		printf("'Exit' - Exit the program\n");
		printf("Would you like to: ");
		fgets(menuInput, sizeof(menuInput), stdin);
		removeNewline(menuInput);

		if(strcmp(menuInput, "Import") == 0) {
			printf("\nCopy and Paste your timetable into the text file 'timetableData.txt' in this directory!\n");
			printf("If the text file 'timetableData.txt' contains your class data, and is saved, type 'Ready'\n");
			printf("If you want a step by step and video demonstration of what to do, type 'Help'\n");
			
			while(loopMenu2 == true) {
				printf("Enter 'Ready' or 'Help': ");
				fgets(importMenu, sizeof(importMenu), stdin);
				removeNewline(importMenu);

				if(strcmp(importMenu, "Help") == 0) {
					printf("Navigate to the Class Schedule Grid screen that can be found on webadvisor.\n");
					printf("Click and drag from the 'Class Schedule Grid' title text, all the way down to the end of your name.\n");
					printf("Copy the selected text (ctrl/cmmnd + C OR right click and select'copy'.)\n");
					printf("Navigate to the folder this program is contained in.\n");
					printf("Open the file 'timetableData.txt'\n");
					printf("Paste the contents into the empty file.\n");
					printf("Save the file (ctrl/cmmnd + S OR click file>save)\n");
					printf("That is it!\n");
					printf("If you would like to see a graphical representation, open the file 'timetableHelp'!\n");

				}	
				else if(strcmp(importMenu, "Ready") == 0) {
					// Process text file
				}
				else {
					printf("Invalid Option! Try Again.\n")
				}
			}

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