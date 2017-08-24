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
	typedef struct {
		char classCode[50];
		char classType[50];
		char classLoc[50];
	} classInfo;

	// Variable Decleration
	size_t numClasses = 1;
	size_t goodClasses = 0;

	int lineChecker = 1;
	int classNameLen = 0;
	int starCounter = 0;

	char menuInput[100] = "NULL";
	char enterCode[100] = "NULL";
	char importMenu[100] = "NULL";
	char tempInput[100] = "NULL";

	classInfo *classArray = NULL;
	classInfo *sortedArray = NULL;
	classInfo tempStruct;

	FILE *timetableDataFP = NULL;
	FILE *classDesc = NULL;

	bool validClasses = false;
	bool loopMenu = true;
	bool loopMenu2 = true;
	bool uniqueClass = true;

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
			loopMenu2 = true;

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
					
					validClasses = false;								// Resetting the valid classes bool every import 			
					timetableDataFP = fopen("timetableData.txt", "r");
					fseek(timetableDataFP, 20, SEEK_SET);				// Seeking to where the class codes start. Will be the same for every paste.

					if(fgets(tempInput, 100, timetableDataFP) == NULL) {
						printf("\nIMPORT ERROR | Check 'timetableData.txt' to make sure your class info is there!\n\n");
						loopMenu2 = false;
					}

					classArray = NULL;		// Resetting class struct array every import
					while(fgets(tempInput, 100, timetableDataFP) != NULL && strcmp(tempInput, " \n") != 0) { 	// Stop input from file right after last class in file
						
						classArray = realloc(classArray, sizeof(classInfo) * numClasses); 						// Realloc for however many stucts (classes) there will be
						removeNewline(tempInput);
						
						if(lineChecker == 1) {							// Store each individual line in appropriate spot in struct
							strcpy(tempStruct.classCode, tempInput);
						}
						else if(lineChecker == 2) {
							strcpy(tempStruct.classType, tempInput);
						}
						else if(lineChecker == 3) {
							strcpy(tempStruct.classLoc, tempInput);
						}

						lineChecker++;									// Count up here so check can happen right after without getting another input line
						if(lineChecker == 4) {							// Because lineChecker counts up one last time, check when 4
							classArray[numClasses - 1] = tempStruct;	// Write tempStruct into struct array
							numClasses++;								// Number of structs in struct array
							lineChecker = 1;							// Reset the counter to put input in correct spot in struct
						
						}
					}

					if(loopMenu2 == true) {
						printf("\nClass Import Success!\n\n");
						validClasses = true;							// Bool set for code generation

																		// *** Removing Duplicate Classes ***
						goodClasses = 1;								// n-1 Number of elements in sorted array
						sortedArray = malloc(sizeof(classInfo));		// Initial malloc for first element
						sortedArray[0] = classArray[0];					// Get first entry as a starting point to check
						for(int j = 1; j < numClasses - 1; j++) {		// 1 (second element in struct array) j starts at 0, but skips 1st
							for(int k = 0; k < goodClasses; k++) { 		// 1 (first element) k is starting at 1
								uniqueClass = true;						// Reset unique class check after checking with each class in sorted array
								if(strcmp(classArray[j].classCode, sortedArray[k].classCode) == 0) {		// Checking class name
									if(strcmp(classArray[j].classType, sortedArray[k].classType) == 0) {	// Checking class type
										uniqueClass = false;			// If class is exactly the same, do not add. Anything else add
									}
								}
							}
							if(uniqueClass == true) {					// If class is unique, create space and add to sorted array
								goodClasses++;
								sortedArray = realloc(sortedArray, sizeof(classInfo) * goodClasses);
								sortedArray[goodClasses - 1] = classArray[j];
							}
						}

						// DELETE CLASS PRINTS AFTER
						// printf("Test Print Structs\n");
						// for(int i = 0; i < goodClasses; i++) {
						// 	printf("Class: %s - Type: %s - Room: %s\n\n", sortedArray[i].classCode, sortedArray[i].classType, sortedArray[i].classLoc);
						// }

					}

					free(classArray);
					fclose(timetableDataFP);

					classDesc = fopen("courseList.txt", "r");
					if(classDesc == NULL) {
						printf("'courseList.txt' seems to be missing! Redownload the application!\n\n");
						loopMenu2 = false;
					}
					else {
						printf("Here are your classes: \n\n");
						for(int i = 0; i < goodClasses; i++) {
							
							starCounter = 0;
							classNameLen = 0;
							for(int x = 0; x < strlen(sortedArray[i].classCode); x++) {
								if(sortedArray[i].classCode[x] == '*') {
									starCounter++;
								}
								if(starCounter == 2) {
									classNameLen = x;
									break;
								}
							}
							printf("%d\n", classNameLen);

							printf("Class: %s - Type: %s - Room: %s\n\n", sortedArray[i].classCode, sortedArray[i].classType, sortedArray[i].classLoc);
						}
					}

					loopMenu2 = false;

					fclose(classDesc);
				}
				else {
					printf("Invalid Option! Try Again.\n");
				}
			}

		}
		else if(strcmp(menuInput, "Generate") == 0) {
			if(validClasses == false) {
				printf("\nYou must import your timetable before generating a code!\n\n");
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
			printf("Invalid Option! Try Again.\n\n");
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
