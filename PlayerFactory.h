#pragma once
#include "RandomCardPlayer.h"
#include "SmallestCardPlayer.h"
#include "BiggestCardPlayer.h"

class PlayerFactory
{
public:
	static Player* getPlayer(const std::string& name, const char& type)
	{
		Player* player;
		switch (type)
		{
		case 'r': player = new RandomCardPlayer(name); break;
		case 'b': player = new BiggestCardPlayer(name); break;
		case 's': player = new SmallestCardPlayer(name); break;
		default: throw std::logic_error("Invalid input. Try again!\nFormat: \"Name type\"");
		}
		return player;
	}
};

