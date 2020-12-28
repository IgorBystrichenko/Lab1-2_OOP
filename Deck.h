#pragma once
#include <vector>
#include "Card.h"

class Deck
{
public:
	void AddCard(const Card& card) { _cards.push_back(card); }
	Card TakeCard(int index);
	void DeleteCard(int index);

	Card GetCard(int index) const { return _cards[index]; }
	int GetDeckSize() const { return _cards.size(); }
	Card GetLastTakedCard() const { return _lastTakedCard; }

private:
	std::vector<Card> _cards;

	Card _lastTakedCard;
};

