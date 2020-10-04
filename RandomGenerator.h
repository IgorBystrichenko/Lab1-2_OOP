#pragma once
#include <random>

class RandomGenerator
{
public:
	static int GenerareRandomInt(int from, int to)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(from, to);
		return dist(gen);
	}
};
