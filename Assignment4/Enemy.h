#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{

public:
	int sprite;
	int state;
	float x;
	float y;
	float direction;
	
	Enemy(int spr);
};

#endif