#ifndef WEAPON_H
#define WEAPON_H

#include "sprite.h"
#include "UC_surfList.h"
#include "UC_CWave.h"

class Weapon: public Sprite
{
public:
	Weapon(char *weaponName, float speed, float angle, float x, float y, float width, float height, float rate, int accuracy);
	
	void setTexture(char * textureName, float width, float height, int r, int g, int b);
	void setWeapon(char *name, float x, float y, float angle, float height, float width, int rate, float accuracy);
	void resetWeapon(float x, float y, float angle);
	void shootWeapon(float angle);
	bool isInPlay();
	
	void newCoordinates();
	
	UC_texture *m_weapon;
	
	static const int MAX_RATE = 20;

	char * m_weaponName;
	int m_rate;
	int m_accuracy;
	int frame;
	float currentSpeed;
	bool fired;
	
};

#endif