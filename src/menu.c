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
#include <ncurses.h>

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
	while (choice < 0 || choice > optionsc) {
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

//Note: This function doesn't get exposed in the header
void printMenu(int optionsc, char **optionsv) {
	for (int option = 0; option < optionsc; option++) {
		printf("%i - %s\n", option + 1, optionsv[option]);
	}
}
