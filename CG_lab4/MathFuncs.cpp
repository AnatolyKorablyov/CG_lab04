#include "MathFuncs.h"



CMathFuncs::~CMathFuncs()
{
}

int CMathFuncs::GetRandomNumber(int range)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(range));
	return dist(gen);
}

int CMathFuncs::GetRandomNumberInRange(int rangeStart, int rangeEnd)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(rangeStart, rangeEnd);
	return dist(gen);
}

int CMathFuncs::DistToPoint(int x1, int y1, int x2, int y2)
{
	double dist = sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
	return dist;
}
