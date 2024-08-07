#ifndef PARTICLES_H
#define PARTICLES_H

#include "sprite.h"
#include "UC_surfList.h"
#include "UC_CWave.h"

class Particle
{
public:
	
	Particle(char *textureName, int maxFrame);
	Particle(char *textureName, float speed, float startAngle, float endAngle,float x, float y, float width, float height, int density, int duration);
	void setTexture(char * textureName, int width, int height, int r, int g, int b);
	void setParticles(float speed, float startAngle, float endAngle,float x, float y, float width, float height, int density, int duration);
	bool moveParticles();
	bool isInPlay();
	int random(int min, int max);
	void cleanUp();
	void newCoordinates(float &x, float &y, float speed, float angle);
	
	static const int MAX_PARTICLES = 50;

	UC_texture *m_particle;
	Sprite *particle[MAX_PARTICLES];
	
	char *m_textureName; 
	float m_1angle;
	float m_2angle;
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	int numOfParticles;
	int m_lifeSpan;
	int m_time;
	bool playing;
	int m_maxFrame;
};

#endif