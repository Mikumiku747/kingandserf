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
#include <stdlib.h>
#include "cardops.h"
#include "cards.h"

#define random(x) ()

void printCard(struct Card card) {
	for (int line = 0; line < 7; line++) {
		printf("%s\n", cards[card.suit][card.value][line]);
	}
	printf("\n");
}

void printCards(struct Card *hand, int handc) {
	for (int line = 0; line < 7; line++) {
		for (int card = 0; card < handc; card++) {
			printf("%s", cards[hand[card].suit][hand[card].value][line]);
		}
		printf("\n");
	}
}

void swapCards(struct Card *set, int a, int b) {
	struct Card temp = set[a];
	set[a] = set[b];
	set[b] = temp;
}

//This function allocates memory, it is YOUR repsonsibility to free that
//memory when you are done in order to prevent a leak. You can use the
//freeHands function to free it up if you want, or you can do it 
//yourself.
//This deals out however many hands you need. It's pretty neat. If sort
//is nonzero, the hands will be sorted.
struct Hand *dealHands(int players, int sort) {
	//We check how many cards each player gets, and check the math
	int cardsperplayer = 54 / players;
	int leftovers = 54 % players;
	if ((cardsperplayer*players + leftovers) != 54) {fprintf(stderr, "Critical Error, we got more than 54 cards!"); return NULL;};
	//IT IS OF THE UTMOST IMPORTANCE THAT THIS HAND IS UN-ALLOCATED AS
	//SOON AS YOU ARE DONE WITH IT, BECAUSE IT IS AN EXCELLENT WAY TO
	//LEAK MEMORY. DO NOT FORGET TO FREE EACH HAND BEFORE FREEING THE
	//POINTER TO IT.
	struct Hand *hands = (struct Hand*)calloc(players, sizeof(struct Hand));
	for (int player = 0; player < leftovers; player++) {
		//Allocate an extra spot for these players, since they take an
		//extra card
		hands[player].cardv = (struct Card*)calloc((cardsperplayer + 1), sizeof(struct Card));
		hands[player].cardc = cardsperplayer + 1;
	}
	for (int player = leftovers; player < players; player++) {
		//Allocate the normal amount of cards for the rest of the players
		hands[player].cardv = (struct Card*)calloc((cardsperplayer), sizeof(struct Card));
		hands[player].cardc = cardsperplayer;
	}
	//First, we create a deck of cards.
	struct Card deck[54];
	int currentCard = 0;
	for (int suit = 0; suit < 4; suit++) {
		for (int value = 0; value < 13; value++) {
			struct Card newCard = {suit, value};
			deck[currentCard] = newCard;
			currentCard++;
		}
	}
	//Then we add the jokers on the end
	struct Card blackJoker = {0, 13};
	deck[52] = blackJoker;
	struct Card redJoker = {1, 13};
	deck[53] = redJoker;
	//Now, we shuffle the deck using the Fisher Yates shuffle (the Durstenfeld version)
	for (int cardsleft = 53; cardsleft > 0; cardsleft--) {
		swapCards(deck, cardsleft, rand() % cardsleft);
	}
	//IT SEEMS TO DROP THE HANDS ARRAY RIGHT HERE...run 
	//Now that the cards are randomly shuffled, we just deal them out to
	// everyone (it doesn't matter about the order, this is supposed to
	//be truly random!
	currentCard = 0;
	for (int player = 0; player < leftovers; player++) {
		//Deal an extra card for these players, since they take an extra
		//card
		for (int card = 0; card < hands[player].cardc; card++) {
			hands[player].cardv[card] = deck[currentCard];
			currentCard++;
		}
	}
	for (int player = leftovers; player < players; player++) {
		//Deal the normal amount of cards for the rest of the players
		for (int card = 0; card < hands[player].cardc; card++) {
			hands[player].cardv[card] = deck[currentCard];
			currentCard++;
		}
	}
	
	if (sort != 0) {
		//Put code to sort hands here
	}
	//Now that we should have dealt out all the cards, it's time to 
	//return them.
	return hands;
}
