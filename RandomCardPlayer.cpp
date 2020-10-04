#include "RandomCardPlayer.h"
#include "RandomGenerator.h"

Card RandomCardPlayer::TakeGameCard()
{
	return TakeCard(RandomGenerator::GenerareRandomInt(0, _deckSize));
}

Card RandomCardPlayer::TakeGameCardBySuit(int suit)
{
	int count = 0;
	for (int i = 0; i < _deckSize; i++)
	{
		if (_cards[i].GetSuit() == suit)
		{
			count++;
		}
	}
	
	if(count == 0)
	{
		return TakeGameCard();
	}
	else
	{
		int rand = RandomGenerator::GenerareRandomInt(1, count);
		int index = -1;
		for (int i = 0; i < _deckSize && rand > 0; i++)
		{
			if (_cards[i].GetSuit() == suit)
			{
				rand--;
				if (rand == 0)
				{
					index = i;
				}
			}
		}

		return TakeCard(index);
	}
}

