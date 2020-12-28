#include "ConsoleInteractor.h"
#include <sstream>
#include <iostream>
#include "BiggestCardPlayer.h"
#include "GameTable.h"
#include "DeckLoader.h"
#include "RandomCardPlayer.h"
#include "SmallestCardPlayer.h"
#include "PlayerFactory.h"
#include "IdentifierGenerator.h"
#include <map>
#include <set>

enum Comands
{
	rules, shuffle, pdeck, pplayercards, prating, givecards, play
};

void ConsoleInteractor::Start()
{
	GameTable gameTable = CreateGameTable();
	PrintRules();

	auto firstPlayer = gameTable.GetPlayersData()->PlayerMapById()->begin();
	while (true)
	{
		try
		{
			std::cout << "Enter next command:\n>> ";
			int temp = ReadValue<int>(std::cin);
			
			switch (temp)
			{
			case rules: PrintRules(); break;
			case shuffle: gameTable.ShuffleDeck(); break;
			case pdeck: PrintDeck(gameTable); break;
			case pplayercards: PrintAllPlayerCards(gameTable); break;
			case prating: PrintRating(gameTable); break;
			case givecards: GivePlayersCards(gameTable); break;
			case play: Play(gameTable, firstPlayer->first);
				std::cout << firstPlayer->first << std::endl;
				firstPlayer++; 
				if (firstPlayer == gameTable.GetPlayersData()->PlayerMapById()->end())
				{
					firstPlayer = gameTable.GetPlayersData()->PlayerMapById()->begin();
				}
				break;
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
	
	
	PlayersData* data = PlayersParser(numberOfPlayers);
	return GameTable(data, deck);
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

PlayersData* ConsoleInteractor::PlayersParser(int numberOfPlayers)
{
	std::map<int, Player*>* players = new std::map<int, Player*>();
	std::cout << "\nEnter players \"Name type\"" << std::endl;
	std::cout << "The type of player determines his way of choosing the card to play\n"
	"Types:\n"
	"r - Random card\n"
	"b - Biggest card\n"
	"s - Smallest card\n";

	int i = 0;
	IdentifierGenerator gen;
	while (i < numberOfPlayers)
	{
		std::string name;
		char type;
		
		std::cout << ">> ";
		try
		{
			name = ReadValue<std::string>(std::cin);
			type = ReadValue<char>(std::cin);

			players->insert(std::pair<int, Player*>(gen.NextId(), PlayerFactory::getPlayer(name, type)));
			i++;
		}
		catch (std::exception err)
		{
			std::cout << err.what() << std::endl << std::endl;
		}
	}
	return new PlayersData(players);
}

void ConsoleInteractor::PrintRules()
{
	std::cout <<
		"\nCommands:\n" <<
		rules << " - Print rules\n" <<
		shuffle << " - Shuffle deck\n" <<
		pdeck << " - Print deck\n" <<
		pplayercards << " - Print player cards\n" <<
		prating << " - Print leaderboard\n" <<
		givecards << " - Give player cards\n" <<
		play << " - Play\n";
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
	std::map<int, Player*>* map = gameTable.GetPlayersData()->PlayerMapById();
	for(auto i = map->begin(); i != map->end(); i++)
	{
		std::cout << i->second->GetName() << ":" << std::endl;
		for(int j = 0; j < i->second->GetDeck()->GetDeckSize(); j++)
		{
			PrintCard(i->second->GetDeck()->GetCard(j));
		}
	}
}

void ConsoleInteractor::PrintRating(const GameTable& gameTable)
{
	std::map<int, std::set<int>>* wmap = gameTable.GetPlayersData()->PlayerMapByWinnings();
	for (auto i = wmap->rbegin(); i != wmap->rend(); i++)
	{
		std::set<int> list = i->second;
		for (auto j = list.begin(); j != list.end(); j++)
		{
			std::cout << gameTable.GetPlayersData()->GetPlayerById(*j)->GetName() << ":" << i->first << std::endl;
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
	PlayersData* data = gameTable.GetPlayersData();
	int winner = gameTable.Play(playerIndex);
	std::cout << "Player " << data->GetPlayerById(playerIndex)->GetName() << " moves first." << std::endl;
	std::cout << "Player moves:" << std::endl;
	auto i = data->PlayerMapById()->find(playerIndex);
	
	do
	{
		std::cout << i->second->GetName() << ": ";
		PrintCard(i->second->GetDeck()->GetLastTakedCard());
		i++;
		if (i == data->PlayerMapById()->end())
		{
			i = data->PlayerMapById()->begin();
		}
	}
	while (i->first != playerIndex);
	
	std::cout << "Winner: " << data->GetPlayerById(winner)->GetName() << std::endl;
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