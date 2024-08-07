#ifndef gameCode_Z11
#define gameCode_Z11
// include file for the main program

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>
#include "UC_gui.h"

#include "UC_gameClass.h"
#include "UC_surfList.h"

class myButton : public UC_GUIButton
{
	public:
		myButton(UC_GUIControl *parent);
		virtual void pressed();
};
class StateEngine_class
{
private:
int prev_state;
UC_GameClass *prev_currentGC;
int state;
UC_GameClass *currentGC;

public:
int getState();
UC_GameClass *getCurrentGC();
void setCurrentGC(UC_GameClass *c);
void transitTo(int newstate);
void transitFromDebug();
void transitToDebug();
// 0 = Just run
// 1 = splash screen
// 2 = selection screen
// 3 = playing level
// 4 = ending
// 5 = help for level
// 6 = debug
// 7 = ending no more renders
StateEngine_class();
~StateEngine_class();
};



class GameCode : public UC_GameClass
{
public:

void render();
void init();
void cleanUp();
void keyhit(WPARAM wParam);
void timerTick();

void loadStockTextures();
UC_texture *getStockTexture(int i);
UC_texture_list *texl;

GameCode();
~GameCode();
};

// globals 

extern StateEngine_class *st;

extern UC_GameClass *state1;
extern UC_GameClass *state2;
extern UC_GameClass *state3;
extern UC_GameClass *state4;
extern UC_GameClass *state5;
extern UC_GameClass *state6; 
extern UC_GameClass *state7;
extern UC_GameClass *state8;// debug

// end
#endif
