//Card Operations header file
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

#ifndef _CARDOPS_C
#define _CARDOPS_C

struct Card {
	int suit;
	int value;
};

struct Hand {
	int cardc;
	struct Card* cardv;
};

void printCard(struct Card card);

void printCards(struct Card *hand, int handc);

//Macro for playing a hand instead of a group of cards
#define printHand(hand) printCards(hand.cardv, hand.cardc)

void swapCards(struct Card *set, int a, int b);

void sortHand(struct Hand hand);

struct Hand *dealHands(int players, int sort);

#endif
