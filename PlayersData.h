#pragma once
#include <map>;
#include <set>;
#include <list>
#include "Player.h"

class PlayersData
{
public:
	PlayersData(const std::map<int, Player*>& players) : _players(players) 
	{
		_playersByWinnings.insert(std::pair<int, std::set<int>>(0, std::set<int>()));
		for (auto i = _players.begin(); i != _players.end(); i++)
		{
			_playersByWinnings[0].insert(i->first);
		}
	};

	Player* GetPlayerById(int id) const;

	std::map<int, Player*>& PlayerMapById() { return _players; }
	std::map<int, std::set<int>>& PlayerMapByWinnings() { return _playersByWinnings; }

	int GetNumberOfPlayers() const { return _players.size(); }
private:
	std::map<int, Player*> _players;
	std::map<int, std::set<int>> _playersByWinnings;
};

