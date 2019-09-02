#include "SceneLevel.h"
#include "../Game.h"
#include "../Level.h"
#include "../Util/File.h"
#include "../Objects/Enemy.h"
#include "../Display/GLFunctions.h"
#include "../Scenes/SceneTitle.h"
#include "../ResManager/ResourceHolder.h"

SceneLevel::SceneLevel(Game& game)
	: SceneBase(game), m_timer(0)
{
	File f("./Resource/level1.txt");											// open the file for the level
	Level::get().init(f.getData(), f.getSize());								// init on the level

	m_background.setTexture(ResourceHolder::get().texture.get("level"));		// set the background image
	m_playerLives.setTexture(ResourceHolder::get().texture.get("player"));		// set the image for the player life 

	m_text.setFont(ResourceHolder::get().font.get("arcade"));
	m_text.setPosition(sf::Vector2f(m_Game->WIDTH/2 - 350, 300));
	m_text.setOutlineColor(sf::Color::Black);									// text color
	m_text.setFillColor({ 255, 75, 50 });
	m_text.setOutlineThickness(2);
	m_text.setCharacterSize(150);												// set the size of texts

	m_scoreText.setFont(ResourceHolder::get().font.get("arcade"));
	m_scoreText.setPosition(sf::Vector2f(m_Game->WIDTH/2 - 70, 0));
	m_scoreText.setOutlineColor(sf::Color::Black);
	m_scoreText.setFillColor({ 255, 255, 255 });								// text color
	m_scoreText.setOutlineThickness(2);
	m_scoreText.setCharacterSize(35);

	for (int i = 0; i < MAX_ENEMIES; i++)
		m_enemies.push_back(std::make_unique<Enemy>(m_player));					// make the vector for the enemy with Max number

	auto curr = m_enemies.begin();
	for (int y = 0; y < Level::get().m_height; ++y)
		for (int x = 0; x < Level::get().m_width; ++x)
		{
			if (Level::get().m_level(x, y) == Level::get().PLAYER)				// set the player position on the level
			{
				m_player.pos.x = x;
				m_player.pos.y = y;
				m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);
			}
			if (Level::get().m_level(x, y) == Level::get().ENEMY)
			{
				if (curr < m_enemies.end())										// if the current enemy is not the end of the enemies
				{
					curr->get()->pos.x = x;										// set the enemies position
					curr->get()->pos.y = y;
					curr->get()->originPos = static_cast<sf::Vector2f>(curr->get()->pos);
				}
				curr++;
			}
		}
}

void SceneLevel::reStart()														// Restart if the player die
{
	m_timer = 0;																// reset all data
	m_player.objectStep = 0;
	m_player.speed = 0;
	m_player.isPowerUp = false;

	m_player.pos.x = 8;															// back to the start position
	m_player.pos.y = 15;
	m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);

	m_enemies.clear();
	for (int i = 0; i < MAX_ENEMIES; i++)
		m_enemies.push_back(std::make_unique<Enemy>(m_player));

	int enemyPos = 8;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		m_enemies[i]->pos.x = enemyPos++;										// back to the start position
		m_enemies[i]->pos.y = 9;
		m_enemies[i]->originPos = static_cast<sf::Vector2f>(m_enemies[i]->pos);
	}
}

