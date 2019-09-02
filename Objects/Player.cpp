#include "Player.h"
#include "../Objects/Component/ObjectMove.h"

Player::Player()
{
	addComponent(std::make_unique<ObjectMove>(*this));				// add the component for moving objects

	// This is the experiment for the frame in Opengl
	// the string of the height pixels
	std::string frame[4] = {};
	frame[0] = "0000000000000000110000110001100011122111012332100012210000011000";
	frame[1] = "0000000010000001010000100011110001122110112332110012210000110000";
	frame[2] = "1000000101000010001001000001100010122101012332100012210000011000";
	frame[3] = "0010010000100100000110000001100001122110012332100012210000001100";

	auto delay = sf::seconds(0.3);									// delay is 0.3sec between frames
	m_animation.addFrame(0, &frame[0], delay);
	m_animation.addFrame(1, &frame[1], delay);
	m_animation.addFrame(2, &frame[2], delay);
	m_animation.addFrame(3, &frame[3], delay);
}