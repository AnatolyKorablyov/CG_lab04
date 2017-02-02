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
	m_texture.resize(m_size.y);
	for (int j = 0; j < m_texture.size(); ++j)
	{
		m_texture[j].resize(m_size.x);
		for (int l = 0; l < m_texture[j].size(); ++l)
		{
			m_texture[j][l] = 128;
		}
	}
	for (int i = 0; i < m_iteration; i++)
	{
		CreateFault();
	}
}

std::vector<std::vector<int>> CFaultFormation::GetTexture()
{
	return m_texture;
}

void CFaultFormation::CreateFault()
{
	CMathFuncs maths;
	int xT1;
	int xB1;
	int xT2;
	int xB2;
	xT1 = maths.GetRandomNumber(m_texture[0].size());
	xB1 = maths.GetRandomNumber(m_texture[0].size());
	xT2 = maths.GetRandomNumber(xT1);
	xB2 = maths.GetRandomNumber(xB1);
	for (int y = 0; y < m_texture.size(); y++)
	{
		int xLine1 = ((xT1 - xB1) * y) / m_texture.size() + xB1;
		int xLine2 = ((xT2 - xB2) * y) / m_texture.size() + xB2;
		for (int x = 0; x < m_texture[y].size(); x++)
		{
			if (x <= xLine1 && x >= xLine2)
				m_texture[y][x] = std::min(m_texture[y][x] + m_delta, 255);
			else
				m_texture[y][x] = std::max(m_texture[y][x] - m_delta, 0);
		}
	}
}
