
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>


int GetRandomNumber(int range)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(range));
	return dist(gen);
}

void CreateFault(std::vector<std::vector<int>> & pic, int delta)
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

std::vector<std::vector<int>> CreateFaultVector(int w, int h, int countItr, int delta = 5)
{
	std::vector<std::vector<int>> picsels(w, std::vector<int>(h, 128));
	for (int i = 0; i < countItr; i++)
	{
		CreateFault(picsels, delta);
	}
	/*for (int i = 0; i < picsels.size(); i++)
	{
		for (int k = 0; k < picsels[i].size(); k++)
			std::cout << picsels[i][k] << ' ';
		std::cout << std::endl;
	}*/
	return picsels;
}


