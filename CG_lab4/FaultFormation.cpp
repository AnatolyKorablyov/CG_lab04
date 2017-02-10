#include "FaultFormation.h"


CFaultFormation::CFaultFormation()
{
}
CFaultFormation::CFaultFormation(glm::vec2 size, unsigned iter, int delta)
{
	SetSize(size);
	SetIterations(iter);
	SetDelta(delta);
}

CFaultFormation::~CFaultFormation()
{
	SDL_FreeSurface(m_texture.get());
}

void CFaultFormation::SetSize(glm::vec2 size)
{
	m_size = size;
}

void CFaultFormation::SetIterations(unsigned iter)
{
	m_iteration = iter;
}

void CFaultFormation::SetDelta(int delta)
{
	m_delta = delta;
}


void CFaultFormation::CreateTexture()
{
	m_intensityMatrix.resize(m_size.y);
	for (int j = 0; j < m_intensityMatrix.size(); ++j)
	{
		m_intensityMatrix[j].resize(m_size.x);
		for (int l = 0; l < m_intensityMatrix[j].size(); ++l)
		{
			m_intensityMatrix[j][l] = 128;
		}
	}
	for (int i = 0; i < m_iteration; i++)
	{
		CreateFault();
	}
}

std::unique_ptr<SDL_Surface> CFaultFormation::GenerateTexture(glm::vec2 sizeScreen, glm::vec3 color)
{
	SetSize(sizeScreen);
	std::vector<std::vector<int>> txVector = GenerateIntensityMatrix();
	m_texture = std::unique_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));

	Uint32* pixels = (Uint32 *)m_texture->pixels;

	glm::vec3 hueRGB;
	for (int x = 0; x < m_texture->w; x++)
	{
		for (int y = 0; y < m_texture->h; y++)
		{
			hueRGB = CMathFuncs::NormalizeRGBOnColor(color, txVector[x][y]);
			pixels[x + y*(m_texture->w)] = SDL_MapRGB(m_texture->format, hueRGB.r, hueRGB.g, hueRGB.b);
		}
	}

	return std::move(m_texture);
}

std::vector<std::vector<int>> CFaultFormation::GenerateIntensityMatrix()
{
	return m_intensityMatrix;
}

void CFaultFormation::CreateFault()
{
	int xT1 = CMathFuncs::GetRandomNumber(m_intensityMatrix[0].size());
	int xB1 = CMathFuncs::GetRandomNumber(m_intensityMatrix[0].size());
	int xT2 = CMathFuncs::GetRandomNumber(xT1);
	int xB2 = CMathFuncs::GetRandomNumber(xB1);
	for (int y = 0; y < m_intensityMatrix.size(); y++)
	{
		int xLine1 = ((xT1 - xB1) * y) / m_intensityMatrix.size() + xB1;
		int xLine2 = ((xT2 - xB2) * y) / m_intensityMatrix.size() + xB2;
		for (int x = 0; x < m_intensityMatrix[y].size(); x++)
		{
			if (x <= xLine1 && x >= xLine2)
				m_intensityMatrix[y][x] = std::min(m_intensityMatrix[y][x] + m_delta, 255);
			else
				m_intensityMatrix[y][x] = std::max(m_intensityMatrix[y][x] - m_delta, 0);
		}
	}
}
