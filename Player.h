#pragma once
#include "Deck.h"

class Player
{
public:
	Player(const std::string& name) : _name(name) { _deck = new Deck(); }

	std::string GetName() const { return _name; }
	Deck* GetDeck() { return _deck; }
	Card TakeCard(int index) { return _deck->TakeCard(index); }
	void AddCard(const Card& card) { _deck->AddCard(card); }
	virtual Card TakeGameCard() = 0;
	virtual Card TakeGameCardBySuit(int suit) = 0;
protected:
	std::string _name;
	Deck* _deck;
};

