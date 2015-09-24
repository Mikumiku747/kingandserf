//Text based menu file
//Copyright Daniel Selmes 2015
//This file is part of King and the Serf (or kats).
//----------------------------------------------------------------------
//kats is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//kats is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with kats.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------

#include "menu.h"

void printMenu(int optionsc, char **optionsv);

int presentMenu(char *question, int optionsc, char **optionsv) {
	int chosenOption = 0;
	printf("%s\n", question);
	printMenu(optionsc, optionsv);
	printf("> ");
	char input[20];
	int choice;
	gets(input);
	sscanf(input, "%d", &choice);
	while (choice < 1 || choice > optionsc) {
		//Clean out any characters if they're in there
		do {
			printf("Invalid choice, choose from 1 to %i (or ?).\n> ", optionsc);
			gets(input);
			if (input[0] == '?') {
				printf("%s\n", question);
				printMenu(optionsc, optionsv);
				printf("> ");
				gets(input);
			}
		} while (input[0] < '0' || input[0] > '9');
		sscanf(input, "%i", &choice);
	}
	return choice;
}

int askForCard(char *question) {
	printf("%s\n> ", question);
	char choice[2];
	scanf("%s", choice);
	while (1) {
		if ((choice[0] >= '2') && (choice[0] <= '9')) {
			return choice[0] - '0' - 2;
		}
		if ((choice[0] == '1') && (choice[1] == '0')) {
			return 8;
		}
		if ((choice[0] == 'j') || (choice[0] == 'J')) {
			return 9;
		}
		if ((choice[0] == 'q') || (choice[0] == 'Q')) {
			return 10;
		}
		if ((choice[0] == 'k') || (choice[0] == 'K')) {
			return 11;
		}
		if ((choice[0] == 'a') || (choice[0] == 'A')) {
			return 12;
		}
		printf("Invalid card value, please enter a card value (A, 2-10, J, Q, K).\n> ");
		scanf("%s", choice);
	}
}

int askYesNo(char *question) {
	printf("%s (Y/N)\n> ", question);
	char choice[1];
	scanf("%s", choice);
	if ((choice[0] == 'y') || (choice[0] == 'Y')) {
		return 1;
	} else {
		return 0;
	}
	return 0;
}

//Note: This function doesn't get exposed in the header
void printMenu(int optionsc, char **optionsv) {
	for (int option = 0; option < optionsc; option++) {
		printf("%i - %s\n", option + 1, optionsv[option]);
	}
}
