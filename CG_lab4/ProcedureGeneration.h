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
	std::unique_ptr<SDL_Surface> GetCellularTextureByColor(glm::vec2 size, glm::vec3 color);
	std::unique_ptr<SDL_Surface> GetFaultFormationTextureByColor(glm::vec2 size, glm::vec3 color);
	glm::vec3 ChooseColorByNum(unsigned num);

private:
	std::unique_ptr<SDL_Surface> m_text;
};

