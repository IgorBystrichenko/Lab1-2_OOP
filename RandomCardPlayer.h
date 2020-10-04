#pragma once
#include "Deck.h"
#include "Player.h"

class RandomCardPlayer : public Player
{
public:
	RandomCardPlayer(const std::string& name) : Player(name) {}
	Card TakeGameCard();
	Card TakeGameCardBySuit(int suit);
};

