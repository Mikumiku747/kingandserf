//kats Main program file
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

#ifndef _KATS_C
#define _KATS_C

//Standard Libary Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//External Library calls
#include <ncurses.h>

//My source includes
#include "cards.h"
#include "cardops.h"
#include "menu.h"

char *turnmenu[4] = 
	{"Pass",
	 "Play your lowest playable card(s)",
	 "Play a card(s)",
	 "Forfeit"};

int main(int argc, char **argv) {
	//Seed the RNG
	srand(time(NULL));
	//Deal out a hand for argc players
	int players;
	sscanf(argv[1], "%i", &players);
	struct Hand *hands = dealHands(players, 0);
	printf("Here is your hand: \n");
	printHand(hands[0]);
	int action = presentMenu("It is your turn, what will you do?", 4, turnmenu);
	printf("You chose to %s\n", turnmenu[action - 1]);
	return 0;
}

#endif
