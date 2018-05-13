#pragma once

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream>

class BetTooHighException :public std::exception {
public:
	const char* what() const noexcept override
	{
		return "Your bet cannot exceed your credits.\nTry again!\n";
	}
};

class Game
{
public:
	Game();
	~Game();

	void play()const;
	void showPayTable()const;
	void welcome()const;
	
private:
	Deck _deck;
	Hand _hand;
	CardPtr _cards;
};

