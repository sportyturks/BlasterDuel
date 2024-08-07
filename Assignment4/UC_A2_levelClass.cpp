//UC_A2_levelClass.cpp

#include "UC_A2_levelClass.h"
#include "UC_main.h"
#include "UC_gameClass.h"
#include "UC_A2_gameCode.h"

char *UC_A2_LevelClass::levelName()
{
return "Unnamed level subtract 5 marks";
}

char *UC_A2_LevelClass::StudentNames()
{
return "No Name Provided";
}

char *UC_A2_LevelClass::StudentIDs()
{
	return "No Id's Provided";
}

void UC_A2_LevelClass::help()
// render help screen
{
}

void UC_A2_LevelClass::timerTick()
{
}

void UC_A2_LevelClass::keyhit(WPARAM wParam)
{
}

int UC_A2_LevelClass::getHowhard()
{
	// 0=easy 1= medium 2=hard
	return -1;
}

void UC_A2_LevelClass::setScoreAndEndLevel(int s)
{
//gameScore=gameScore+s;
st->transitTo(4);
}


UC_A2_LevelClass::UC_A2_LevelClass() // constructor
{
//howHard = 1;
}

// end