#pragma once

#include "SceneBase.h"
#include <SFML/Graphics.hpp>

class SceneTitle : public SceneBase
{
public:
	SceneTitle(Game& game);

	void input() override;
	void update(float dt, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Sprite m_background;
	sf::Text m_title;
	sf::Text m_pressEnter;
};