void SceneLevel::input()
{
	if (m_player.objectStep ==0)												// if the player is normal
	{
		if (m_player.moving == 0)												// if not moving for the player
		{
			// checking the pressing key and walls
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Level::get().m_level(m_player.pos.x - 1, m_player.pos.y) != Level::get().WALL)
			{
				m_player.moving = 0.1f;											// start the moving for the player
				m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);
				Level::get().setPos(m_player.pos.x, m_player.pos.y, Level::get().SPACE);	// reset the space

				if (Level::get().m_level(m_player.pos.x - 1, m_player.pos.y) == Level::get().COOKIE) m_player.score+=10; // if having the cookies
				else if (Level::get().m_level(m_player.pos.x - 1, m_player.pos.y) == Level::get().POWERUP)				// if having the powerup
				{
					for (int i = 0; i < m_enemies.size(); i++)					// change the enemies status to the power up
					{
						m_enemies[i]->isPowerUp = true;
					}
				}

				Level::get().setPos(--m_player.pos.x, m_player.pos.y, Level::get().PLAYER);		// set the position for the player
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Level::get().m_level(m_player.pos.x + 1, m_player.pos.y) != Level::get().WALL)
			{
				m_player.moving = -0.1f;
				m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);
				Level::get().setPos(m_player.pos.x, m_player.pos.y, Level::get().SPACE);

				if (Level::get().m_level(m_player.pos.x + 1, m_player.pos.y) == Level::get().COOKIE) m_player.score += 10;
				else if (Level::get().m_level(m_player.pos.x + 1, m_player.pos.y) == Level::get().POWERUP)
				{
					for (int i = 0; i < m_enemies.size(); i++)
					{
						m_enemies[i]->isPowerUp = true;
					}
				}

				Level::get().setPos(++m_player.pos.x, m_player.pos.y, Level::get().PLAYER);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Level::get().m_level(m_player.pos.x, m_player.pos.y - 1) != Level::get().WALL)
			{
				m_player.moving = 0.1f;
				m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);
				Level::get().setPos(m_player.pos.x, m_player.pos.y, Level::get().SPACE);

				if (Level::get().m_level(m_player.pos.x, m_player.pos.y-1) == Level::get().COOKIE) m_player.score += 10;
				else if (Level::get().m_level(m_player.pos.x, m_player.pos.y-1) == Level::get().POWERUP)
				{
					for (int i = 0; i < m_enemies.size(); i++)
					{
						m_enemies[i]->isPowerUp = true;
					}
				}

				Level::get().setPos(m_player.pos.x, --m_player.pos.y, Level::get().PLAYER);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Level::get().m_level(m_player.pos.x, m_player.pos.y + 1) != Level::get().WALL)
			{
				m_player.moving = -0.1f;
				m_player.originPos = static_cast<sf::Vector2f>(m_player.pos);
				Level::get().setPos(m_player.pos.x, m_player.pos.y, Level::get().SPACE);

				if (Level::get().m_level(m_player.pos.x, m_player.pos.y + 1) == Level::get().COOKIE) m_player.score += 10;
				else if (Level::get().m_level(m_player.pos.x, m_player.pos.y + 1) == Level::get().POWERUP)
				{
					for (int i = 0; i < m_enemies.size(); i++)
					{
						m_enemies[i]->isPowerUp = true;
					}
				}

				Level::get().setPos(m_player.pos.x, ++m_player.pos.y, Level::get().PLAYER);
			}
		}
	}
	else if (m_player.objectStep == 2)										// after finishing the explosion
	{
		m_timer++;
		if (m_timer > 60)
		{
			m_player.playerLife--;
			if (m_player.playerLife > 0)
			{
				reStart();													// re-start
			}
			else
				m_Game->loadScene(std::make_unique<SceneTitle>(*m_Game));	// if no life, go to the title Scene
		}

	}
}

void SceneLevel::update(float dt, sf::RenderWindow& window)
{
	if (m_player.objectStep != 2)											// if the player is not dead
	{
		m_player.update(dt);													// excute update() for all objects
		for (auto& obj : m_enemies) obj->update(dt);
	}
}

void SceneLevel::render(sf::RenderWindow& window)
{
	window.pushGLStates();
		window.draw(m_background);
		for (int i = 0; i < m_player.playerLife; ++i)
		{
			m_playerLives.setPosition(sf::Vector2f(50 * i, 80));			// set the position for the player life image
			window.draw(m_playerLives);
		}
	window.popGLStates();

	GL::createWalls();														// draw the walls
	m_player.draw();														// draw the player
	for (auto& obj : m_enemies) obj->draw();								// draw the enemies

	window.pushGLStates();
		m_scoreText.setString("SCORE     " + std::to_string((int)m_player.score));	// score text
		window.draw(m_scoreText);
		if (m_player.objectStep == 2)										// if the player is dead
		{
			if (m_player.playerLife > 1) m_text.setString("Try   again!!");	// if having the life, try again
			else m_text.setString("Game   Over!!");							// if not, game over
			window.draw(m_text);
		}
	window.popGLStates();
}