/**
* @file Card.cpp
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

#include "Card.h"
#include <string>

Card::~Card(){}

std::set<Face> Card::allFaceNames()
{
	std::set<Face>tmp;
	for (auto p : _faceNames)
		tmp.insert(p.first);
	return tmp;
}

std::set<Suit> Card::allSuitNames()
{
	std::set<Suit>tmp;
	for (auto p : _suitNames)
		tmp.insert(p.first);
	return tmp;
}

std::map<Face, std::string> Card::_faceNames
{
	{ Face::ACE, "ace" },
	{ Face::TWO, "two" },
	{ Face::THREE, "three" },
	{ Face::FOUR, "four" },
	{ Face::FIVE, "five" },
	{ Face::SIX, "six" },
	{ Face::SEVEN, "seven" },
	{ Face::EIGHT, "eight" },
	{ Face::NINE, "nine" },
	{ Face::TEN, "ten" },
	{ Face::JACK, "jack" },
	{ Face::QUEEN, "queen" },
	{ Face::KING, "king" }
};

std::map<Suit, std::string> Card::_suitNames =
{
	{ Suit::CLUB, "club" },
	{ Suit::DIAMOND, "diamond" },
	{ Suit::HEART, "heart" },
	{ Suit::SPADE, "spade" },
};

std::ostream& operator<<(std::ostream & os, const Card & rhs)
{
	os <<"\t===== "<< Card::_faceNames[rhs.face] << " of " << Card::_suitNames[rhs.suit]<< " ======" << std::endl;

	return os;
}
