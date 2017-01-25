#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>


class ITextureGenerator
{
public:
	ITextureGenerator();
	~ITextureGenerator();

	std::vector<std::vector<int>> CreateFaultTexture(int w, int h, int countItr, int delta = 5);
	
	
	
	std::vector<std::vector<int>> GetCellularTexture(int w, int h, int countVertix, int countBasisFunc);

	
	std::vector<std::vector<int>> GetUniformCellularTexture(int w, int h, int countVertix, int countBasisFunc);

private:
	void CreateFault(std::vector<std::vector<int>> & pic, int delta);
	int DistToPoint(int x1, int y1, int x2, int y2);
	int GetRandomNumber(int range);
	int GetRandomNumberInRange(int rangeStart, int rangeEnd);
	void CalcDistances(std::vector<std::vector<int>>& distBuffer, int countVertix, bool isFirst);

	void ArrangementPoint(std::vector<std::vector<int>>& texture, int countPoint);

	
private:

	std::vector<int> xcoords;
	std::vector<int> ycoords;		 


	int maxDist = 1;
	int theSmallestDist = 1000;
};

