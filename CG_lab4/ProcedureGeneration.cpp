#include "ProcedureGeneration.h"

const unsigned TEXTURE_SIZE = 100;

CProcedureGeneration::CProcedureGeneration()
{
}


CProcedureGeneration::~CProcedureGeneration()
{		
	SDL_FreeSurface(m_text);
	delete m_text;
}

SDL_Surface * CProcedureGeneration::GetCellularTextureByColor(glm::vec3 color)
{
	CCellurarFormation textureGenerator;
	textureGenerator.SetBasisFuncNumber(1);
	textureGenerator.SetVertexNumber(100);
	m_text = textureGenerator.GenerateTexture(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE), color).get();
	return m_text;
}

SDL_Surface * CProcedureGeneration::GetFaultFormationTextureByColor(glm::vec3 color)
{
	CFaultFormation textureGenerator;
	textureGenerator.SetDelta(1);
	textureGenerator.SetIterations(100);
	m_text = textureGenerator.GenerateTexture(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE), color).get();
	return m_text;
}



glm::vec3 CProcedureGeneration::ChooseColorByNum(unsigned num)
{
	glm::vec3 color;
	switch (num)
	{
	case 0:
		color = {0, 255, 0};
		break;
	case 1:
		color = { 255, 0, 0 };
		break;
	case 2:
		color = { 0, 0, 255 };
		break;
	default:
		color = { 200, 200, 200};
	}
	return color;
}
