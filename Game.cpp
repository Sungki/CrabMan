#include "Game.h"
#include "Display/GLFunctions.h"
#include "Util/Random.h"
#include "Scenes/SceneTitle.h"

Game::Game()
	: m_window(sf::VideoMode(WIDTH,HEIGHT), "Crab Man")
{
	m_window.setFramerateLimit(60);							// set FrameLimit as 60fps
	GL::start(WIDTH, HEIGHT);								// OpenGL setting function
	Random::init();											// init() for random function

	loadScene(std::make_unique<SceneTitle>(*this));			// The first scene is Title Scene.
}

void Game::mainLoop()
{
	sf::Clock clock;
	while (m_window.isOpen())								// Main Loop for the game
	{
		auto deltaTime = clock.restart();					// reset the delta time
		auto& scene = getCurrentScene();					// get the current Scene reference

		GL::clear();										// Opengl clear function

		scene.update(deltaTime.asSeconds(), m_window);		// update() for the current Scene
		counter.update();									// update() for FPS count

		scene.render(m_window);								// render() for the current Scene
		counter.draw(m_window);								// draw FPS count
		handleInput(scene);									// handle Event for Input

		m_window.display();									// SFML the display function for swaping the screens
	}
}

const sf::RenderWindow& Game::getWindow() const
{
	return m_window;										// SFML RenderWindow instance
}

SceneBase& Game::getCurrentScene()
{
	return *m_scene.back();									// return the reference for the current Scene
}

void Game::loadScene(std::unique_ptr<SceneBase> scene)
{
	if (!m_scene.empty())									// if Vector for the Scenes is not empty
		m_scene.pop_back();									// pop the current Scene
	m_scene.push_back(std::move(scene));					// and push the next Scene into Vector
}

void Game::handleInput(SceneBase& scene)
{
	sf::Event e;											// SFML event
	while (m_window.pollEvent(e))							// poll Events
	{
		if (e.type == sf::Event::Closed) m_window.close();													// close the window
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Escape)) m_window.close();	// close the window if ESC clicked
	}
	scene.input();											// input for the current Scene
}