#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Animation
{
	struct Frame
	{
		std::string frame;
		sf::Time	delay;
	};

public:
	Animation();
	void addFrame(int num, std::string* data, sf::Time delay);
	std::string& getCurrentFrame();

private:
	std::vector<Frame> m_frame;
	sf::Clock m_timer;
	unsigned int m_currentFrame;
};