#include "Deck.h"

Card Deck::TakeCard(int index)
{
	_lastTakedCard = _cards[index];
	DeleteCard(index);
	
	return _lastTakedCard;
}

void Deck::DeleteCard(int index)
{
	for (int i = index; i < _cards.size() - 1; i++)
	{
		_cards[i] = _cards[i + 1];
	}
	_cards.pop_back();
}