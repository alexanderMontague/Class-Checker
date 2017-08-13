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
	// Struct Decleration
	struct classInfo {
		char classCode[50];
		char classType[50];
		char classLoc[50];
	};

	// Variable Decleration
	int numClasses = 1;
	int lineChecker = 1;

	char menuInput[100];
	char enterCode[100];
	char importMenu[100];
	char tempInput[100];

	struct classInfo classArray[numClasses];

	FILE *timetableDataFP = NULL;

	bool validClasses = false;
	bool loopMenu = true;
	bool loopMenu2 = true;

	printf("\nWelcome to the Guelph Class Checker!\n");
	printf("This program will determine if you have any classes with a peer!\n\n");
	
	while(loopMenu == true) {

		printf("'Import' - Import your timetable classes (Needs to be done in order to generate code)\n");
		printf("'Generate' - Generate a shareable code that you can give to others to check classes you have together\n");
		printf("'Enter' - Enter a friend's generated code to see what classes you have!\n");
		printf("'Exit' - Exit the program\n");
		printf("Would you like to: ");
		fgets(menuInput, sizeof(menuInput), stdin);
		removeNewline(menuInput);

		if(strcmp(menuInput, "Import") == 0) {

			timetableDataFP = fopen("timetableData.txt", "r");
			if(timetableDataFP == NULL) {
				timetableDataFP = fopen("timetableData.txt", "w");
			}
			fclose(timetableDataFP);

			printf("\nCopy and Paste your timetable data into the text file 'timetableData.txt' in this directory!\n");
			printf("If the text file 'timetableData.txt' contains your class data, and is saved, type 'Ready'\n");
			printf("If you want a step by step and video demonstration of what to do, type 'Help'\n");
			
			while(loopMenu2 == true) {
				printf("Enter 'Ready' or 'Help': ");
				fgets(importMenu, sizeof(importMenu), stdin);
				removeNewline(importMenu);

				if(strcmp(importMenu, "Help") == 0) {
					printf("\nNavigate to the Class Schedule Grid screen that can be found on webadvisor.\n");
					printf("Click and drag from the 'Class Schedule Grid' title text, all the way down to the end of your name.\n");
					printf("Copy the selected text (ctrl/cmd + C OR right click and select 'copy'.)\n");
					printf("Navigate to the folder this program is contained in.\n");
					printf("Open the file 'timetableData.txt'\n");
					printf("Paste the contents into the empty file.\n");
					printf("Save the file (ctrl/cmd + S OR click file > save)\n");
					printf("That's it!\n");
					printf("If you would like to see a graphical representation, open the file 'timetableHelp' in the directory!\n\n");

				}	
				else if(strcmp(importMenu, "Ready") == 0) {
										
					timetableDataFP = fopen("timetableData.txt", "r");
					fseek(timetableDataFP, 21, SEEK_SET);	// Seeking to where the class codes start. Will be the same for every paste.
															// SOMETHING WRONG HERE, Second line (first entry location) not being read or something
					while(strcmp(tempInput, " ") != 0) {
						while(lineChecker < 4) {
							fgets(tempInput, sizeof(tempInput), timetableDataFP);
							removeNewline(tempInput);
							if(lineChecker == 1) {
								strcpy(classArray[numClasses].classCode, tempInput);
							}
							else if(lineChecker == 2) {
								strcpy(classArray[numClasses].classType, tempInput);
							}
							else if(lineChecker == 3) {
								strcpy(classArray[numClasses].classLoc, tempInput);
							}
							lineChecker++;
						}
						printf("Class: %s Type: %s Loc: %s\n", classArray[numClasses].classCode, classArray[numClasses].classType, classArray[numClasses].classLoc);						lineChecker = 1;
						numClasses++;
					}
					loopMenu2 = false;
				}
				else {
					printf("Invalid Option! Try Again.\n");
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
			printf("\n");

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