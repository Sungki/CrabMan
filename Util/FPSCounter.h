#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter
{
public:
	FPSCounter();
	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::Text m_text;

	sf::Clock m_delayTimer;
	sf::Clock m_fpsTimer;

	float m_fps = 0;
	int m_frameCount = 0;
};