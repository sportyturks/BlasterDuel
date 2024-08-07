#include "Enemy.h"
#ifndef ENEMYAI_H
#define ENEMYAI_H

/*struct Enemy
{
	int sprite;
	int state;
	float x;
	float y;
	float direction;

};*/

class EnemyAI
{

public:
	
	Enemy *e_ship[6];
	EnemyAI();
	EnemyAI(int sprite);
	
	void InitAI();
	
	int moveShip();
	int targetNewEnemy();
	
	int random(int min, int max);
	bool enemyAlive(int newSprite);
	void targetPosition();
	void targetPosition(int x0, int x1, int y0, int y1);
	void destinReached(int x0, int x1, int y0, int y1);
	void checkDuration();

	void movingDirection();
	void calculateTarAngle();

	void setSprites(int spriteNo, float sX, float sY, float sDirection, int sState);
	void setBullets(int bulletNo, float bX, float bY, float bDirection);

/*	typedef struct
	{
		int sprite;
		float x;
		float y;
		float direction;
	} Bullets;
	
	Bullets e_bullet[12];*/

	int currentEnemyTarget;
	float m_targetAngle;
	float m_targetX;
	float m_targetY;
	
	bool rallyPoint;

	int forSprite;
	bool turnLeft;
	bool turnRight;
	bool shoot;
	bool noTarget;
	int targetDuration;
	bool UpdateTarget;


};

#endif