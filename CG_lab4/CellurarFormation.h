#pragma once
#include "ITextureGenerator.h"
#include "MathFuncs.h"

class CCellurarFormation : public ITextureGenerator
{
public:
	CCellurarFormation();

	CCellurarFormation(glm::vec2 size, int countVertix, int countBasisFunc);

	~CCellurarFormation();

	void SetSize(glm::vec2 size);

	void SetVertexNumber(int number);

	void SetBasisFuncNumber(int number);

	std::unique_ptr<SDL_Surface> GenerateTexture(glm::vec2 sizeScreen, glm::vec3 color) override;
	std::vector<std::vector<int>> GenerateIntensityMatrix() override;
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
	std::unique_ptr<SDL_Surface> m_texture;
	std::vector<std::vector<int>> m_intensityMatrix;
	glm::vec2 m_size;	
};

