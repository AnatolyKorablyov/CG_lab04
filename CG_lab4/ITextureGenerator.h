#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>


class ITextureGenerator
{
public:
	ITextureGenerator();
	virtual  ~ITextureGenerator();


	virtual void SetSize(glm::vec2 size) = 0;
	virtual std::vector<std::vector<int>> GetTexture() = 0;
};

