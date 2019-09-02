#include "GLFunctions.h"
#include "../Level.h"

// all OpenGL functions

float pointSize = 0;

void GL::start(int width, int height)
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (double)width / height, 1, 1000);
	gluLookAt(0, 12, -5, 0, 0, 0, 0, 1, 0);
	glTranslatef(9.5, 0, 12);
}

void GL::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GL::createWalls()														// create the level with walls
{
	for (int y = 0; y < Level::get().m_height; ++y)
		for (int x = 0; x < Level::get().m_width; ++x)
		{
			if (Level::get().m_level(x, y) == Level::get().WALL)
			{
				cubeWall(x, y);
			}
			if (Level::get().m_level(x, y) == Level::get().COOKIE)
			{
				pointCircle(x, y, sf::Color::Yellow, 7);
			}
			if (Level::get().m_level(x, y) == Level::get().POWERUP)
			{
				pointCircle(x, y, sf::Color::Yellow, pointSize +=0.2f);
				if (pointSize >= 25) pointSize = 0;
			}
		}
}

void GL::cubeWall(float x, float y)
{
	glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 1, 1); glVertex3f(0 - x, 0.5f, -0.5f - y);
		glColor3f(0, 0.3f, 0.3f); glVertex3f(-0.5f - x, 0.5f, 0.5f - y);
		glColor3f(0, 0.3f, 0.3f); glVertex3f(0.5f - x, 0.5f, 0.5f - y);

		glColor3f(0.5f, 1, 1); glVertex3f(0 - x, 0.5f, -0.5f - y);
		glColor3f(0, 0.4f, 0.2f); glVertex3f(-0.5f - x, 0.5f, 0.5f - y);
		glColor3f(0, 0.4f, 0.2f); glVertex3f(-0.5f - x, 0, 0 - y);

		glColor3f(0.5f, 1, 1); glVertex3f(0 - x, 0.5f, -0.5f - y);
		glColor3f(0, 0.2f, 0.4f); glVertex3f(0.5f - x, 0.5f, 0.5f - y);
		glColor3f(0, 0.2f, 0.4f); glVertex3f(0.5f - x, 0, 0 - y);
	glEnd();
}

void GL::pointPos(float x, float y, float height, float col, float row)
{
	glPointSize(10);
	glBegin(GL_POINTS);
		if (height != 0)
		{
			glColor3f(height+0.3f+ col, height+0.5f, height+0.8f);
			glVertex3f(0 - x + col - 0.5f, height+0.3f, 0 - y + row-0.3f);
		}
	glEnd();
}

void GL::pointCircle(float x, float y, sf::Color color, float size)
{
	glPointSize(size);
	glBegin(GL_POINTS);
		glColor3f(color.r, color.g, color.b);
		glVertex3f(0-x, 0.4f, 0-y);
	glEnd();
}

void GL::enemyEye(float x, float y, sf::Color color, float size)			// enemy eyes
{
	glPointSize(size);
	glBegin(GL_POINTS);
		glColor3f(color.r, color.g, color.b);
		glVertex3f(0.2 - x, 0.4f, -0.1 - y);
		glVertex3f(-0.2 - x, 0.4f, -0.1 - y);
	glEnd();

	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(0, 0, 0);
		glVertex3f(0.2 - x, 0.4f, -0.1 - y);
		glVertex3f(-0.2 - x, 0.4f, -0.1 - y);
	glEnd();
}