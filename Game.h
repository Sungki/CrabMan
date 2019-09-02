#pragma once

// SFML library definition
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Scenes/SceneBase.h"
#include "Util/FPSCounter.h"

class Game
{
public:
	Game();
	void mainLoop();
	const sf::RenderWindow& getWindow() const;			// get Game class reference
	void loadScene(std::unique_ptr<SceneBase> scene);	// Swtich to the next Scene
	const int WIDTH = 1600, HEIGHT = 900;				// window width and height

private:
	SceneBase& getCurrentScene();						// the current loading Scene
	void handleInput(SceneBase& scene);					// get Event input
	std::vector<std::unique_ptr<SceneBase>> m_scene;	// Vector for the using Scenes

	sf::RenderWindow m_window;							// SFML window
	FPSCounter counter;									// FPS count class
};