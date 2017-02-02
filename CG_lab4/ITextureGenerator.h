#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <SDL2/SDL_surface.h>

class ITextureGenerator
{
public:
	ITextureGenerator();
	virtual  ~ITextureGenerator();

	virtual std::unique_ptr<SDL_Surface> GenerateTexture(const std::string & colorName) = 0;

protected:
	virtual std::vector<std::vector<int>> GenerateIntensityMatrix() = 0;
};

