#pragma once
#include "ITextureGenerator.h"
#include "MathFunc.h"

class CCellurarFormation : public ITextureGenerator
{
public:
	CCellurarFormation();

	CCellurarFormation(glm::vec2 size, int countVertix, int countBasisFunc);

	~CCellurarFormation();

	void SetSize(glm::vec2 size) override;

	void SetVertexNumber(int number);

	void SetBasisFuncNumber(int number);

	std::vector<std::vector<int>> GetTexture() override;
	void CalcCellularTexture();

	void CalcUniformCellularTexture();


private:
	void CalcDistances(std::vector<std::vector<int>>& distBuffer, bool isFirst);
	void ArrangementPoint();

private:
	int m_vertexNum;
	int m_basisFuncNum;
	std::vector<int> m_xCoords;
	std::vector<int> m_yCoords;
	int m_maxDist = 1;
	int m_theSmallestDist = 1000;


};

