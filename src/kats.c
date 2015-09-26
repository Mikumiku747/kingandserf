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

//My source includes
#include "cards.h"
#include "cardops.h"
#include "menu.h"

char *turnmenu[4] = 
	{"Pass",
	 "Play your lowest playable card(s)",
	 "Play a card(s)",
	 "Forfeit"};
	 
char **startmenu = turnmenu + 1;

char *numToPlayMenu[4] = 
	{"Play One Card",
	 "Play Two Cards",
	 "Play Three Cards",
	 "Play Four Cards"};

int main(int argc, char **argv) {
	//Seed the RNG
	srand(argv[1][0]);
	//For now, we'll assume a game with 4 players
	int players = 6;
	//Deal a hand to everyone
	struct Hand *hands = dealHands(players, 1);
	//Set up for the game loop
	struct Card currentCard[4];
	int currentMulti = 0;
	int currentPlayer = 0;
	int choice;
	int chosenCard;
	int cardsToPlay;
	int indexToPlay;
	int validMove;
	int lowestPlayable;
	int lastPlay = 0;
	int forfeitTurn = 0;
	struct Hand tempHand;
	//Now we enter the first stage main game loop, this continues until 
	//a player has 0 cards, thereby winning and becoming king.
	do {
		if (lastPlay == currentPlayer) {
			//This player was the last one to play a card, they can start
			currentMulti = 0;
		}
		if (currentMulti == 0) {
			//This is a starter turn
			do {
				validMove = 0;
				printf("It's player %d's turn. Here is your hand: \n", currentPlayer + 1);
				printHand(hands[currentPlayer]);
				choice = presentMenu("You're starting the round, what will you do?", 3, startmenu);
				switch (choice) {
					case 1: //Play lowest cards
						//Do they have more than one of thier lowest card?
						if (hands[currentPlayer].cardv[0].value == hands[currentPlayer].cardv[1].value) {
							//They CAN play more than one
							//Ask them how many they want to play
							cardsToPlay = presentMenu("How many cards do you want to play?", 4, numToPlayMenu);
							//Do they have that many?
							if (hands[currentPlayer].cardv[0].value == hands[currentPlayer].cardv[cardsToPlay - 1].value) {
								//They do
								currentMulti = cardsToPlay;
								for (int playedCards = 0; playedCards < currentMulti; playedCards++) {
									currentCard[playedCards] = playCard(&(hands[currentPlayer]), 0);
								}
								lastPlay = currentPlayer;
								validMove = 1;
								break;
							} else {
								printf("You can't play that many cards, you don't have enough of them.\n");
								validMove = 0;
								break;
							}
						} else {
							//They only have one of thier lowest
							currentMulti = 1;
							currentCard[0] = playCard(&(hands[currentPlayer]), 0);
							lastPlay = currentPlayer;
							validMove = 1;
							break;
						}
						//Somehow, if execution gets here, break
						break;
					case 2:
						//Ask them which card they have
						chosenCard = askForCard("Which card do you want to play?");
						//Check if they have the card they asked for
						if ((indexToPlay = findInHandv(hands[currentPlayer], chosenCard)) > -1) {
							//They have that card
							//Do they have more than one?
							if (hands[currentPlayer].cardv[indexToPlay].value == hands[currentPlayer].cardv[indexToPlay+1].value) {
								//They DO have more than one
								//Ask them how many they want to play
								cardsToPlay = presentMenu("How many cards do you want to play?", 4, numToPlayMenu);
								//Do they have that many?
								if (hands[currentPlayer].cardv[indexToPlay].value == hands[currentPlayer].cardv[indexToPlay + cardsToPlay - 1].value) {
									//They do
									currentMulti = cardsToPlay;
									for (int playedCards = 0; playedCards < currentMulti; playedCards++) {
										currentCard[playedCards] = playCard(&(hands[currentPlayer]), indexToPlay);
									}
									validMove = 1;
									lastPlay = currentPlayer;
									break;
								} else {
									//They don't
									printf("You can't play that many cards, you don't have enough of them.\n");
									validMove = 0;
									break;
								}	
							} else {
								//They Don't have more than one
								currentMulti = 1;
								currentCard[0] = playCard(&(hands[currentPlayer]), chosenCard);
								lastPlay = currentPlayer;
								validMove = 1;
								break;
							}
						} else {
							//They don't have that card
							printf("You can't play that card, you don't have it!\n");
							validMove = 0;
							break;
						}
					case 3:
						//They want to forfeit
						if (askYesNo("Are you sure you want to forfiet?")) {
							//They are forfeiting
							printf("Player %i has forfeited!\nThis was thier hand:\n", currentPlayer + 1);
							printHand(hands[currentPlayer]);
							printf("Everybody will now shift palce to fill the gap.\n");
							for (int player = currentPlayer; player < players - 1; player++) {
								//Bubble this player to the end of the set
								tempHand = hands[player];
								hands[player] = hands[player + 1];
								hands[player + 1] = tempHand;								
							}
							//Now, reduce the amount of players in the game.
							players--;
							//Enable the forfeit flag so we don't skip the new "current" player
							forfeitTurn = 1;
							validMove = 1;
							break;
						}		
				}
			} while (validMove == 0);
		} else {
			//This is a normal turn
			//Tell the player the current game state
			printf("This is the current pile: \n");
			printCards(currentCard, currentMulti);
			do {
				validMove = 0;
				printf("It's player %d's turn. Here is your hand: \n", currentPlayer + 1);
				printHand(hands[currentPlayer]);
				choice = presentMenu("It's your turn, what will you do?", 4, turnmenu);
				switch (choice) {
					case 1: //Pass
						printf("Player %d passes.\n", currentPlayer + 1);
						validMove = 1;
						break;
					case 2: //Play lowest cards
						lowestPlayable = findInHandgtv(hands[currentPlayer], currentCard[0].value);
						if (lowestPlayable < 0) {
							//No playable cards
							printf("You have no playable cards, you must pass!\n");
							validMove = 0;
							break;
						} else {
							//They can play at least one...
							indexToPlay = lowestPlayable;
							if (currentMulti > 1) {
								//Do they have enough to play?
								if (hands[currentPlayer].cardv[indexToPlay + currentMulti - 1].value == hands[currentPlayer].cardv[indexToPlay].value) { //This code might segfault due to reading past the end of the hand
									//They do, so play multiple cards
									for (int playedCards = 0; playedCards < currentMulti; playedCards++) {
										currentCard[playedCards] = playCard(&(hands[currentPlayer]), indexToPlay);
									}
									lastPlay = currentPlayer;
									validMove = 1;
									break;
								} else {
									//They need more, or a higher number
									printf("You can't play your lowest card, you need more of them to play.\n");
									validMove = 0;
									break;
								}
							} else {
								currentCard[0] = playCard(&(hands[currentPlayer]), indexToPlay);
								lastPlay = currentPlayer;
								validMove = 1;
								break;
							}
						}
						//Somehow, if execution gets here, break
						break;
					case 3:
						//They want to play a specific card
						lowestPlayable = findInHandgtv(hands[currentPlayer], currentCard[0].value);
						if (lowestPlayable < 0) {
							//No playable cards
							printf("You have no playable cards, you must pass!\n");
							validMove = 0;
							break;
						} else {
							//Let them choose a card:
							chosenCard = askForCard("Which card do you want to play?");
							//Check that the card is high enough
							if (chosenCard > currentCard[0].value) {
								indexToPlay = findInHandv(hands[currentPlayer], chosenCard);
								//Check they have enough of that card to play
								if (hands[currentPlayer].cardv[indexToPlay].value == hands[currentPlayer].cardv[indexToPlay + currentMulti - 1].value) { //This code might segfault due to reading past the end of the hand
									//They do have enough, play a multiple cards
									for (int playedCards = 0; playedCards < currentMulti; playedCards++) {
										currentCard[playedCards] = playCard(&(hands[currentPlayer]), indexToPlay);
									}
									lastPlay = currentPlayer;
									validMove = 1;
									break;
								} else {
									//They need more
									printf("You can't play your lvl%d card, you need more of them to play.\n", chosenCard);
									validMove = 0;
									break;
								}
							} else {
								//That card isn't high enough to play
								printf("You can't play that card, it doesn't beat the current card.\n");
								validMove = 0;
								break;
							}
						}
						break;
					case 4:
						//They want to forfeit
						if (askYesNo("Are you sure you want to forfiet?")) {
							//They are forfeiting
							printf("Player %i has forfeited!\nThis was thier hand:\n", currentPlayer + 1);
							printHand(hands[currentPlayer]);
							printf("Everybody will now shift palce to fill the gap.\n");
							for (int player = currentPlayer; player < players - 1; player++) {
								//Bubble this player to the end of the set
								tempHand = hands[player];
								hands[player] = hands[player + 1];
								hands[player + 1] = tempHand;								
							}
							//Now, reduce the amount of players in the game.
							players--;
							//Enable the forfeit flag so we don't skip the new "current" player
							forfeitTurn = 1;
							validMove = 1;
							break;
						}
								
				}
			} while (validMove == 0);
		}
		//End of turn, on to the next player
		currentPlayer++;
		if (forfeitTurn) {
			currentPlayer--;
			forfeitTurn = 0;
		}
		if (currentPlayer == players) {currentPlayer = 0;}
		
	} while ((checkWinner(hands, players) == -1) || (players > 1));
	if (players > 1) {
		printf("Player %d is the Winner of this round, and the new king!\n", checkWinner(hands, players) + 1);
	} else {
		printf("Player 1 wins by default!");
	}
	return 0;
}

#endif
