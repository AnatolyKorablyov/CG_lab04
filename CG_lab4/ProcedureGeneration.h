#pragma once
#include <SDL2\SDL_surface.h>
#include <string>
#include <glm\detail\type_vec.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CellurarFormation.h"
#include "FaultFormation.h"

class CProcedureGeneration
{
public:
	CProcedureGeneration();
	~CProcedureGeneration();
	glm::vec3 GetRGBhueOnName(const std::string & colorName, int colorValue);
	void FillingInPixels(SDL_Surface * pSur, Uint32 * pixels, const std::string & colorName);
};

