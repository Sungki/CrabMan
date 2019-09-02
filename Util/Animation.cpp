#include "Animation.h"

Animation::Animation() 
	: m_currentFrame(0)
{
}

void Animation::addFrame(int num, std::string* data, sf::Time delay)		// the function for adding the frame data into the frame vector
{
	Frame newFrame;
	newFrame.frame = *data;
	newFrame.delay = delay;
	m_frame.push_back(newFrame);											//  push_back to the fram vector
}

std::string& Animation::getCurrentFrame()
{
	if (m_timer.getElapsedTime() > m_frame[m_currentFrame].delay)			// after the delay
	{
		m_currentFrame++;													// increase the number of the frame
		m_timer.restart();													// reset the timer
		if (m_currentFrame == m_frame.size())								// if the end of the frame
		{
			m_currentFrame = 0;												// reset the number of the frame
		}
	}

	return m_frame[m_currentFrame].frame;									// return the string data for the current frame
}