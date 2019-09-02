#include "ResourceHolder.h"

ResourceHolder::ResourceHolder()
	: texture("Resource/Texture/", "jpg"), font("Resource/Font/", "ttf")			// set the image and font file
{
}

ResourceHolder& ResourceHolder::get()
{
	static ResourceHolder res;
	return res;
}

const sf::Texture& ResourceHolder::getTexture(const std::string& name)
{
	return get().texture.get(name);
}

const sf::Font& ResourceHolder::getFont(const std::string& name)
{
	return get().font.get(name);
}