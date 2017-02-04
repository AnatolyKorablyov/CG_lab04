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
	SDL_Surface * GetCellularTextureByColor(glm::vec3 color);
	SDL_Surface * GetFaultFormationTextureByColor(glm::vec3 color);
	glm::vec3 ChooseColorByNum(unsigned num);

private:
	SDL_Surface * m_text;
};

