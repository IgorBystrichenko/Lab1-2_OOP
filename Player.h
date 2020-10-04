#pragma once
#include "Deck.h"

class Player : public Deck
{
public:
	Player(const std::string& name) : Deck(), _name(name) {}

	std::string GetName() const { return _name; }
	virtual Card TakeGameCard() = 0;
	virtual Card TakeGameCardBySuit(int suit) = 0;
protected:
	std::string _name;
};

