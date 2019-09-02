#include "SceneTitle.h"
#include "../Display/GLFunctions.h"
#include "../Game.h"
#include "SceneLevel.h"
#include "../ResManager/ResourceHolder.h"

SceneTitle::SceneTitle(Game& game)
	: SceneBase(game)
{
	m_background.setTexture(ResourceHolder::get().texture.get("title"));		// set the image file for the background image

	m_title.setFont(ResourceHolder::get().font.get("arcade"));					// set the font
	m_title.setPosition(sf::Vector2f(m_Game->WIDTH/2 - 310, 250));				// set the position
	m_title.setOutlineColor(sf::Color::Black);									// the outline color
	m_title.setFillColor({ 255, 255, 0 });										// text color
	m_title.setOutlineThickness(2);
	m_title.setCharacterSize(150);
	m_title.setString("Crab   Man");											// the title text

	m_pressEnter.setFont(ResourceHolder::get().font.get("arcade"));
	m_pressEnter.setPosition(sf::Vector2f(m_Game->WIDTH / 2 - 300, 550));
	m_pressEnter.setOutlineColor(sf::Color::Black);
	m_pressEnter.setFillColor({ 255, 125, 125 });
	m_pressEnter.setOutlineThickness(2);
	m_pressEnter.setCharacterSize(80);
	m_pressEnter.setString("Press   the   Enter");								// the text for 'Press the enter'
}

void SceneTitle::input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))							// if pressing the enter key
	{
		m_Game->loadScene(std::make_unique<SceneLevel>(*m_Game));				// switch the Scene to the level Scene
	}
}

void SceneTitle::update(float dt, sf::RenderWindow& window)
{
}

void SceneTitle::render(sf::RenderWindow& window)
{
	window.pushGLStates();
	window.draw(m_background);													// draw the background image
	window.draw(m_title);														// draw the title text
	window.draw(m_pressEnter);													// draw the text 'Press the enter'
	window.popGLStates();
}