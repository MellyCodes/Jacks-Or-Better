/**
* @file Hand.cpp
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

#include "Hand.h"
#include <algorithm>
#include <iostream>

Hand::Hand(){}

Hand::~Hand(){}

#pragma region poker hands
// check for different winning hands

bool Hand::isRoyalFlush() const
{
	std::set<Face> faces = getFaces();

	if ((*faces.begin() == Face::ACE && *faces.begin()++ == Face::TEN) && isFlush())
		return true;
	else
		return false;
}

bool Hand::isStraightFlush() const
{
	if (isStraight() && isFlush())
		return true;
}

bool Hand::isFourOfAKind()const
{
	auto faceCounts = getFaceCounts();
	return std::any_of(
		faceCounts.begin(),
		faceCounts.end(),
		[](auto p) {
		return p.second == 4;
	});
}

bool Hand::isFullHouse() const
{
	if (isPair() && isThreeOfAKind())
		return true;
}

bool Hand::isFlush()const
{
	auto suitCounts = getSuitCounts();
	return std::any_of(
		suitCounts.begin(),
		suitCounts.end(),
		[](auto s) {
		return s.second == 5;
	});
}

bool Hand::isStraight()const
{
	auto faceCounts = getFaceCounts();
	std::set<Face> faces = getFaces();

	int min = static_cast<int>(*faces.begin());
	int max = static_cast<int>(*faces.rbegin());

	if(faces.size()<5) //If there are fewer than 5 unique faces - no straight
	{
		return false;
	}	

	//once we know that there are 5 unique faces...checks for Ace high straight
	if ((*faces.begin()) == Face::ACE && (*faces.begin()++) == Face::TEN) {
		return true;
	}

	//checks for Ace low straight
	if ((*faces.begin()) == Face::ACE && (*faces.rbegin()) == Face::FIVE) {
		return true;
	}
	
	if (max == min + 4) {
		return true;
	}
	else
		return false;
}

bool Hand::isThreeOfAKind() const
{
	auto faceCounts = getFaceCounts();
	return std::any_of(
		faceCounts.begin(),
		faceCounts.end(),
		[](auto p) {
		return p.second == 3;
	});
}

bool Hand::isTwoPairs() const
{
	int pairs = 0;
	auto faceCounts = getFaceCounts();
	std::set<Face> faces = getFaces();
	
	std::for_each(faceCounts.begin(),faceCounts.end(),
		[&](auto p )
	{
		if (p.second == 2) { pairs++; };
	});

	if(pairs == 2)
		return true;
	else
		return false;	
}

bool Hand::isJacksOrBetter() const
{
	std::map<Face, int> faceCounts = getFaceCounts();

	bool hasJacksOrHigher = false;

	std::for_each(
		faceCounts.begin(),
		faceCounts.end(),
		[&hasJacksOrHigher](auto c) {
		if ((c.first >= Face::JACK || c.first == Face::ACE) && c.second == 2)
		{
			hasJacksOrHigher = true;
		}
	});

	return hasJacksOrHigher;
}

bool Hand::isPair()const
{
	auto faceCounts = getFaceCounts();
	return std::any_of(
		faceCounts.begin(),
		faceCounts.end(),
		[](auto p) {
		return p.second == 2;
	});
}

#pragma endregion different types of winning hands

#pragma region findWinningHand
PokerHand Hand::findWinningHand() const
{
	if (isRoyalFlush()) {		
		return PokerHand::ROYAL_FLUSH;
	}
	else if (isStraightFlush()) {
		return PokerHand::STRAIGHT_FLUSH;
	}
	else if (isFourOfAKind()) {
		return PokerHand::FOUR_OF_A_KIND;
	}
	else if (isFullHouse()) {
		return PokerHand::FULL_HOUSE;
	}
	else if (isFlush()) {
		return PokerHand::FLUSH;
	}
	else if (isStraight()) {
		return PokerHand::STRAIGHT;
	}
	else if (isThreeOfAKind()) {
		return PokerHand::THREE_OF_A_KIND;
	}
	else if (isTwoPairs()) {
		return PokerHand::TWO_PAIRS;
	}
	else if (isJacksOrBetter()) {
		return PokerHand::JACKS_OR_BETTER;
	}
	else {
		return PokerHand::NONE;
	}
}
#pragma endregion This is code for finding winning hand

#pragma region Helper Methods

std::set<Face> Hand::getFaces() const
{
	std::set<Face> tmp;
	std::for_each(
		_hand.begin(),
		_hand.end(),
		[&tmp](auto c) {
		tmp.insert(c->face);
	});
	return tmp;
}

std::map<Face, int> Hand::getFaceCounts() const
{
	std::map<Face, int> tmp;
	std::for_each(
		_hand.begin(),
		_hand.end(),
		[&tmp](auto c) {
		tmp[c->face]++;
		
	});
	return tmp;
}

std::map<Suit, int> Hand::getSuitCounts() const
{
	std::map<Suit, int> tmp;
	std::for_each(
		_hand.begin(),
		_hand.end(),
		[&tmp](auto c) {
		tmp[c->suit]++;		
	});
	return tmp;
}

#pragma endregion Different Methods for extracting Faces, FaceCounts and SuitCounts

#pragma region Methods for: 

void Hand::addCard(CardPtr card)
{
	_hand.push_back(card);
}

void Hand::cardToDiscard(int cardToDraw)
{	
	_drawCard[cardToDraw] = true;	
}

void Hand::discard() {
	int handIndex = 0;
	int flagIndex = 0;

	while (flagIndex < _drawCard.size()) {
		if (_drawCard.at(flagIndex++)) {
			_hand.erase(_hand.begin() + handIndex);
		}
		else {
			handIndex++;
		}
	}	
}

int Hand::sizeOfHand()
{
	return _hand.size();
}

#pragma endregion Adding and Discarding cards

std::ostream & operator<<(std::ostream & os, const Hand& rhs)
{
	for (auto c : rhs._hand) {
		os <<*c;
	}
	return os;
}
