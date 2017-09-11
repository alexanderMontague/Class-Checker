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
	size_t numClasses = 0;
	size_t goodClasses = 0;
	size_t totalClassCodes = 0;
	size_t totalGoodClassCodes = 0;

	int lineChecker = 1;
	int classNameLen = 0;
	int starCounter = 0;
	int starCounter2 = 0;

	char menuInput[100] = "NULL";
	char enterCode[100] = "NULL";
	char importMenu[100] = "NULL";
	char tempInput[100] = "NULL";
	char searchInput[100] = "NULL";
	char searchInput2[100] = "NULL";
	char classDesc[100] = "NULL";
	char tempClassCode[100] = "NULL";
	char specificCode[100];
	char generatedCode[100] = "NULL";

	char **onlyClassCode = NULL;
	char **onlyClassCode2 = NULL;
	char **goodClassCodeP1 = NULL;
	char **goodClassCodeP2 = NULL;

	classInfo *classArray = NULL;
	classInfo *sortedArray = NULL;
	classInfo tempStruct;

	FILE *timetableDataFP = NULL;
	FILE *classDescFP = NULL;

	bool validClasses = false;
	bool loopMenu = true;
	bool loopMenu2 = true;
	bool uniqueClass = true;
	bool descSearch = true;
	bool secondRun = false;

	printf("\nWelcome to the Guelph Class Checker!\n");
	printf("This program will determine if you have any classes with a peer!\n\n");
	
	while(loopMenu == true) {

		printf("'Import' - Import your timetable classes (Needs to be done in order to generate code)\n");
		printf("'Generate' - Generate a shareable code that you can give to others to check classes you have together\n");
		printf("'Enter' - Enter a friend's generated code to see what classes you have!\n");
		printf("'Exit' - Exit the program\n");
		printf("What would you like to do?: ");
		fgets(menuInput, sizeof(menuInput), stdin);
		removeNewline(menuInput);

		if(secondRun == true && strcmp(menuInput, "Import") == 0) {
			printf("\n\nYou have already imported your classes successfully!\n");
			printf("If you want to change users and class data, please run the program again.\n\n\n");
			strcpy(menuInput, "RUN2");
		}

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

					classArray = NULL;									// Resetting class struct array every import
					numClasses = 1;
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
						printf("\nClass Import Success!\n");
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
					}

					free(classArray);
					fclose(timetableDataFP);

					classDescFP = fopen("courseList.txt", "r");
					if(classDescFP == NULL) {
						printf("'courseList.txt' seems to be missing! Redownload the application!\n\n");
						loopMenu2 = false;
					}
					else {
						printf("Here are your classes: \n\n");								// *** Formatting and Displaying classes and their descriptions from file *** 
						for(int i = 0; i < goodClasses; i++) {								// Going through every class code
							starCounter = 0;												// Resetting asterisk counter
							classNameLen = 0;												// Resetting the class length counter
							for(int x = 0; x < strlen(sortedArray[i].classCode); x++) {		// Going through each character in the class codes
								if(sortedArray[i].classCode[x] == '*') {					// If an asterisk is found, add to star counter
									starCounter++;
								}
								if(starCounter == 2) {										// Check right after if the second star has been found, and if it has, break out of the character search loop
									classNameLen = x;
									break;
								}
							}
							descSearch = true;												// Reset the description dearch bool back to true for the next search
							while(descSearch == true) {										// Searching the class description list to grab the descriptions we need
								fgets(tempInput, 150, classDescFP);							// Reading in every line, line by line from the class description file
								for(int z = 0; z < classNameLen; z++) {												
									searchInput[z] = tempInput[z];							// Getting right length class code from description file 
									searchInput2[z] = sortedArray[i].classCode[z];			// Getting right length class code from the class code section of the struct
								}
								if(strcmp(searchInput2, searchInput) == 0) {				// If both the class codes match, get only the description portion into a variable
									descSearch = false;										// Reset the description search bool back for the next class
									fseek(classDescFP, 0, SEEK_SET);						// Seek back to the start of the description file for the next class search.
									for(int y = classNameLen + 1; y <= strlen(tempInput); y++) {
										classDesc[y - (classNameLen + 1)] = tempInput[y];	// Set only the description portion of the input to a new variable for output
									}
								}
							}
							printf("%s - %sType: %s       Room: %s\n\n", sortedArray[i].classCode, classDesc, sortedArray[i].classType, sortedArray[i].classLoc);
						}
					}

					secondRun = true;
					loopMenu2 = false;

					classArray = NULL;
					fclose(classDescFP);
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

				onlyClassCode = malloc(goodClasses * sizeof(char *));			// Allocating number of spots in array for first portion of class code
				onlyClassCode2 = malloc(goodClasses * sizeof(char *));			// Allocating number of spots in array for second portion of class code

				for(int a = 0; a < goodClasses; a++) {									// First loop goes through whole portion class code
					onlyClassCode[a] = malloc(strlen(sortedArray[a].classCode) + 1);	// Allocating room for each char of first portion of class code
					starCounter2 = 0;													// Second star counter, same system as above
					for(int b = 0; b < strlen(sortedArray[a].classCode); b++) {			// Goes through each character in the entire class code string
						if(sortedArray[a].classCode[b] == '*') {						// If an asterisk is found, add to star counter
							starCounter2++;												
							if(starCounter2 == 2) {
								size_t d = 0;											// New variable to hold characters after the second asterisk
								for(int c = b + 1; c < (b + (strlen(sortedArray[a].classCode) - b)); c++) {		// Start the loop at the first char after the second asterisk, and stop when string runs out
									specificCode[d] = sortedArray[a].classCode[c];								// Transferring characters from after the second asterisk to a new variable
									d++;
								}
								onlyClassCode2[a] = malloc(strlen(specificCode) + 1);							// Allocating for each character per each element for the string after the second asterisk
								strcpy(onlyClassCode2[a], specificCode);
								break;
							}
							else {
								tempClassCode[b] = sortedArray[a].classCode[b];									// Transferring characters before second asterisk to a new variable in an array only if it is before the second asterisk
							}
						}
						else {
							tempClassCode[b] = sortedArray[a].classCode[b];										// Same as ^. Just when char is not an asterisk
						}
					}

					strcpy(onlyClassCode[a], tempClassCode);
					printf("%s %s\n", onlyClassCode[a], onlyClassCode2[a]);
				}
					totalGoodClassCodes = 1;
					goodClassCodeP1 = malloc(sizeof(char *));		
					goodClassCodeP1[0] = malloc(strlen(onlyClassCode[0]) + 1);
					goodClassCodeP1[0] = onlyClassCode[0];					
					for(int j = 1; j < goodClasses + 1; j++) {		// OUTSIDE LOOP NOT SORTED CLASSES	
						uniqueClass = true;
						for(int i = 0; i < totalGoodClassCodes; i++) {		// INSIDE SORTED CLASSES
							if(strcmp(onlyClassCode[j], goodClassCodeP1[i]) == 0) {
								uniqueClass = false;
								printf("made it in\n");
							}
						}
						if(uniqueClass == true) {
							totalGoodClassCodes++;
							goodClassCodeP1 = realloc(goodClassCodeP1, sizeof(char *) * totalGoodClassCodes);		// Initial malloc for first element
							goodClassCodeP1[j] = realloc(goodClassCodeP1, strlen(onlyClassCode[j]) + 1);
							goodClassCodeP1[j] = onlyClassCode[j];
						}
					}

					for(int fuk = 0; fuk < totalGoodClassCodes; fuk++) {
						printf("%s\n", goodClassCodeP1[fuk]);
					}

				
				free(sortedArray);
				sortedArray = NULL;
				// FREE EVERYTHING
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
		else if(strcmp(menuInput, "RUN2") == 0) {
			// Do nothing and go back to menu
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
