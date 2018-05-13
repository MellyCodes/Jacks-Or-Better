/**
* @file Deck.cpp
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

#include "Deck.h"
#include "Card.h"

Deck::Deck()
{
	srand(time(NULL));
	for (auto s : Card::allSuitNames()) {
		for (auto f : Card::allFaceNames()) {
			_cards.push_back(CardPtr(new Card(f, s)));
		}
	}
}

Deck::~Deck()
{
}

const CardPtr Deck::drawCard()
{
	if (!isEmpty()) {
		return _cards[_topCard++];
	}
	else {
		throw std::invalid_argument("The deck is empty");
	}
}

void Deck::shuffle()
{
	std::random_shuffle(_cards.begin(), _cards.end());
}

bool Deck::isEmpty() const
{
	return(_topCard == DECK_SIZE);
}





