#include "Object.h"
#include "../Display/GLFunctions.h"
#include "../ResManager/ResourceHolder.h"

Object::Object()
	: pos(0,0), originPos(0,0), moving(0), speed(0), isPowerUp(false), objectStep(0), playerLife(3), score(0)
{
}

void Object::addComponent(std::unique_ptr<ComponentBase> com)
{
	m_components.push_back(std::move(com));										// add the components
}

void Object::update(float dt)
{
	for (auto& component : m_components)										// excute update() for all objects
	{
		component->update(dt);
	}
}

void Object::draw()
{
	if (objectStep == 1)														// if the object is dead
	{
		for (int i = 0; i < m_animation.getCurrentFrame().length(); ++i)		// explosion
		{
			float x = speed*std::cos(3.14 * 2 * i / m_animation.getCurrentFrame().length());
			float y = speed*std::sin(3.14 * 2 * i / m_animation.getCurrentFrame().length());
			GL::pointCircle(originPos.x+x, originPos.y+y, sf::Color::Red, 10);
		}
		speed += 0.05f;

		if (speed >= 5) objectStep = 2;
	}
	else if(objectStep == 0)
	{
		float col = 0;
		float row = 0;

		for (int i = 0; i < m_animation.getCurrentFrame().length(); ++i)		// draw the frame
		{
			if (m_animation.getCurrentFrame()[i] == '0')
				GL::pointPos(originPos.x, originPos.y, 0, col += 0.1f, row);
			else if (m_animation.getCurrentFrame()[i] == '1')
				GL::pointPos(originPos.x, originPos.y, 0.1f, col += 0.1f, row);
			else if (m_animation.getCurrentFrame()[i] == '2')
				GL::pointPos(originPos.x, originPos.y, 0.3f, col += 0.1f, row);
			else if (m_animation.getCurrentFrame()[i] == '3')
				GL::pointPos(originPos.x, originPos.y, 0.5f, col += 0.1f, row);

			if (col >= 0.8f)
			{
				col = 0;
				row += 0.1f;
			}
		}
	}
}