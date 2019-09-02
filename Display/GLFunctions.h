#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>

namespace GL
{
	void start(int width, int height);
	void clear();
	void cubeWall(float x, float y);
	void createWalls();

	void pointPos(float x, float y, float height, float col, float row);
	void pointCircle(float x, float y, sf::Color color, float size);
	void enemyEye(float x, float y, sf::Color color, float size);
}
