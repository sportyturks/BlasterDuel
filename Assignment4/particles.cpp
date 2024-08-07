#include "particles.h"
#include "UC_Dir.h"
#include <stdio.h>
#include "UC_UtilsV2.h"


Particle::Particle(char *textureName, int maxFrame)
{
	m_textureName = textureName;
	playing = false;
	numOfParticles = 0;
	m_maxFrame = maxFrame;
	//setTexture(textureName, (int)16, (int)16, 0, 0, 0);

	for (int i = 0; i < numOfParticles; i++)
	{
		particle[i] = new Sprite(-100, -100, 0, 0, 0, 0);
		particle[i]->showSprite = false;
		particle[i]->s_frame = 0;
	}

	m_particle = new UC_texture(getFileName(textureName),256, 64, D3DCOLOR_XRGB(0, 0, 0));
}

Particle::Particle(char *textureName, float speed, float startAngle, float endAngle,float x, float y, float width, float height, int density, int duration)
{
	m_textureName = textureName;
	m_1angle = startAngle;
	m_2angle = endAngle;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	numOfParticles = density;
	m_lifeSpan = duration;
	m_time = 0;

	for (int i = 0; i < numOfParticles; i++)
	{
		particle[i] = new Sprite(m_x, m_y, (m_1angle + (i/numOfParticles)*(m_2angle-m_1angle)), m_height, m_width, speed);
		particle[i]->showSprite = true;
		particle[i]->s_frame = 0;
	}

	setTexture(textureName, (int)m_width, (int)m_height, 0, 0, 0);
}

void Particle::setTexture(char *textureName, int texWidth, int texHeight, int r, int g, int b)
{
	m_particle = new UC_texture(getFileName(textureName),texWidth, texHeight, D3DCOLOR_XRGB(r, g, b));
}

void Particle::cleanUp()
{	
	for (int i = 0; i < numOfParticles; i++)
	{
		delete particle[i];
	}	
}

void Particle::setParticles(float speed, float startAngle, float endAngle,float x, float y, float width, float height, int density, int duration)
{
	float tempAngle= 0.0;
	float tempSpeed= 0.0;

	m_1angle = startAngle;
	m_2angle = endAngle;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	numOfParticles = density;
	m_lifeSpan = duration;
	m_time = 0;
	playing = true;
	
	for (int i = 0; i < numOfParticles; i++)
	{
		//tempAngle = (float) (m_1angle + ((float)i/(float)numOfParticles)*(m_2angle-m_1angle));
		tempAngle = (float) (random((int)m_1angle,(int)m_2angle));
		tempSpeed = (float) (random((int)1,(int)speed));
		particle[i] = new Sprite(m_x, m_y, tempAngle, m_height, m_width, tempSpeed);
		particle[i]->showSprite = true;
		particle[i]->s_frame = 0;
	}
	
}

bool Particle::moveParticles()
{
	if (m_lifeSpan <= m_time)
	{
		for (int i = 0; i < numOfParticles; i++)
		{
			particle[i]->showSprite = false;
		}
		return false;
	}
	else
	{
		for (int i = 0; i < numOfParticles; i++)
		{
			if (particle[i]->m_width < 2)
			{
				m_time = m_lifeSpan;
			}
			else
			{
				newCoordinates(particle[i]->m_x, particle[i]->m_y, particle[i]->m_speed, particle[i]->m_direction);
				particle[i]->m_height= particle[i]->m_height * (float)(1.0 - ((float)m_time/(float)m_lifeSpan));
				particle[i]->m_width= particle[i]->m_width * (float)(1.0 - ((float)m_time/(float)m_lifeSpan));
				m_time ++;
			}
		}
	}

	return true;
}

bool Particle::isInPlay()
{
	return ((m_x > 0) && (m_x < 1024) && (m_y > 0) && (m_y < 700));
}


int Particle::random(int min, int max)
{
	return (rand()%(max-min)+min);
}

void Particle::newCoordinates(float &x, float &y, float speed, float angle)
{
		float newx=0.0;
		float newy=0.0;
		newx= float(speed  * (float)cos(degToRad(angle)));
		newy= float(speed  * (float)sin(degToRad(angle)));
		x = x + (float) newx;
		y = y + (float) newy;
}