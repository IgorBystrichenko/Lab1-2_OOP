#pragma once
#include "Player.h"
class SmallestCardPlayer : public Player
{
public:
	SmallestCardPlayer(const std::string& name) : Player(name) {}
	Card TakeGameCard();
	Card TakeGameCardBySuit(int suit);
};

