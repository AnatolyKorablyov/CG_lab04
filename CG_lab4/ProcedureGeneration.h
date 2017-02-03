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
	SDL_Surface * GetCellularTextureByColor(const std::string & colorName);
	SDL_Surface * GetFaultFormationTextureByColor(const std::string & colorName);
	std::string ChooseColorByNum(unsigned num);

private:
	SDL_Surface * m_text;
};

