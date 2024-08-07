#ifndef z88888_zzz
#define z88888_zzz
// sample level in assignment 2

#include "UC_gameClass.h"
#include "UC_surfList.h"
#include "UC_A2_LevelClass.h"
#include "UC_CWave.h"
#include "Rebel_Ship.h"
#include "sprite.h"
#include "particles.h"
#include "EnemyAI.h"


class u888888_class : public UC_A2_LevelClass
{
private:
	HRESULT rc;

public:

	static const int numShips = 6;
	static const int numStars = 60;
	UC_texture *background;
	UC_texture *bang;
	UC_texture *shield;
	UC_texture *exhaust;
	UC_texture *helpTex;
	int pilotWinner;
	bool showWinner;
	bool helpScreen;
	
	UC_CWave * explosion2;
	UC_CWave * endLaugh;
    
	Rebel_Ship *player[numShips];
	EnemyAI *computer[numShips];
	Sprite *s_explosions[numShips];
	Particle *m_particles[numShips];
	Particle *m_particles2[numShips];
	Particle *m_particles3[numShips];
	Sprite *backStars[numStars];
	bool polling, pollFinished, endRound, endLeague;
	int endCount;

	bool player1;
	bool player2;
	bool player3;
	bool player4;

	//int score;
	int timerCount;
	//UC_CWave *sound1;
	
	typedef struct
	{
		int m_x0;
		int m_y0;
		int m_x1;
		int m_y1;
	} box;

virtual void init();
virtual void cleanUp();
virtual void keyhit(WPARAM wParam);
virtual void render();

virtual void timerTick();

void setPlayer(int i);
void processKeys();
void drawBackground();
int random(int min, int max);
void moveSprites();
bool collision(int m_x0, int m_x1, int m_y0, int m_y1, int m_x2, int m_x3, int m_y2, int m_y3);
void performCollision();
void pollPosition();
void updateResults();
void freezePlay();

virtual char *levelName();
virtual char *StudentNames();
virtual char *StudentIDs();
virtual bool put_in_class_game(); // return true to be included in class game
virtual void help(); // render help screen
};


// end
#endif