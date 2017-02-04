#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "MathFuncs.h"
#include "ITextureGenerator.h"

class CFaultFormation : public ITextureGenerator
{
public:
	CFaultFormation();
	CFaultFormation(glm::vec2 size, unsigned iter, int delta);
	~CFaultFormation();

	void SetSize(glm::vec2 size);
	void SetIterations(unsigned iter);
	void SetDelta(int delta);
			
	void CreateTexture();
	std::unique_ptr<SDL_Surface> GenerateTexture(glm::vec2 sizeScreen, glm::vec3 color) override;
	std::vector<std::vector<int>> GenerateIntensityMatrix() override;

private:
	void CreateFault();
private:
	unsigned m_iteration = 0;
	int m_delta = 5;
	std::vector<std::vector<int>> m_texture;
	glm::vec2 m_size;
};

