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


void ITextureGenerator::CalcDistances(std::vector<std::vector<int>> & distBuffer, int countVertix, bool isFirst)
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

					bool minDistLarge;
					if (isFirst)
					{
						minDistLarge = minDist > dist;
					}
					else
					{
						minDistLarge = minDist > dist && distBuffer[y][x] < dist;
					}
					if (minDistLarge)
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


std::vector<std::vector<int>> ITextureGenerator::GetCellularTexture(int w, int h, int countVertix, int countBasisFunc)
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

	CalcDistances(distBuffer, countVertix, true);
	for (auto i = 1; i < countBasisFunc; ++i)
	{
		CalcDistances(distBuffer, countVertix, false);
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

void ITextureGenerator::ArrangementPoint(std::vector<std::vector<int>> & texture, int countPoint)
{
	int wSector = texture.size() / 4;
	int hSector = texture[0].size() / 4;
	int countSectors = (texture.size() * texture[0].size()) / (wSector * hSector);
	int xCurrentSector = 0;
	int yCurrentSector = 0;
	for (int i = 0; i < countSectors; i++)
	{
		int countPointInSector = GetRandomNumberInRange(1, 4);
		if (countPointInSector > wSector * hSector)
		{
			countPointInSector = wSector * hSector;
		}
			
		while (countPointInSector > 0)
		{

			countPointInSector--;
			int xPoint = GetRandomNumberInRange(xCurrentSector, xCurrentSector + wSector - 1);
			int yPoint = GetRandomNumberInRange(yCurrentSector, yCurrentSector + hSector - 1);
			//std::cout << xPoint << " x " << yPoint << std::endl;
			if (texture[xPoint][yPoint] != 0)
				continue;
			if (countPoint > 0)
			{
				xcoords[countPoint] = xPoint;
				ycoords[countPoint] = yPoint;
				texture[xPoint][yPoint] = 100;
				countPoint--;
			}
		}

		xCurrentSector += wSector;
		if (xCurrentSector >= texture[0].size())
		{
			xCurrentSector = 0;
			yCurrentSector += hSector;
		}
	}
}

std::vector<std::vector<int>> ITextureGenerator::GetUniformCellularTexture(int w, int h, int countVertix, int countBasisFunc)
{
	std::vector<std::vector<int>> picsels(w, std::vector<int>(h, 0));
	std::vector<std::vector<int>> distBuffer(w, std::vector<int>(h, 0));
	xcoords.resize(countVertix + 1);
	ycoords.resize(countVertix + 1);

	ArrangementPoint(picsels, countVertix);

	CalcDistances(distBuffer, countVertix, true);
	for (auto i = 1; i < countBasisFunc; ++i)
	{
		CalcDistances(distBuffer, countVertix, false);
	}
	for (int y = 0; y < picsels.size(); y++)
	{
		for (int x = 0; x < picsels[y].size(); x++)
		{
			picsels[y][x] = (255 - distBuffer[y][x] * 10);
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

int ITextureGenerator::GetRandomNumberInRange(int rangeStart, int rangeEnd)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(rangeStart, rangeEnd);
	return dist(gen);
}