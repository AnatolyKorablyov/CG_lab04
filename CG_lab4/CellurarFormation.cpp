#include "CellurarFormation.h"

CCellurarFormation::CCellurarFormation(glm::vec2 size, int vertexNum, int basisFuncNum)
{
	SetSize(size);
	SetVertexNumber(vertexNum);
	SetBasisFuncNumber(basisFuncNum);
}

CCellurarFormation::CCellurarFormation()
{
}

CCellurarFormation::~CCellurarFormation()
{
	std::cout << "hui";
	SDL_FreeSurface(m_texture.get());
}


void CCellurarFormation::SetSize(glm::vec2 size)
{
	m_size = size;
}

void CCellurarFormation::SetVertexNumber(int number)
{
	m_vertexNum = number;

}

void CCellurarFormation::SetBasisFuncNumber(int number)
{
	m_basisFuncNum = number;
}

std::unique_ptr<SDL_Surface> CCellurarFormation::GenerateTexture(glm::vec2 sizeScreen, glm::vec3 color)
{
	SetSize(sizeScreen);
	std::vector<std::vector<int>> txVector = GenerateIntensityMatrix();
	m_texture = std::unique_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000));

	Uint32* pixels = (Uint32 *)m_texture->pixels;

	glm::vec3 hueRGB;
	for (int x = 0; x < m_texture->h; x++)
	{
		for (int y = 0; y < m_texture->w; y++)
		{
			hueRGB = CMathFuncs::NormalizeRGBOnColor(color, txVector[x][y]);
			pixels[x + y*(m_texture->h)] = SDL_MapRGB(m_texture->format, hueRGB.r , hueRGB.g, hueRGB.b);

		}
	}

	return std::move(m_texture);
}

std::vector<std::vector<int>> CCellurarFormation::GenerateIntensityMatrix()
{
	CalcCellularTexture();
	return m_intensityMatrix;
}

void CCellurarFormation::CalcDistances(std::vector<std::vector<int>> & distBuffer, bool isFirst)
{
					
	int dist = 0;
	for (int y = 0; y < distBuffer.size(); y++)
	{
		for (int x = 0; x < distBuffer[y].size(); x++)
		{
			auto minDist = 1000;

			for (int j = 0; j < m_vertexNum; ++j)
			{
				if (x != m_xCoords[j] && y != m_yCoords[j])
				{
					dist = CMathFuncs::DistToPoint(x, y, m_xCoords[j], m_yCoords[j]);

					bool minDistLarge;
					if (isFirst)
					{
						minDistLarge = minDist > dist;
					}
					else
					{
						minDistLarge = minDist > dist && distBuffer[y][x] < dist;
					}
					if (minDistLarge)
					{
						distBuffer[y][x] = dist;
						minDist = dist;
					}
					else if (m_maxDist < dist)
					{
						m_maxDist = dist;
					}
					if (m_theSmallestDist > minDist)
					{
						m_theSmallestDist = minDist;
					}
				}
			}
		}
	}
}

void CCellurarFormation::CalcCellularTexture()
{
	std::vector<std::vector<int>> distBuffer(m_size.y, std::vector<int>(m_size.x, 0));
	m_intensityMatrix.resize(m_size.y);
	for (int j = 0; j < m_intensityMatrix.size(); ++j)
	{
		m_intensityMatrix[j].resize(m_size.x);
	}

	m_xCoords.resize(m_vertexNum);
	m_yCoords.resize(m_vertexNum);
	std::vector<int> distPoint(m_vertexNum);


	for (int i = 0; i < m_vertexNum; ++i)
	{
		m_xCoords[i] = std::rand() % int(m_size.x);
		m_yCoords[i] = std::rand() % int(m_size.y);
	}

	CalcDistances(distBuffer, true);
	for (auto i = 1; i < m_basisFuncNum; ++i)
	{
		CalcDistances(distBuffer, false);
	}

	for (int y = 0; y < m_intensityMatrix.size(); y++)
	{
		for (int x = 0; x < m_intensityMatrix[y].size(); x++)
		{
			m_intensityMatrix[y][x] = (200 - 2 * ((distBuffer[y][x] - m_theSmallestDist) * 255) / (m_maxDist / m_theSmallestDist));
		}
	}
}

void CCellurarFormation::CalcUniformCellularTexture()
{
	std::vector<std::vector<int>> distBuffer(m_size.y, std::vector<int>(m_size.x, 0));
	m_intensityMatrix.resize(m_size.y);
	for (int j = 0; j < m_intensityMatrix.size(); ++j)
	{
		m_intensityMatrix[j].resize(m_size.x);
	}

	m_xCoords.resize(m_vertexNum + 1);
	m_yCoords.resize(m_vertexNum + 1);

	ArrangementPoint();

	CalcDistances(distBuffer, true);
	for (auto i = 1; i < m_basisFuncNum; ++i)
	{
		CalcDistances(distBuffer, false);
	}
	for (int y = 0; y < m_intensityMatrix.size(); y++)
	{
		for (int x = 0; x < m_intensityMatrix[y].size(); x++)
		{
			m_intensityMatrix[y][x] = CMathFuncs::GetRandomNumberInRange(240, 255);
		}
	}

}

void CCellurarFormation::ArrangementPoint()
{

	int wSector = m_intensityMatrix.size() / 4;
	int hSector = m_intensityMatrix[0].size() / 4;
	int countSectors = (m_intensityMatrix.size() * m_intensityMatrix[0].size()) / (wSector * hSector);
	int xCurrentSector = 0;
	int yCurrentSector = 0;
	int countPoint = m_vertexNum;

	for (int i = 0; i < countSectors; i++)
	{
		int countPointInSector = CMathFuncs::GetRandomNumberInRange(1, 4);
		if (countPointInSector > wSector * hSector)
		{
			countPointInSector = wSector * hSector;
		}

		while (countPointInSector > 0)
		{

			countPointInSector--;
			int xPoint = CMathFuncs::GetRandomNumberInRange(xCurrentSector, xCurrentSector + wSector - 1);
			int yPoint = CMathFuncs::GetRandomNumberInRange(yCurrentSector, yCurrentSector + hSector - 1);
			//std::cout << xPoint << " x " << yPoint << std::endl;
			if (m_intensityMatrix[xPoint][yPoint] != 0)
				continue;
			if (countPoint > 0)
			{
				m_xCoords[countPoint] = xPoint;
				m_yCoords[countPoint] = yPoint;
				m_intensityMatrix[xPoint][yPoint] = 100;
				countPoint--;
			}
		}

		xCurrentSector += wSector;
		if (xCurrentSector >= m_intensityMatrix[0].size())
		{
			xCurrentSector = 0;
			yCurrentSector += hSector;
		}
	}
}