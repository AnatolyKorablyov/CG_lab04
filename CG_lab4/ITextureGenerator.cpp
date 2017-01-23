#include "ITextureGenerator.h"



ITextureGenerator::ITextureGenerator()
{
}


ITextureGenerator::~ITextureGenerator()
{
}

std::vector<std::vector<int>> ITextureGenerator::CreateFaultTexture(int w, int h, int countItr, int delta)
{
	std::vector<std::vector<int>> picsels(w, std::vector<int>(h, 128));
	for (int i = 0; i < countItr; i++)
	{
		CreateFault(picsels, delta);
	}
	return picsels;
}


void ITextureGenerator::CalcDistancesFirstIteration(std::vector<std::vector<int>> & distBuffer, int countVertix)
{
	double dist = 0.0;
	for (int y = 0; y < distBuffer.size(); y++)
	{
		for (int x = 0; x < distBuffer[y].size(); x++)
		{
			auto minDist = 1000;

			for (int j = 0; j < countVertix; ++j)
			{
				if (x != xcoords[j] && y != ycoords[j])
				{
					dist = DistToPoint(x, y, xcoords[j], ycoords[j]);
					if (minDist > dist)
					{
						distBuffer[y][x] = dist;
						minDist = dist;
					}
					else if (maxDist < dist)
					{
						maxDist = dist;
					}
					if (theSmallestDist > minDist)
					{
						theSmallestDist = minDist;
					}
				}
			}
		}
	}
}

void ITextureGenerator::CalcDistancesNextIteration(std::vector<std::vector<int>> & distBuffer, int countVertix)
{
	double dist = 0.0;
	maxDist = 1;
	theSmallestDist = 1000;
	for (int y = 0; y < distBuffer.size(); y++)
	{
		for (int x = 0; x < distBuffer[y].size(); x++)
		{
			auto minDist = 1000;

			for (int j = 0; j < countVertix; ++j)
			{
				if (x != xcoords[j] && y != ycoords[j])
				{
					dist = DistToPoint(x, y, xcoords[j], ycoords[j]);
					if (minDist > dist && distBuffer[y][x] < dist)
					{
						distBuffer[y][x] = dist;
						minDist = dist;
					}
					else if (maxDist < dist)
					{
						maxDist = dist;
					}
					if (theSmallestDist > minDist)
					{
						theSmallestDist = minDist;
					}
				}
			}
		}
	}
}

std::vector<std::vector<int>> ITextureGenerator::CreateCellularTexture(int w, int h, int countVertix, int countBasisFunc)
{
	std::vector<std::vector<int>> picsels(w, std::vector<int>(h, 255));
	std::vector<std::vector<int>> distBuffer(w, std::vector<int>(h, 0));

	xcoords.resize(countVertix);
	ycoords.resize(countVertix);
	std::vector<int> distPoint(countVertix);


	for (int i = 0; i < countVertix; ++i)
	{
		xcoords[i] = std::rand() % w;
		ycoords[i] = std::rand() % h;
	}

	CalcDistancesFirstIteration(distBuffer, countVertix);

	for (auto i = 0; i < countBasisFunc; ++i)
	{
		CalcDistancesNextIteration(distBuffer, countVertix);
	}
	
	for (int y = 0; y < picsels.size(); y++)
	{
		for (int x = 0; x < picsels[y].size(); x++)
		{
			picsels[y][x] = (200 - 2*((distBuffer[y][x] - theSmallestDist) * 255) / (maxDist / theSmallestDist));
		}
	}
	return picsels;
}

void ITextureGenerator::CreateFault(std::vector<std::vector<int>>& pic, int delta)
{
	int xT1;
	int xB1;
	int xT2;
	int xB2;
	xT1 = GetRandomNumber(pic[0].size());
	xB1 = GetRandomNumber(pic[0].size());
	xT2 = GetRandomNumber(xT1);
	xB2 = GetRandomNumber(xB1);
	for (int y = 0; y < pic.size(); y++)
	{
		int xLine1 = ((xT1 - xB1) * y) / pic.size() + xB1;
		int xLine2 = ((xT2 - xB2) * y) / pic.size() + xB2;
		for (int x = 0; x < pic[y].size(); x++)
		{
			if (x <= xLine1 && x >= xLine2)
				pic[y][x] = std::min(pic[y][x] + delta, 255);
			else
				pic[y][x] = std::max(pic[y][x] - delta, 0);
		}
	}
}

int ITextureGenerator::DistToPoint(int x1, int y1, int x2, int y2)
{
	double dist = sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
	return dist;
}

int ITextureGenerator::GetRandomNumber(int range)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(range));
	return dist(gen);
}
