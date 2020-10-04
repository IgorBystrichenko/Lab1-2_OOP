#include "DeckLoader.h"
#include "Deck.h"
#include <fstream>
#include <iostream>


Deck* DeckLoader::LoadFromFile(const std::string& file)
{
	std::fstream fin;
	fin.open(file);
	
	Deck* deck = new Deck();

	if (fin.is_open())
	{
		while(!fin.eof())
		{
			std::string rank;
			std::string suit;
			if (fin >> rank >> suit)
			{
				Card temp = CardParser(rank, suit);
				deck->AddCard(temp);
			}
		}
		
	}
	else
	{
		throw std::runtime_error("File not found exception");
	}
	
	return deck;
}

Card DeckLoader::CardParser(const std::string& rank, const std::string& suit)
{
	int cardRank = -1;
	char cardSuit = -1;
	
	if(rank == "10")
	{
		cardRank = 10;
	}
	else if(rank.length() == 1)
	{
		if(rank[0] >= '2' && rank[0] <= '9')
		{
			cardRank = rank[0] - '0';
		}
		else
		{
			switch (rank[0])
			{
			case 'J': cardRank = 11; break;
			case 'Q': cardRank = 12; break;
			case 'K': cardRank = 13; break;
			case 'A': cardRank = 14; break;
			}
		}
	}

	if(suit.length() == 1 && suit[0] >= '1' && suit[0] <= '4')
	{
		cardSuit = suit[0];
	}

	if(cardRank == -1 || cardSuit == -1)
	{
		throw std::runtime_error("Card parser exception");
		
	}
	
	return Card(cardRank, cardSuit);
}
