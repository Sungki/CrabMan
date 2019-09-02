#include "Enemy.h"
#include "../Objects/Component/ObjectMove.h"
#include "../Objects/Component/EnemyAI.h"
#include "../Display/GLFunctions.h"

Enemy::Enemy(Object& player)
	: m_eyeSize(1)
{
	addComponent(std::make_unique<ObjectMove>(*this));							// add the component for moving objects
	addComponent(std::make_unique<EnemyAI>(*this, player));

	// This is the experiment for the frame in Opengl
	// the string of the height pixels
	std::string frame[4] = {};
	frame[0] = "0001100000122100012332101112211100011000110000110000000000000000";
	frame[1] = "0011000000122100112332110112211000111100010000101000000100000000";
	frame[2] = "0001100000122100012332101012210100011000001001000100001010000001";
	frame[3] = "0000110000122100012332100112211000011000000110000010010000100100";

	auto delay = sf::seconds(0.3);												// delay is 0.3sec between frames
	m_animation.addFrame(0, &frame[0], delay);
	m_animation.addFrame(1, &frame[1], delay);
	m_animation.addFrame(2, &frame[2], delay);
	m_animation.addFrame(3, &frame[3], delay);
}

void Enemy::draw()
{
	Object::draw();																// excute the parent class draw for the animation

	if (isPowerUp)
	{
		GL::enemyEye(originPos.x, originPos.y, sf::Color::Red, m_eyeSize++);	// draw the red eyes
		if (m_eyeSize >= 25) m_eyeSize = 1;
	}
	else
		GL::enemyEye(originPos.x, originPos.y, sf::Color::Cyan, 15);			// draw the cyan eyes
}