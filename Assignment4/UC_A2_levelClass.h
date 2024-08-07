#ifndef UC_A2_Level
#define UC_A2_Level
// UC_A2_levelClass

#include "UC_gameClass.h"

class UC_A2_LevelClass : public UC_GameClass
{
private:


protected:
virtual void init()=0;
virtual void cleanUp()=0;
virtual void keyhit(WPARAM wParam);
virtual void render()=0;

virtual void timerTick();

virtual char *levelName();
virtual char *StudentNames();
virtual char *StudentIDs();
virtual bool put_in_class_game()=0; // return true to be included in class game
virtual void help(); // render help screen

public:
virtual int getHowhard(); // 0=easy 1= medium 2=hard
void setScoreAndEndLevel(int s); // score that the player got 0 to 100

UC_A2_LevelClass(); // constructor
};




#endif