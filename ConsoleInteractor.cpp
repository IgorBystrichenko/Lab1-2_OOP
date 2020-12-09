#include "ConsoleInteractor.h"
#include <sstream>
#include <iostream>
#include "BiggestCardPlayer.h"
#include "GameTable.h"
#include "DeckLoader.h"
#include "RandomCardPlayer.h"
#include "SmallestCardPlayer.h"
#include "PlayerFactory.h"


void ConsoleInteractor::Start()
{
	GameTable gameTable = CreateGameTable();
	std::cout <<
	"\nCommands:\n"
	"1 - Shuffle deck\n"
	"2 - Print deck\n"
	"3 - Print player cards\n"
	"4 - Give players cards\n"
	"5 - Play\n";

	while (true)
	{
		try
		{
			std::cout << "Enter next command:\n>> ";
			int temp = ReadValue<int>(std::cin);
			
			switch (temp)
			{
			case 1: gameTable.ShuffleDeck(); break;
			case 2: PrintDeck(gameTable); break;
			case 3: PrintAllPlayerCards(gameTable); break;
			case 4: GivePlayersCards(gameTable); break;
			case 5: Play(gameTable, _playerIndex); _playerIndex = (_playerIndex + 1) % gameTable.GetNumberOfPlayers(); break;
			default: throw std::logic_error("Illegal command input");
			}
			
			std::cout << std::endl;
		}
		catch (std::exception err)
		{
			std::cout << err.what() << std::endl << std::endl;
		}
	}
}

GameTable ConsoleInteractor::CreateGameTable()
{
	Deck* deck = DeckParser();

	int numberOfPlayers = -1;

	while (numberOfPlayers <= 0)
	{
		try
		{
			std::cout << "\nEnter the number of players:\n>> ";
			numberOfPlayers = ReadValue<int>(std::cin);
			if (numberOfPlayers <= 0)
			{
				throw std::logic_error("For game you should have 1 or more players!");
			}
		}
		catch (std::exception err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	
	Player** players = PlayersParser(numberOfPlayers);
	return GameTable(players, numberOfPlayers, deck);
}

Deck* ConsoleInteractor::DeckParser()
{
	Deck* deck = nullptr;
	while (deck == nullptr)
	{
		try
		{
			std::string deckFile;
			std::cout << "Enter the deck file:\n>> ";
			std::cin >> deckFile;
			deck = DeckLoader::LoadFromFile(deckFile);
		}
		catch (std::exception err)
		{
			std::cout << err.what() << std::endl << std::endl;
		}
	}
	return deck;
}

Player** ConsoleInteractor::PlayersParser(int numberOfPlayers)
{
	
	Player** players = new Player * [numberOfPlayers];
	std::cout << "\nEnter players \"Name type\"" << std::endl;
	std::cout << "The type of player determines his way of choosing the card to play\n"
	"Types:\n"
	"r - Random card\n"
	"b - Biggest card\n"
	"s - Smallest card\n";

	int i = 0;
	while (i < numberOfPlayers)
	{
		std::string name;
		char type;
		
		std::cout << ">> ";
		try
		{
			name = ReadValue<std::string>(std::cin);
			type = ReadValue<char>(std::cin);
			players[i] = PlayerFactory::getPlayer(name, type);
			i++;
		}
		catch (std::exception err)
		{
			std::cout << err.what() << std::endl << std::endl;
		}
	}
	return players;
}

void ConsoleInteractor::PrintCard(const Card& card)
{
	if (card.GetRank() >= 2 && card.GetRank() <= 10)
	{
		std::cout << card.GetRank() << " " << card.GetSuit() << std::endl;
	}
	else if(card.GetRank() >= 11 && card.GetRank() <= 14)
	{
		switch (card.GetRank())
		{
			case 11: std::cout << 'J'; break;
			case 12: std::cout << 'Q'; break;
			case 13: std::cout << 'K'; break;
			case 14: std::cout << 'A'; break;
		}
		std::cout << " " << card.GetSuit() << std::endl;
	}
}

void ConsoleInteractor::PrintAllPlayerCards(const GameTable& gameTable)
{
	for(int i = 0; i < gameTable.GetNumberOfPlayers(); i++)
	{
		std::cout << gameTable.GetPlayer(i)->GetName() << ":" << std::endl;
		for(int j = 0; j < gameTable.GetPlayer(i)->GetDeck()->GetDeckSize(); j++)
		{
			PrintCard(gameTable.GetPlayer(i)->GetDeck()->GetCard(j));
		}
	}
}

void ConsoleInteractor::PrintDeck(const GameTable& gameTable)
{
	Deck* deck = gameTable.GetDeck();
	if (deck->GetDeckSize() == 0)
	{
		throw std::logic_error("Deck is empty!");
	}
	for(int i = 0; i < deck->GetDeckSize(); i++)
	{
		PrintCard(deck->GetCard(i));
	}
}

void ConsoleInteractor::GivePlayersCards(GameTable& gameTable)
{
	std::cout << "Enter number of cards: ";
	int number = ReadValue<int>(std::cin);

	gameTable.GiveCards(number);
}

void ConsoleInteractor::Play(GameTable& gameTable, int playerIndex)
{
	int winner = gameTable.Play(playerIndex);
	std::cout << "Player " << gameTable.GetPlayer(playerIndex)->GetName() << " moves first." << std::endl;
	std::cout << "Player moves:" << std::endl;
	int i = playerIndex;
	
	do
	{
		std::cout << gameTable.GetPlayer(i)->GetName() << ": ";
		PrintCard(gameTable.GetPlayer(i)->GetDeck()->GetLastTakedCard());
		i = (i + 1) % gameTable.GetNumberOfPlayers();
	}
	while (i != playerIndex);
	
	std::cout << "Winner: " << gameTable.GetPlayer(winner)->GetName() << std::endl;
}

template <typename T>
T ConsoleInteractor::ReadValue(std::istream& stream)
{
	T res;

	std::string input;
	stream >> input;

	std::istringstream sin(input);

	if (!(sin >> res))
	{
		throw std::logic_error("Illegal value input");
	}

	char c;
	if (sin >> c)
	{
		throw std::logic_error("Garbage after value input");
	}

	return res;
}