#include "BiggestCardPlayer.h"

Card BiggestCardPlayer::TakeGameCard()
{
	int index = 0;
	for (int i = 1; i < _deckSize; i++)
	{
		if (_cards[i].GetRank() > _cards[index].GetRank())
		{
			index = i;
		}
	}
	return TakeCard(index);
}

Card BiggestCardPlayer::TakeGameCardBySuit(int suit)
{
	int index = -1;
	for (int i = 0; i < _deckSize; i++)
	{
		if (_cards[i].GetSuit() == suit && (index == -1 || _cards[i].GetRank() > _cards[index].GetRank()))
		{
			index = i;
		}
	}
	
	if (index == -1)
	{
		return TakeGameCard();
	}
	else
	{
		return TakeCard(index);
	}
}
