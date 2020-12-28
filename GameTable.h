#pragma once
#include "Deck.h"
#include "Player.h"
#include "PlayersData.h"

class GameTable
{
public:
	
	GameTable(PlayersData* data, Deck* deck) : _data(data), _deck(deck) {};
	~GameTable();
	
	void ShuffleDeck();
	static int CompareCards(const Card& card1, const Card& card2);
	static int CompareCardRanks(const Card& card1, const Card& card2) { return card1.GetRank() - card2.GetRank(); };
	void GiveCards(int number);
	int Play(int firstPlayerID);
	int GetNumberOfPlayers() const { return _data->GetNumberOfPlayers(); }
	PlayersData* GetPlayersData() const { return  _data; }
	Deck* GetDeck() const { return _deck; }
	
private:
	PlayersData* _data;
	Deck* _deck;
	
	int DoPlay(int firstPlayerID);
};
