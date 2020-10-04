#pragma once
#include <stdexcept>
#include "Card.h"

class Deck
{
public:
	const int DEFAULT_BUFF_SIZE = 36;
	
	Deck()
	{
		_cards = new Card[DEFAULT_BUFF_SIZE];
	}
	
	~Deck()
	{
		if (_cards != nullptr)
		{
			delete[] _cards;
		}
	}
	
	void AddCard(const Card& card);
	Card TakeCard(int index);
	void DeleteCard(int index);

	Card GetCard(int index) const { return _cards[index]; }
	int GetDeckSize() const { return _deckSize; }
	Card GetLastTakedCard() const { return _lastTakedCard; }
protected:
	
	Card* _cards = nullptr;
	int _deckSize = 0;
	int _bufSize = DEFAULT_BUFF_SIZE;

	Card _lastTakedCard;

	void IncreaseBufferSize();
	
};

