#pragma once

#include "../Util/Array2D.h"

class Level
{
public:
	static Level& get()
	{
		static Level* instance = new Level();
		return *instance;
	}

	enum LevelState {
		COOKIE,
		WALL,
		PLAYER,
		ENEMY,
		POWERUP,
		SPACE
	};
	Array2D<LevelState> m_level;
	int m_width;
	int m_height;

	void setPos(int x, int y, LevelState s);
	void init(const char* data, int size);

private:
	Level() : m_width(0), m_height(0) {}
	void setSize(const char* data, int size);
};