/**
* @file Deck.h
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

#include <vector>
#include <memory>
#include <algorithm>
#include <ctime>
#include "Card.h"


class Deck
{
public:
	Deck();
	~Deck();
	const int DECK_SIZE = 52;
	const CardPtr drawCard();
	void shuffle();
	bool isEmpty() const;

	friend std::ostream& operator<<(std::ostream & os, const Deck & rhs)
	{
		for (auto c : rhs._cards) {
			os << *c;
		}
		return os;
	}

private:

	std::vector<CardPtr>	_cards;
	int						_topCard = 0;
};


