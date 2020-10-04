#pragma once
#include "Card.h"
#include "Player.h"
#include "GameTable.h"

class ConsoleInteractor
{
public:
	void Start();
private:
	int _playerIndex = 0;
	static GameTable CreateGameTable();
	static Deck* DeckParser();
	static Player** PlayersParser(int numberOfPlayers);
	
	static void PrintCard(const Card& card);
	static void PrintAllPlayerCards(const GameTable& gameTable);
	static void PrintDeck(const GameTable& gameTable);
	
	static void GivePlayersCards(GameTable& gameTable);
	static void Play(GameTable& gameTable, int playerIndex);

	template < typename T >
	static T ReadValue(std::istream& stream);
};

