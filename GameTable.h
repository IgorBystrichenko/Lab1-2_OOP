#pragma once
#include "Deck.h"
#include "Player.h"

class GameTable
{

public:
	
	GameTable(Player** players, int numberOfPlayers, Deck* deck) : _players(players), _numberOfPlayers(numberOfPlayers), _deck(deck) {}
	~GameTable();
	
	void ShuffleDeck();
	static int CompareCards(const Card& card1, const Card& card2);
	static int CompareCardRanks(const Card& card1, const Card& card2) { return card1.GetRank() - card2.GetRank(); };
	void GiveCards(int number);
	int Play(int playerIndex);

	Deck* GetDeck() const { return _deck; }
	Player* GetPlayer(int index) const { return _players[index]; }
	int GetNumberOfPlayers() const { return _numberOfPlayers; }
	
private:
	Deck* _deck;
	Player** _players;
	int _numberOfPlayers;
	
	int DoPlay(int firstPlayer);
	
};
