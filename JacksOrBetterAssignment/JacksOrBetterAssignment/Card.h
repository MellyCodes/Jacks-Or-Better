/**
* @file Card.h
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

#include <map>
#include <set>
#include <memory>

enum class Suit {
	CLUB,
	DIAMOND,
	HEART,
	SPADE
};
enum class Face {
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};

class Card
{
public:
	Card(Face f, Suit s) :face(f), suit(s) {};
	~Card();
	const Face face;
	const Suit suit;

	//class methods and members
	static std::set<Face> allFaceNames();
	static std::set<Suit> allSuitNames();
	friend std::ostream& operator<<(std::ostream& os, const Card& rhs);

private:
	static std::map<Face, std::string> _faceNames;
	static std::map<Suit, std::string> _suitNames;

};
inline bool operator<(const Card& lhs, const Card& rhs) {
	return (lhs.face < rhs.face) ||
		((lhs.face == rhs.face) && (lhs.suit < rhs.suit));
}

inline bool operator==(const Card& lhs, const Card& rhs) {

	return (lhs.face == rhs.face && lhs.suit == rhs.suit);
}

using CardPtr = std::shared_ptr<Card>;


