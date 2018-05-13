/**
* @file Hand.h
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

#pragma once

#include <set>
#include <vector>
#include <algorithm>
#include "Card.h"




enum class PokerHand {
	NONE,
	JACKS_OR_BETTER,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH,
	ROYAL_FLUSH,
};




using CardPtr = std::shared_ptr<Card>;

class Hand
{
public:
	Hand();
	~Hand();

	void addCard(CardPtr card);
	void clear() { _hand.clear(); }
	friend std::ostream& operator<<(std::ostream& os, const Hand& rhs);

	bool isRoyalFlush()const;
	bool isStraightFlush()const;
	bool isFourOfAKind()const;
	bool isFullHouse()const;
	bool isFlush()const;
	bool isStraight()const;
	bool isThreeOfAKind()const;
	bool isTwoPairs()const;
	bool isJacksOrBetter()const;
	bool isPair()const; 

	bool isNotAWinningHand()const;

	PokerHand findWinningHand()const;

	std::set<Face> getFaces() const;
	std::map<Face, int> getFaceCounts() const;
	std::map<Suit, int> getSuitCounts() const;

	void Hand::cardToDiscard(int cardToDraw);
	void discard();
	//Hand discard( );
	int sizeOfHand();

	std::map<PokerHand, int> paySheet =
	{
		{ PokerHand::ROYAL_FLUSH, 250 },
		{ PokerHand::STRAIGHT_FLUSH, 50 },
		{ PokerHand::FOUR_OF_A_KIND, 25 },
		{ PokerHand::FULL_HOUSE, 9 },
		{ PokerHand::FLUSH, 6 },
		{ PokerHand::STRAIGHT, 4 },
		{ PokerHand::THREE_OF_A_KIND, 3 },
		{ PokerHand::TWO_PAIRS, 2 },
		{ PokerHand::JACKS_OR_BETTER, 1 }
	};
private:	
	std::vector<CardPtr> _hand;	
	std::map<int, int> _faceCount;
	std::vector<bool> _drawCard = { false,false,false,false,false };	
};


