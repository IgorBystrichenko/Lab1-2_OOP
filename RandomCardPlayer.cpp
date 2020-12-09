#include "RandomCardPlayer.h"
#include "RandomGenerator.h"

Card RandomCardPlayer::TakeGameCard()
{
	return TakeCard(RandomGenerator::GenerareRandomInt(0, _deck->GetDeckSize()));
}

Card RandomCardPlayer::TakeGameCardBySuit(int suit)
{
	int count = 0;
	for (int i = 0; i < _deck->GetDeckSize(); i++)
	{
		
		if (_deck->GetCard(i).GetSuit() == suit)
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
		for (int i = 0; i < _deck->GetDeckSize() && rand > 0; i++)
		{
			if (_deck->GetCard(i).GetSuit() == suit)
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

