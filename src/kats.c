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

#include "cards.h"
#include "cardops.h"

int main(int argc, char **argv) {
	//Print out some cards to start with
	for (int suit = 0; suit < 4; suit++) {
		printf("\n");
		for (int line = 0; line < 7; line++) {
			for (int card = 0; card < 13; card++) {
				printf("%s", cards[suit][card][line]);
			}
			printf("\n");
		}	
	}
	struct Card jokers[4] = 
	{
		{1, 13},
		{0, 13},
		{2, 7 },
		{3, 11}
	};
	printf("\n");
	printCards(jokers, 4);
	return 0;
}

#endif
