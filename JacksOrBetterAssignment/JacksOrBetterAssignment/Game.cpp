/**
* @file Game.cpp
* @author Melanie Roy-Plommer
* @version 1.0
*
* @section DESCRIPTION
* < brief description of the purpose of this file >
*
* @section LICENSE
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

#include "Game.h"
#include <exception>

Game::Game()
{
}
Game::~Game()
{
}

void Game::play()const {	

	int credits = 20;
	int bet = 0;
	char playAgain = 'y';

	std::cout << "\n\tPlease enjoy these " << credits << " credits on the house!\n\n";

	while (tolower(playAgain) == 'y')
	{
		//create Deck and Hand object////
		Deck deck;
		Hand hand;
		hand.clear();
		//shuffle deck///
		deck.shuffle();

		std::cout << "\t===============================================\n";
		std::cout << "\t======== You currently have " << credits << " credits ========\n";
		std::cout << "\t===============================================\n";

		std::cout << "\t===============================================\n";
		std::cout << "\t=============== Enter your bet: ===============\n";
		std::cout << "\t===============================================\n";
		do{
			try
			{
				std::cin >> bet;
				if(bet > credits)
				{
					throw BetTooHighException(); // loop executes again to get proper bet amount <= credits
				}
				else
				{
					break; //if exception is not thrown, exit loop
				}
			}
			catch(BetTooHighException& e)
			{
				std::cout << e.what() << std::endl;				
			}
		} while (true);

		//add 5 cards to a hand
		for (int i = 0; i < 5; i++) {
			hand.addCard(deck.drawCard());
		}

		//Display hand
		std::cout << hand << std::endl;

		//capture user's choices of cards to hold
		int choice = 1;
		int cardsInHand = 5;

		std::cout << "Which cards would you like to DISCARD? (1 to 5) -OR- 0 to DRAW" << std::endl;

		while ((0 < choice <= 5 && 0 < cardsInHand--)) {
			
			std::cin >> choice;				
			
			if (choice == 0) {
				credits -= bet;
				std::cout << "\t*******************************\n";
				std::cout << "\t*****  Drawing new cards  *****\n";
				std::cout << "\t*******************************\n";
				break;
			}
			if (choice >0 && choice <6)
			{
				std::cout << "CARD " << choice << " DISCARDED" << std::endl;
				hand.cardToDiscard(choice - 1);
			}
			else
			{
				std::cout << choice << " is not a valid card. (1 to 5) -OR- 0 to DRAW\n";
			}
			
			
		}

		hand.discard();
		int size = hand.sizeOfHand();

		for (int i = 0; i < 5 - size; i++) {
			hand.addCard(deck.drawCard());
		}

		std::cout << hand << std::endl;

		switch (hand.findWinningHand()) {
		case PokerHand::NONE:
			std::cout << "Sorry! Better luck next time!" << std::endl;
			break;
		case PokerHand::JACKS_OR_BETTER:
			std::cout << "You have Jacks or better! Paying out " << hand.paySheet[PokerHand::JACKS_OR_BETTER] * bet << " credit!" << std::endl;
			credits += hand.paySheet[PokerHand::JACKS_OR_BETTER] * bet;
			break;
		case PokerHand::TWO_PAIRS:
			std::cout << "You have Two Pairs! Paying out " << hand.paySheet[PokerHand::TWO_PAIRS] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::TWO_PAIRS] * bet;
			break;
		case PokerHand::THREE_OF_A_KIND:
			std::cout << "You have Three Of A Kind! Paying out " << hand.paySheet[PokerHand::THREE_OF_A_KIND] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::THREE_OF_A_KIND] * bet;
			break;
		case PokerHand::STRAIGHT:
			std::cout << "You have a Straight! Paying out " << hand.paySheet[PokerHand::STRAIGHT] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::STRAIGHT] * bet;
			break;
		case PokerHand::FLUSH:
			std::cout << "You have a Flush! Paying out " << hand.paySheet[PokerHand::FLUSH] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::FLUSH] * bet;
			break;
		case PokerHand::FULL_HOUSE:
			std::cout << "You have a Full House! Paying out " << hand.paySheet[PokerHand::FULL_HOUSE] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::FULL_HOUSE] * bet;
			break;
		case PokerHand::FOUR_OF_A_KIND:
			std::cout << "You have Four Of A Kind! Paying out " << hand.paySheet[PokerHand::FOUR_OF_A_KIND] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::FOUR_OF_A_KIND] * bet;
			break;
		case PokerHand::STRAIGHT_FLUSH:
			std::cout << "You have a Straight Flush! Paying out " << hand.paySheet[PokerHand::STRAIGHT_FLUSH] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::STRAIGHT_FLUSH] * bet;
			break;
		case PokerHand::ROYAL_FLUSH:
			std::cout << "You have a Royal Flush! Paying out " << hand.paySheet[PokerHand::ROYAL_FLUSH] * bet << " credits!" << std::endl;
			credits += hand.paySheet[PokerHand::ROYAL_FLUSH];
			break;
		}
		getchar();

		if (credits > 0) {
			std::cout << "\t=============================================\n";
			std::cout << "\t============== Play again? (y/n) ============\n";
			std::cout << "\t=============================================\n";
			std::cin >> playAgain;
		}
		else
		{
			char addCredits = 'n';
			std::cout << "You have " << credits << " credits left. Add more? (y/n)\n";
			std::cin >> addCredits;
			if (tolower(addCredits) == 'y')
			{
				std::cout << "Enter number of credits you would like to purchase: \n";
				std::cin >> credits;
			}
			else
			{
				playAgain = 'n';				
			}			
		}		
		getchar();
	}

	if (credits>0)
	{
		std::cout << "\t========================================================================\n";
		std::cout << "\t======================= Cashing out " << credits << " credits =======================\n";
		std::cout << "\t========================================================================\n";
	}

	std::cout << "\t========================================================================\n";
	std::cout << "\t== Thanks for playing Mel's Ultimate Jacks Or Better! Come back soon! ==\n";
	std::cout << "\t========================================================================\n";
	
}

void Game::showPayTable() const
{
	std::cout << "   *******************\tPAY TABLE\t*********************\n";
	std::cout << "   **********************************************************\n";
	std::cout << "   ******\tHAND\t\t|\tCREDITS\t\t*****\n";
	std::cout << "   ****** --------------------------------------------- *****\n";
	std::cout << "   ******\tRoyal Flush\t|\t250\t\t*****\n";
	std::cout << "   ******\tStraight Flush\t|\t50\t\t*****\n";
	std::cout << "   ******\tFour Of A Kind\t|\t25\t\t*****\n";
	std::cout << "   ******\tFull House\t|\t9\t\t*****\n";
	std::cout << "   ******\tFlush\t\t|\t6\t\t*****\n";
	std::cout << "   ******\tStraight\t|\t4\t\t*****\n";
	std::cout << "   ******\tThree Of A Kind\t|\t3\t\t*****\n";
	std::cout << "   ******\tTwo Pair\t|\t2\t\t*****\n";
	std::cout << "   ******\tJacks Or Better\t|\t1\t\t*****\n";
	std::cout << "   **********************************************************\n";	
}

void Game::welcome() const
{
	std::cout << "\t=================================================\n";
	std::cout << "\t================== Welcome to ===================\n";
	std::cout << "\t== Mel's Ultimate Jacks Or Better Video Poker! ==\n";
	std::cout << "\t=================================================\n";
	std::cout << "\t===== Get a pair of Jacks or better to win! =====\n";
	std::cout << "\t=================================================\n\n";
	
}


