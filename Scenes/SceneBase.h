#pragma once

#include <SFML/Graphics.hpp>

class Game;

class SceneBase
{
public:
	SceneBase(Game& game):m_Game(&game) {}

	virtual void input() = 0;
	virtual void update(float dt, sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

protected:
	Game* m_Game;
};