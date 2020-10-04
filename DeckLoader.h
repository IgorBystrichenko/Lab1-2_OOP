#pragma once
#include <string>
#include "Deck.h"

class DeckLoader
{
public:
	static Deck* LoadFromFile(const std::string& file);
private:
	static Card CardParser(const std::string& rank, const std::string& suit);
};

