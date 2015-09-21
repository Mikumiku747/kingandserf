//Card Operations file
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

//Includes
#include <stdio.h>
#include "cardops.h"
#include "cards.h"

struct Card {
	int suit;
	int value;
};

void printCard(struct Card card) {
	for (int line = 0; line < 7; line++) {
		printf("%s\n", cards[card.suit][card.value][line]);
	}
}
