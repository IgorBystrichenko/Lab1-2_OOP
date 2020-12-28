#pragma once
#include <map>;
#include <set>;
#include <list>
#include "Player.h"

class PlayersData
{
public:
	PlayersData(std::map<int, Player*>* players) : _players(players)
	{
		_playersByWinnings = new std::map<int, std::set<int>>();
		_playersByWinnings->insert(std::pair<int, std::set<int>>(0, std::set<int>()));
		for (auto i = _players->begin(); i != _players->end(); i++)
		{
			(*_playersByWinnings)[0].insert((*i).first);
		}
	}
	Player* GetPlayerById(int id) const
	{
		auto it = _players->find(id);
		if (it == _players->end())
		{
			throw std::exception("Wrong player id");
		}
		return (*it).second;
	}

	std::map<int, Player*>* PlayerMapById() const { return _players; }
	std::map<int, std::set<int>>* PlayerMapByWinnings() const { return _playersByWinnings; }

	int GetNumberOfPlayers() const { return _players->size(); }
private:
	std::map<int, Player*>* _players;
	std::map<int, std::set<int>>* _playersByWinnings;
};

