#include "weapon.h"
#include "UC_Dir.h"
#include <stdio.h>
#include "UC_UtilsV2.h"


Weapon::Weapon(char *weaponName, float speed, float angle, float x, float y, float width, float height, float rate, int accuracy)
: Sprite(x, y, angle, height, width, speed)
{
	setWeapon(weaponName, x, y, angle, height, width, (int) rate, (float) accuracy);
}

void Weapon::setTexture(char *textureName, float texWidth, float texHeight, int r, int g, int b)
{
	m_weapon = new UC_texture(getFileName(textureName),(int) texWidth, (int) texHeight, D3DCOLOR_XRGB(r, g, b), 255);
}

void Weapon::setWeapon(char *name, float x, float y, float angle, float height, float width, int rate, float accuracy)
{
	m_weaponName = name;
	m_x= x;
	m_y= y;
	m_direction = angle;
	m_height= height;
	m_width= width;
	m_rate = rate;
	m_accuracy= (int)accuracy;
	fired = false;
}

void Weapon::resetWeapon(float x, float y, float angle)
{
	m_x= x;
	m_y= y;
	m_direction = angle;
	m_speed = 0.0;
	m_rate = 0;
	fired = false;
}

void Weapon::shootWeapon(float angle)
{
	m_direction = angle;
	m_speed = 15.0;
	m_rate = 0;
	fired = true;
} 

bool Weapon::isInPlay()
{
	return ((m_x > 0) && (m_x < 1024) && (m_y > 0) && (m_y < 700));
}

void Weapon::newCoordinates()
{
		float newx=0.0;
		float newy=0.0;
		newx= float(m_speed  * (float)cos(degToRad(m_direction)));
		newy= float(m_speed  * (float)sin(degToRad(m_direction)));
		m_x = m_x + (float) newx;
		m_y = m_y + (float) newy;

		boundBox.m_x0 = (int) m_x;
		boundBox.m_y0 = (int) m_y;
		boundBox.m_x1 = (int) m_x + 32;
		boundBox.m_y1 = (int) m_y + 16; 
}