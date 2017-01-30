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

std::vector<std::vector<int>> CCellurarFormation::GetTexture()
{
	
	return m_texture;
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
					dist = DistToPoint(x, y, m_xCoords[j], m_yCoords[j]);

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
	m_texture.resize(m_size.y);
	for (int j = 0; j < m_texture.size(); ++j)
	{
		m_texture[j].resize(m_size.x);
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

	for (int y = 0; y < m_texture.size(); y++)
	{
		for (int x = 0; x < m_texture[y].size(); x++)
		{
			m_texture[y][x] = (200 - 2 * ((distBuffer[y][x] - m_theSmallestDist) * 255) / (m_maxDist / m_theSmallestDist));
		}
	}
}

void CCellurarFormation::CalcUniformCellularTexture()
{
	std::vector<std::vector<int>> distBuffer(m_size.y, std::vector<int>(m_size.x, 0));
	m_texture.resize(m_size.y);
	for (int j = 0; j < m_texture.size(); ++j)
	{
		m_texture[j].resize(m_size.x);
	}

	m_xCoords.resize(m_vertexNum + 1);
	m_yCoords.resize(m_vertexNum + 1);

	ArrangementPoint();

	CalcDistances(distBuffer, true);
	for (auto i = 1; i < m_basisFuncNum; ++i)
	{
		CalcDistances(distBuffer, false);
	}
	for (int y = 0; y < m_texture.size(); y++)
	{
		for (int x = 0; x < m_texture[y].size(); x++)
		{
			m_texture[y][x] = GetRandomNumberInRange(240, 255);
			//m_texture[y][x] = (distBuffer[y][x] * 10);
		}
	}

}

void CCellurarFormation::ArrangementPoint()
{
	int wSector = m_texture.size() / 4;
	int hSector = m_texture[0].size() / 4;
	int countSectors = (m_texture.size() * m_texture[0].size()) / (wSector * hSector);
	int xCurrentSector = 0;
	int yCurrentSector = 0;
	int countPoint = m_vertexNum;

	for (int i = 0; i < countSectors; i++)
	{
		int countPointInSector = GetRandomNumberInRange(1, 4);
		if (countPointInSector > wSector * hSector)
		{
			countPointInSector = wSector * hSector;
		}

		while (countPointInSector > 0)
		{

			countPointInSector--;
			int xPoint = GetRandomNumberInRange(xCurrentSector, xCurrentSector + wSector - 1);
			int yPoint = GetRandomNumberInRange(yCurrentSector, yCurrentSector + hSector - 1);
			//std::cout << xPoint << " x " << yPoint << std::endl;
			if (m_texture[xPoint][yPoint] != 0)
				continue;
			if (countPoint > 0)
			{
				m_xCoords[countPoint] = xPoint;
				m_yCoords[countPoint] = yPoint;
				m_texture[xPoint][yPoint] = 100;
				countPoint--;
			}
		}

		xCurrentSector += wSector;
		if (xCurrentSector >= m_texture[0].size())
		{
			xCurrentSector = 0;
			yCurrentSector += hSector;
		}
	}
}