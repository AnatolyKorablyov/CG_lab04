#include "ProcedureGeneration.h"

const unsigned TEXTURE_SIZE = 100;

CProcedureGeneration::CProcedureGeneration()
{
}


CProcedureGeneration::~CProcedureGeneration()
{		
	SDL_FillRect(m_text, NULL, 0x000000);
	//delete m_text;
}

SDL_Surface * CProcedureGeneration::GetCellularTextureByColor(const std::string & colorName)
{
	CCellurarFormation textureGenerator;
	textureGenerator.SetSize(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE));
	textureGenerator.SetBasisFuncNumber(1);
	textureGenerator.SetVertexNumber(100);
	textureGenerator.CalcCellularTexture();
	m_text = textureGenerator.GenerateTexture(colorName).get();
	return m_text;
}

SDL_Surface * CProcedureGeneration::GetFaultFormationTextureByColor(const std::string & colorName)
{
	CFaultFormation textureGenerator;
	textureGenerator.SetSize(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE));
	textureGenerator.SetDelta(1);
	textureGenerator.SetIterations(100);
	textureGenerator.CreateTexture();
	m_text = textureGenerator.GenerateTexture(colorName).get();
	return m_text;

}



std::string CProcedureGeneration::ChooseColorByNum(unsigned num)
{
	std::string colorName;
	switch (num)
	{
	case 0:
		colorName = "green";
		break;
	default:
		colorName = "grey";
	}
	return colorName;
}
