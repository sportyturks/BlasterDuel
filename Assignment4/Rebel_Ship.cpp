
#include "Rebel_Ship.h"
#include "UC_Dir.h"
#include <stdio.h>
#include <dsound.h>
#include "UC_UtilsV2.h"

Rebel_Ship::Rebel_Ship(int colour, int energy, float x, float y, float angle, float height, float width, float speed, int homeStation )
	: Sprite(x, y, angle, height, width, speed)
{
	m_colour = colour;
	m_energy = energy;
	m_score = 0; 
	frame = 8;
	state = 0;
	stateTime = 0;
	stateDuration = 0;
	turnLeft = false;
	turnRight = false;
	playSound = false;
	station = homeStation;
	m_x = (float) (70 + station * INTERVAL+station*7);
	bulletCheck = MAX_BLASTERS;

	for (int i= 0; i < MAX_BLASTERS; i++)
	{
		m_weapon[i] = new Weapon("enemyFire", 10, m_direction,m_x, m_y, 32, 32, 2, 100);
	}

	for (int i = 0; i < 6; i ++)
	{
		previousX[i] = -100;
		previousY[i] = -100;
	}
}

void Rebel_Ship::setTexture(char *textureName, int texWidth, int texHeight, int r, int g, int b)
{
	m_body = new UC_texture(getFileName(textureName),texWidth, texHeight, D3DCOLOR_XRGB(r, g, b));
	
	for (int i= 0; i < MAX_BLASTERS; i++)
	{
		switch (m_colour)
		{
			case 0: 
				m_weapon[i]->setTexture("redLaz.bmp", 32, 16, 0, 0, 0);
				break;
			case 1:
				m_weapon[i]->setTexture("greenLaz.bmp", 32, 16, 0, 0, 0);
				break;
			case 2:
				m_weapon[i]->setTexture("yellowLaz.bmp", 32, 16, 0, 0, 0);
				break;
			case 3:
				m_weapon[i]->setTexture("blueLaz.bmp", 32, 16, 0, 0, 0);
				break;
			case 4:
				m_weapon[i]->setTexture("purpleLaz.bmp", 32, 16, 0, 0, 0);
				break;
			case 5:
				m_weapon[i]->setTexture("yellowLaz.bmp", 32, 16, 0, 0, 0);
				break;
		}
	}
}

void Rebel_Ship::setSounds(char * soundName1, char * soundName2)
{
	launch = new UC_CWave(getFileName(soundName1));
	laser = new UC_CWave(getFileName(soundName2));
	launch->setVolume(1);
	laser->setVolume(100);
}

void Rebel_Ship::initPlayer()
{
	currentSpeed = 0;
	state = 0; // Launching state
	m_x = (float) (70 + station * INTERVAL+ 7*station); // start x which will vary across multiple players
	m_y = 750; // start y which will be the same for all players
	m_direction = 270;
	turnLeft = false;
	turnRight = false;
	frame = 8;
	m_energy = 100;

	/*for (int i= 0; i < MAX_BLASTERS; i++)
	{
		//m_weapon[i]->setWeapon("enemyFire", m_x, m_y, m_direction, 32, 16, 2, 100);
	}*/
}

void Rebel_Ship::launchPlayer()
{
	switch (stateTime)
	{
	case 0: 
			currentSpeed = 0.0;
			stateTime = stateTime + 1;
			bulletCheck = 0;
			break;
	case 1:
			if (currentSpeed < m_speed)
			{
     			currentSpeed = (float)((currentSpeed+0.02)*1.03); // launching acceleration
			}
			else
			{
				state = state + 1;
				currentSpeed = m_speed;
			}
			break;
	}
}


bool Rebel_Ship::decreaseEnery(int amount)
{
	m_energy = m_energy - amount;

	if (m_energy > 0)
		return true;
	else
		return false;
}


void Rebel_Ship::fireWeapon()
{
	bool iterate = true;
	bool goOn = false;
	int i = 0;
	
	while (iterate && (i < MAX_BLASTERS) && (bulletCheck <= MAX_BLASTERS)) //"blasters" is the Star Wars jargon for bullets
		{
			if (i == 0) 
			{
				goOn = true;
			}
			else if (i > 0)
			{
				if (((m_weapon[i-1]->fired) && (m_weapon[i-1]->m_rate >= m_weapon[i-1]->MAX_RATE)) || (!m_weapon[i-1]->fired))
					goOn = true;
				else
					goOn = false;
			}
			
			if (goOn)
			{
				if ((!m_weapon[i]->fired))
				{
						//playSound()
						//if (!playSound)
						laser->stop();
						laser->play();
						m_weapon[i]->resetWeapon(m_x+20, m_y+10, m_direction);
						m_weapon[i]->shootWeapon(m_direction);
						iterate=false;
						
						if (bulletCheck < MAX_BLASTERS )
							bulletCheck = bulletCheck +1;
				}
				else
				{
					i ++;
				}
			}
			else
			{
				i++;
			}
		}
}


void Rebel_Ship::newCoordinates()
{
	float newx=0.0;
	float newy=0.0;

	m_oldX= m_x;
	m_oldY= m_y;

	
	newx= float(currentSpeed  * (float)cos(degToRad(m_direction)));
	newy= float(currentSpeed  * (float)sin(degToRad(m_direction)));
	
	m_x = m_x + (float) newx;
	m_y = m_y + (float) newy;

	boundBox.m_x0 = (int) (m_x+m_width/4);
	boundBox.m_y0 = (int) (m_y+m_width/4);
	boundBox.m_x1 = (int) (m_x + m_width);
	boundBox.m_y1 = (int) (m_y + m_height-m_height/4);

	for (int i= 0; i < MAX_BLASTERS; i++)
	{
		if (!m_weapon[i]->fired)
		{
			m_weapon[i]->resetWeapon(m_x, m_y, m_direction);
		}
		else if (!m_weapon[i]->isInPlay())
		{
			m_weapon[i]->resetWeapon(m_x, m_y, m_direction);
			bulletCheck=  bulletCheck-1;
		}
		else
		{
			m_weapon[i]->newCoordinates();
			m_weapon[i]->m_rate++;

		}
	}
	/*for (int i = 0; i < 6; i ++)
	{
		if (i == 5)
		{
			previousX[i] = m_x;
			previousY[i] = m_y;
		}
		else
		{
			previousX[i] = previousX[i+1];
			previousY[i] = previousY[i+1];
		}
	}*/

}


void Rebel_Ship::cleanUp()
{
	laser->stop();
	delete laser;
	launch->stop();
	delete launch;
	delete m_body;
	
	for (int i = 0; i < MAX_BLASTERS; i++)
	{
		delete m_weapon[i]->m_weapon;
	}
}