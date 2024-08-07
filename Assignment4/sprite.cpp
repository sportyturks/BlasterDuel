
#include "sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(float x, float y, float angle, float height, float width, float speed)
{
	m_x = x;
	m_y = y;
	m_height = height;
	m_width = width;
	m_oldX = 0;
	m_oldY = 0;
	s_frame = 0;
	m_direction = angle;
	m_speed = speed;
}

float Sprite::getX()
{
	return m_x;
}


float Sprite::getY()
{
	return m_y;
}

void Sprite::setX(float x)
{
	m_x = x;
}


void Sprite::setY(float y)
{
	m_y = y;
}

float Sprite::getSpeed()
{
	return m_speed;
}

void Sprite::setSpeed(float speed)
{
	m_speed = speed;
}