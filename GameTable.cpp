#include "GameTable.h"
#include "DeckLoader.h"
#include "RandomGenerator.h"

GameTable::~GameTable()
{
	delete _deck;
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		delete _players[i];
	}
	delete[] _players;
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
	if (number < 0 || number > _deck->GetDeckSize() / _numberOfPlayers)
	{
		throw std::exception("Wrong number of cards!");
	}
	for (int i = 0; i < number * _numberOfPlayers; i++)
	{
		_players[i / number]->AddCard(_deck->TakeCard(0));
	}
}

int GameTable::Play(int playerIndex)
{
	if (_players[0]->GetDeck()->GetDeckSize() == 0)
	{
		throw std::logic_error("Players don't have cards");
	}
	else
	{
		return DoPlay(playerIndex);
	}
}

int GameTable::DoPlay(int firstPlayer)
{
	Card biggestCard = _players[firstPlayer]->TakeGameCard();
	char suit = biggestCard.GetSuit();
	int winnerIndex = firstPlayer;

	for (int i = 0; i < _numberOfPlayers; i++)
	{
		if (i == firstPlayer)
		{
			continue;
		}
		Card playerCard = _players[i]->TakeGameCardBySuit(suit);
		if (playerCard.GetSuit() == suit && CompareCards(playerCard, biggestCard) > 0)
		{
			biggestCard = playerCard;
			winnerIndex = i;
		}
	}
	return winnerIndex;
}
