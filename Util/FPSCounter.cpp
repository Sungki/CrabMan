#include "FPSCounter.h"
#include "../ResManager/ResourceHolder.h"

FPSCounter::FPSCounter()
{
	m_text.setFont(ResourceHolder::get().font.get("arcade"));				// set the font for the text
	m_text.setOutlineColor(sf::Color::Black);								// set the color as Black
	m_text.setFillColor({ 255, 255, 255 });									// text color
	m_text.setOutlineThickness(2);											// set the outline for texts
	m_text.setCharacterSize(25);											// text size
}

void FPSCounter::update()
{
	m_frameCount++;
	if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
		m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();			// calculate the FPS number
		m_frameCount = 0;													// reset the fps number
		m_delayTimer.restart();												// restart the delay timer
	}
}

void FPSCounter::draw(sf::RenderWindow& window)
{
	m_text.setString("FPS  " + std::to_string((int)m_fps));
	window.pushGLStates();
	window.draw(m_text);													// draw the text on the screen
	window.popGLStates();
}