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

glm::vec3 CMathFuncs::NormalizeRGBOnColor(glm::vec3 color, int colorValue)
{
	glm::vec3 hueRGB = { color.r * colorValue, color.g * colorValue, color.b * colorValue };
	return hueRGB;
}

glm::vec3 CMathFuncs::GetRGBhueOnName(const std::string & colorName, int colorValue)
{
	glm::vec3 hueRGB;
	if (colorName == "green")
	{
		hueRGB.r = 0;
		hueRGB.g = colorValue * 1.5;
		hueRGB.b = 0;
	}
	else if (colorName == "grey")
	{
		hueRGB = { colorValue, colorValue, colorValue };
	}
	else if (colorName == "red")
	{
		auto num = std::rand() % colorValue + colorValue * 2;
		hueRGB.r = num;
		hueRGB.g = num;
		hueRGB.b = num;
	}
	return hueRGB;
}

int CMathFuncs::DistToPoint(int x1, int y1, int x2, int y2)
{
	double dist = sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
	return dist;
}
