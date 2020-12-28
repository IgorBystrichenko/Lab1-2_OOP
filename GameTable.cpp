#include "GameTable.h"
#include "DeckLoader.h"
#include "RandomGenerator.h"
#include <map>
#include <set>
#include <stdexcept>
#include <iostream>

GameTable::~GameTable()
{
	delete _deck;
	delete _data;
}

void GameTable::ShuffleDeck()
{
	for (int i = _deck->GetDeckSize() - 1; i > 0; i--)
	{
		_deck->AddCard(_deck->TakeCard(RandomGenerator::GenerareRandomInt(0, i)));
	}
}

int GameTable::CompareCards(const Card& card1, const Card& card2)
{
	if (card1.GetSuit() == card2.GetSuit())
	{
		return CompareCardRanks(card1, card2);
	}
	else
	{
		throw std::logic_error("Ñomparison of cards of different suits");
	}
}

void GameTable::GiveCards(int number)
{
	if (number < 0 || number > _deck->GetDeckSize() / _data->GetNumberOfPlayers())
	{
		throw std::exception("Wrong number of cards!");
	}
	std::map<int, Player*> map = _data->PlayerMapById();
	for (auto i = map.begin(); i != map.end(); i++)
	{
		for (int j = 0; j < number; j++)
		{
			i->second->AddCard(_deck->TakeCard(0));
		}
	}
}

int GameTable::Play(int firstPlayerID)
{
	Player* player = _data->GetPlayerById(firstPlayerID);
	
	if (player->GetDeck()->GetDeckSize() == 0)
	{
		throw std::logic_error("Players don't have cards");
	}
	else
	{
		return DoPlay(firstPlayerID);
	}
}

int GameTable::DoPlay(int firstPlayerID)
{
	Card biggestCard = _data->GetPlayerById(firstPlayerID)->TakeGameCard();
	char suit = biggestCard.GetSuit();
	std::map<int, Player*> map = _data->PlayerMapById();
	
	std::map<int, Player*>::iterator winner = map.begin();

	for (auto i = map.begin(); i != map.end(); i++)
	{
		if (i == map.find(firstPlayerID))
		{
			continue;
		}
		Card playerCard = i->second->TakeGameCardBySuit(suit);
		if (playerCard.GetSuit() == suit && CompareCards(playerCard, biggestCard) > 0)
		{
			biggestCard = playerCard;
			winner = i;
		}
	}
	
	_data->PlayerMapByWinnings()[(*winner).second->GetWinnings()].erase(winner->first);
	winner->second->IncWinnings();
	_data->PlayerMapByWinnings()[(*winner).second->GetWinnings()].insert(winner->first);
	return (*winner).first;
}
