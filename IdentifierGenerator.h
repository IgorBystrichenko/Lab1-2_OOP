#pragma once
class IdentifierGenerator
{
public:
	IdentifierGenerator() : last(1) {}
	int NextId() { return last++; }
private: 
	int last;
};

