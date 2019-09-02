#include "Level.h"

void Level::init(const char* data, int size)
{
	setSize(data, size);										// set a size for Array2D
	m_level.setSize(m_width, m_height);							// allocate a level in the memory
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			m_level(x, y) = WALL;								// set the level as Wall in default

	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i)
	{
		LevelState s;
		switch (data[i])
		{
		case '#': s = WALL; break;								// Wall for the level
		case ' ': s = COOKIE; break;							// yellow cookies 
		case 'P': s = PLAYER; break;							// player
		case 'O': s = ENEMY; break;								// enemy
		case 'U': s = POWERUP; break;							// Power Cookie
		case '\n': x = 0; ++y; s = SPACE; break;				// line break
		default: s = SPACE; break;
		}
		if (s != SPACE) { m_level(x, y) = s; ++x; }			// set the state for the level
	}
}

void Level::setSize(const char* data, int size)
{
	const char* d = data;
	m_width = m_height = 0;

	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i)
	{
		switch (data[i])
		{
		case '#': case ' ': case 'O': case 'U': case 'P': ++x; break;	// increase the x axis
		case '\n':
			++y;														// increase the y axis
			m_width = (m_width > x) ? m_width : x;
			m_height = (m_height > y) ? m_height : y;
			x = 0;
			break;
		}
	}
}

void Level::setPos(int x, int y, LevelState s)
{
	m_level(x, y) = s;													// set the state in the level
}