#pragma once
#include "Player.h"
class BiggestCardPlayer : public Player
{
public:
	BiggestCardPlayer(const std::string& name) : Player(name) {}
	Card TakeGameCard();
	Card TakeGameCardBySuit(int suit);
};

