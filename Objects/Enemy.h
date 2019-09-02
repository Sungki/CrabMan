#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
	Enemy(Object& player);

	void draw() override;

private:
	float m_eyeSize;
};
