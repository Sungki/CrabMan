#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class ResourceHolder
{
public:
	static ResourceHolder& get();
	static const sf::Texture& getTexture(const std::string& name);
	static const sf::Font& getFont(const std::string& name);

	ResourceManager<sf::Texture> texture;
	ResourceManager<sf::Font> font;

private:
	ResourceHolder();
};