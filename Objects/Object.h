#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Component/ComponentBase.h"
#include "../Util/Animation.h"

class Object
{
public:
	Object();

	void update(float dt);
	virtual void draw();
	void addComponent(std::unique_ptr<ComponentBase> com);

	sf::Vector2i pos;
	sf::Vector2f originPos;

	float moving;
	float speed;
	int objectStep;
	int playerLife;
	int score;
	bool isPowerUp;

protected:
	Animation m_animation;

private:
	std::vector<std::unique_ptr<ComponentBase>> m_components;
};