
#include "EnemyAI.h"
#include <math.h>
#include <stdio.h>
#include "UC_UtilsV2.h"


EnemyAI::EnemyAI()
{

}

EnemyAI::EnemyAI(int newSprite)
{
	for (int i = 0; i < 6; i++)
	{
		e_ship[i] = new Enemy(i);
	}

	currentEnemyTarget= -1;
	m_targetAngle= -1.0;
	m_targetX= -1.0;
	m_targetY= -1.0;

	
	rallyPoint =false;

	forSprite= newSprite;
	turnLeft= false;
	turnRight= false;
	shoot= false;
	noTarget = true;
	UpdateTarget = true;
	targetDuration = 2;
}

void EnemyAI::InitAI()
{
	currentEnemyTarget= -1;
	m_targetAngle= -1.0;
	m_targetX= -1.0;
	m_targetY= -1.0;
	
	rallyPoint =false;

	turnLeft= false;
	turnRight= false;
	shoot= false;
	noTarget = true;
	UpdateTarget = true;
}

int EnemyAI::random(int min, int max)
{
	return (rand()%(max-min)+min);
}

bool EnemyAI::enemyAlive(int sprite)
{
	return (e_ship[sprite]->state == 1);
}

void EnemyAI::targetPosition()
{
	m_targetX = (float) (random(0, 1024));
	m_targetY = (float) (random(200,600));
}

void EnemyAI::targetPosition(int x0, int x1, int y0, int y1)
{
	m_targetX = (float) (random(x0, x1));
	m_targetY = (float) (random(y0,y1));
}

void EnemyAI::destinReached(int x0, int x1, int y0, int y1)
{
	if ((m_targetX >= x0) && (m_targetX <= x1) && (m_targetY >= y0) && (m_targetY <= y1))
	{
		InitAI();
		rallyPoint = true;
		targetPosition();
	}
}

void EnemyAI::checkDuration()
{
	if (targetDuration > 0)
	{
		targetDuration --;
	}
	else
	{
		UpdateTarget = true;
	}	
}

int EnemyAI::targetNewEnemy()
{
	float dist= -1.0;
	int targetedSprite = -1;
	float shortestDist = -1.0;
	int m_rand = rand();

	if (m_rand%3 ==0 || m_rand%3 ==2)
	{
		targetDuration = 30;
		for (int i = 0; i < 6; i++)
		{
			if (i != forSprite)
			{
				if (enemyAlive(i))
				{
					dist= sqrt((e_ship[i]->x-e_ship[forSprite]->x)*(e_ship[i]->x-e_ship[forSprite]->x)+(e_ship[i]->y-e_ship[forSprite]->y)*(e_ship[i]->y-e_ship[forSprite]->y));
					
					if (dist < shortestDist)
					{
						shortestDist = dist;
						targetedSprite = i;
					}
					else
					{
						if (shortestDist == -1.0)
						{
							shortestDist= dist;
							targetedSprite = i;
						}
					}
				}
			}
		}
	}
	else if (m_rand%3 ==1)
	{
		targetDuration = 30;
		targetedSprite = -1;
	}

		return targetedSprite;
}


int EnemyAI::moveShip()
{
	if (noTarget || UpdateTarget )
	{
	//find a target--> enemy or way point
		int i = targetNewEnemy();
		
		if (i > -1)
		{
			currentEnemyTarget = i;
			rallyPoint = false;
		}
		else
		{
			rallyPoint = true;
			targetPosition();
		}	

		UpdateTarget = false;
		noTarget = false;
	}
	
	if (!rallyPoint)
	{
		if (enemyAlive(currentEnemyTarget))
		{
			if (e_ship[forSprite]->y < 50.0)
			{
				InitAI();
				rallyPoint = true;
				targetPosition((int) (e_ship[forSprite]->x - 300), (int) (e_ship[forSprite]->x + 300), 300, 500);
			}
			else if (e_ship[forSprite]->y > 550.0)
			{
				InitAI();
				rallyPoint = true;
				targetPosition((int) (e_ship[forSprite]->x - 300), (int) (e_ship[forSprite]->x + 300), 200, 400);
			}
			else
			{
				m_targetX = (float) (e_ship[currentEnemyTarget]->x);
				m_targetY = (float) (e_ship[currentEnemyTarget]->y);
			}
		}
		else
		{
			InitAI();
			rallyPoint = true;
			targetPosition();
		}
	}
//find out the required angle if sufficient an amount of time has passed
//work it out given your current position and the angle required to get there

	if (!noTarget)
	{
		calculateTarAngle();

//Adjust the ship so that it moves towards the preffered angle
//return the direction in which the ship will move
	
		movingDirection();
	
	}

	if (turnLeft) return 0;
	else if (turnRight) return 1;
	else return -1;
}

void EnemyAI::movingDirection()
{
//special Case
	float adjustment = 0.0;
	
	e_ship[forSprite]->direction = (float)((int)(e_ship[forSprite]->direction)%360);
	m_targetAngle = (float)(((int)m_targetAngle)%360);


	if ((e_ship[forSprite]->direction < 180) && 
		(m_targetAngle>= (180 + e_ship[forSprite]->direction)))
	{
			adjustment = 360;
	}
	else if ((e_ship[forSprite]->direction >= (180+ m_targetAngle)) && 
		(m_targetAngle< 180))
	{
			adjustment = -360;
	}

// Normal Case

	if ((e_ship[forSprite]->direction - m_targetAngle + adjustment) > 50.0)
	{
			turnLeft = true;
			shoot = false;
	}
	else if ((e_ship[forSprite]->direction - m_targetAngle + adjustment)< -50.0)
	{
			turnRight = true;
			shoot = false;
	}
	else
	{
		turnLeft = false;
		turnRight = false;
		
		if (!rallyPoint)
			shoot = true;
	}
}

void EnemyAI::calculateTarAngle()
{
	float newX = m_targetX - e_ship[forSprite]->x;
	float newY = m_targetY - e_ship[forSprite]->y;
	float tAngle= 0.0;
	tAngle = (float)((atan(newY/newX))*(180.0/3.14159)); 

	if (newX > 0 && newY > 0)
	{
		tAngle = (float) (tAngle + 0.0);
	}
	else if (newX < 0 && newY > 0)
	{
		tAngle = (float) (tAngle + 180.0);
	}
	else if (newX > 0 && newY < 0)
	{
		tAngle = (float) (tAngle + 360.0);
	}
	else if (newX < 0 && newY < 0)
	{
      tAngle = (float) (tAngle + 180.0);
	}

	if (!((abs((int)(tAngle-m_targetAngle))) < 5))
		m_targetAngle = tAngle;
}

void EnemyAI::setSprites(int spriteNo, float sX, float sY, float sDirection, int sState)
{
	if (spriteNo < 6)
	{
			e_ship[spriteNo]->x = (float)(sX);
			e_ship[spriteNo]->y = (float)(sY);
			e_ship[spriteNo]->direction = (float)(sDirection);
			e_ship[spriteNo]->state = (int)(sState);
	}
}

void EnemyAI::setBullets(int bulletNo, float bX, float bY, float bDirection)
{
	if (bulletNo < 12)
	{
	/*	e_bullet[bulletNo].x = bX;
		e_bullet[bulletNo].y = bY;
		e_bullet[bulletNo].direction = bDirection;*/
	}
}