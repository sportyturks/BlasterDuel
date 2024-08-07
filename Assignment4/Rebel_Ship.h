#ifndef REBEL_SHIP_H
#define REBEL_SHIP_H

#include "sprite.h"
#include "UC_surfList.h"
#include "CWave.h"
#include "UC_CWave.h"
#include "weapon.h"

class Rebel_Ship: public Sprite
{
public:
	Rebel_Ship(int colour, int energy, float x, float y, float angle, float height, float width, float speed, int homeStation);
	void setTexture(char * textureName, int width, int height, int r, int g, int b);
	void setSounds(char * soundName1, char * soundName2);
	void initPlayer();
	bool decreaseEnery(int amount);
	void fireWeapon();
	void launchPlayer();
	void newCoordinates();
	void cleanUp();

	static const int INTERVAL = 155;
	static const int MAX_BLASTERS= 2;
	
	UC_texture *m_body;
	Weapon *m_weapon[MAX_BLASTERS];
	UC_CWave *launch;
	UC_CWave *laser;

	int m_energy;
	int frame;
	float currentSpeed;

	int state; // which sate? 0 = lanching, 1 = inAir, 2 = died 
	int stateTime; // elapsed duration 
	int stateDuration; // max duration

	int station;
	int m_colour;
	int m_score;

	int previousX[6];
	int previousY[6];
	
	int bulletCheck;
	bool turnLeft;
	bool playSound;
	bool turnRight;
	
private:
	
};
# endif
