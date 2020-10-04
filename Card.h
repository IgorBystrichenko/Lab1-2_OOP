#pragma once

class Card
{
public:
	Card(int rank = 0, char suit = 0) : _rank(rank), _suit(suit) {}
	int GetRank() const { return _rank; }
	char GetSuit() const { return _suit; }
	
private:
	int _rank;
	char _suit;
};
