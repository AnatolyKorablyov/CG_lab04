#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

class CMathFuncs
{
public:
	CMathFuncs() = delete;
	~CMathFuncs();

	static int GetRandomNumber(int range);
	static int GetRandomNumberInRange(int rangeStart, int rangeEnd);

	static glm::vec3 GetRGBhueOnName(const std::string & colorName, int colorValue);
	static int DistToPoint(int x1, int y1, int x2, int y2);

};

