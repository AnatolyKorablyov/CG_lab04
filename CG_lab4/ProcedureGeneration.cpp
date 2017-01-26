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
		//auto randNum = std::rand() % 130;
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
	//auto txVector = CreateFaultVector(1000, 1000, 100, 1);
	
	std::vector<std::vector<int>> txVector;
	if (colorName == "green")
	{
		//txVector = textureGenerator.GetUniformCellularTexture(TEXTURE_SIZE, TEXTURE_SIZE, 100, 3);
		//txVector = textureGenerator.CreateFaultTexture(TEXTURE_SIZE, TEXTURE_SIZE, 100, 1);
		//auto txVector = textureGenerator.CreateCellularTexture(100, 100, 10, 5);
		CFaultFormation textureGenerator;
		textureGenerator.SetSize(glm::vec2(TEXTURE_SIZE, TEXTURE_SIZE));
		textureGenerator.SetIterations(100);
		textureGenerator.SetDelta(1);
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
		//txVector = textureGenerator.GetUniformCellularTexture(TEXTURE_SIZE, TEXTURE_SIZE, 100, 1);
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
