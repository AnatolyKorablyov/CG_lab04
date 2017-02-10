#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <SDL2/SDL_surface.h>
#include "MathFuncs.h"

struct CloserStruct {
	void operator()(SDL_Surface* f) { SDL_FreeSurface(f); }
};

class ITextureGenerator
{
public:
	ITextureGenerator();
	virtual  ~ITextureGenerator();

	virtual std::unique_ptr<SDL_Surface, CloserStruct> GenerateTexture(glm::vec2 sizeScreen, glm::vec3 color) = 0;

protected:
	virtual std::vector<std::vector<int>> GenerateIntensityMatrix() = 0;
};

