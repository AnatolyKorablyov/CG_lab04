#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class CMathFuncs
{
public:
	CMathFuncs() = default;
	~CMathFuncs();

	static int GetRandomNumber(int range);
	static int GetRandomNumberInRange(int rangeStart, int rangeEnd);

	static int DistToPoint(int x1, int y1, int x2, int y2);

};

