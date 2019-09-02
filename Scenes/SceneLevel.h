#pragma once

#include "SceneBase.h"
#include "../Objects/Player.h"

#define MAX_ENEMIES 4

class SceneLevel : public SceneBase
{
public:
	SceneLevel(Game& game);

	void input() override;
	void update(float dt, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;

private:
	Player m_player;

	sf::Sprite m_background;
	sf::Sprite m_playerLives;
	sf::Text m_text;
	sf::Text m_scoreText;
	int m_timer;

	std::vector<std::unique_ptr<Object>> m_enemies;

	void reStart();
};