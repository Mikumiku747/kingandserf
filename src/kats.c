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

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cards.h"
#include "cardops.h"

int main(int argc, char **argv) {
	//Seed the RNG
	srand(time(NULL));
	//Deal out a hand for argc players
	struct Hand *hands = dealHands(argc, 0);
	for (int i = 0; i < argc; i++) {
		printCards(hands[i].cardv, hands[i].cardc);
		printf("\n");
	}
	return 0;
}

#endif
