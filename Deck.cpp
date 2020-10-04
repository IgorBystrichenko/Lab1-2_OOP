#include "Deck.h"

void Deck::AddCard(const Card& card)
{
	if (_deckSize == _bufSize)
	{
		IncreaseBufferSize();
	}
	
	_cards[_deckSize] = card;
	_deckSize++;
}

Card Deck::TakeCard(int index)
{
	_lastTakedCard = _cards[index];
	DeleteCard(index);
	
	return _lastTakedCard;
}

void Deck::DeleteCard(int index)
{
	for (int i = index; i < _deckSize; i++)
	{
		_cards[i] = _cards[i + 1];
	}
	_deckSize--;
}

void Deck::IncreaseBufferSize()
{
	_bufSize *= 2;
	Card* temp = new Card[_bufSize];
	
	for (int i = 0; i < _deckSize; i++)
	{
		temp[i] = _cards[i];
	}
	delete[] _cards;
	_cards = temp;

}
