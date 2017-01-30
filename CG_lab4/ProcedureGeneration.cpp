#include "ProcedureGeneration.h"

const unsigned TEXTURE_SIZE = 100;

CProcedureGeneration::CProcedureGeneration()
{
}


CProcedureGeneration::~CProcedureGeneration()
{
}


glm::vec3 CProcedureGeneration::GetRGBhueOnName(const std::string & colorName, int colorValue)
{
	glm::vec3 hueRGB;
	if (colorName == "green")
	{
		hueRGB.r = 0;
		hueRGB.g = colorValue * 1.5;
		hueRGB.b = 0;
	}
	else if (colorName == "grey")
	{
		hueRGB = { colorValue, colorValue, colorValue };
	}
	else if (colorName == "red")
	{
		auto num = std::rand() % colorValue + colorValue * 2;
		hueRGB.r = num;
		hueRGB.g = num;
		hueRGB.b = num;
	}
	return hueRGB;
}

void CProcedureGeneration::FillingInPixels(SDL_Surface * pSur, Uint32 * pixels, const std::string & colorName)
{
	std::vector<std::vector<int>> txVector;
	if (colorName == "green")
	{
		CFaultFormation textureGenerator;
		textureGenerator.SetSize(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE));
		textureGenerator.SetDelta(1);
		textureGenerator.SetIterations(100);
		textureGenerator.CreateTexture();
		txVector = textureGenerator.GetTexture();

	}
	else
	{
		CCellurarFormation textureGenerator;
		textureGenerator.SetSize(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE));
		textureGenerator.SetBasisFuncNumber(1);
		textureGenerator.SetVertexNumber(100);
		textureGenerator.CalcCellularTexture();
		txVector = textureGenerator.GetTexture();
	}


	glm::vec3 hueRGB;
	for (int x = 0; x < pSur->w; x++)
	{
		for (int y = 0; y < pSur->h; y++)
		{
			hueRGB = GetRGBhueOnName(colorName, txVector[x][y]);
			pixels[x + y*(pSur->w)] = SDL_MapRGB(pSur->format, hueRGB.r, hueRGB.g, hueRGB.b);
		}
	}
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
