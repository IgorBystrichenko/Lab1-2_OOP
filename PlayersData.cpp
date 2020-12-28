#include "PlayersData.h"


Player* PlayersData::GetPlayerById(int id) const
{
	auto it = _players.find(id);
	if (it == _players.end())
	{
		throw std::exception("Wrong player id");
	}
	return it->second;
}