// game code for assigment 4

#include "UC_main.h"
#include "UC_Dir.h"
#include "UC_UtilsV2.h"
#include "UC_A2_gameCode.h"
#include "UC_A2_states.h"

#include "myclass.h"

#define TIMER_MS 50

// define any new globals needed
StateEngine_class *st;

UC_GameClass *state1;//Introduction
UC_GameClass *state2;//Main Menu
UC_GameClass *state3;//Settings
UC_GameClass *state4;//Player Selection
UC_GameClass *state5;//Play 
UC_GameClass *state6;//Round Winner
UC_GameClass *state7;//League winner
UC_GameClass *state8;//Debug


// -------------------------------------------------------------
void GameCode::init()
{
	texl=new UC_texture_list();
	loadStockTextures();
	UC_UtilsCreateFonts(g_pDirect3DDevice);
	st=new StateEngine_class();

	state1 = new state1_class();
	state2 = new state2_class();
	state3 = new state3_class();
	state4 = new state4_class();
	state5 = new state5_class();
	state6 = new state6_class();
	state7 = new state7_class();
	state8 = new state8_class();

	//gameScore=0;

	st->transitTo(1);
	UC_renderON(); // allow rendering
}

void GameCode::cleanUp()
{
UC_UtilsDeleteFonts();
if (texl != NULL) delete texl;
if (st->getCurrentGC() != NULL) st->getCurrentGC()->cleanUp();
st->setCurrentGC(NULL);
delete st;
st=NULL;
}

void GameCode::loadStockTextures()
{
}

UC_texture *GameCode::getStockTexture(int i)
{
	return texl->getUC_Texture(i);
}

void GameCode::keyhit(WPARAM wParam)
{
	if (st->getCurrentGC() != NULL) st->getCurrentGC()->keyhit(wParam);
	
}


//////////////////////////////////////////////////////
// Render()
//////////////////////////////////////////////////////
void GameCode::render()
{
if (st->getCurrentGC() != NULL) st->getCurrentGC()->render();
}


void GameCode::timerTick()
{
	if (st->getCurrentGC() != NULL) st->getCurrentGC()->timerTick();
}

GameCode::GameCode()
{
}

GameCode::~GameCode()
{
}

// ----- define state engine class below ------------------------

/*
int prev_state;
UC_GameClass *prev_currentGC;
int state;
UC_GameClass *currentGC;
*/

int StateEngine_class::getState()
{
	return state;
}

void StateEngine_class::transitTo(int newstate)
{
UC_GameClass *temp;
if (newstate==state) return;

UC_renderOFF();

temp=NULL;
if (newstate == 1) temp = state1;
if (newstate == 2) temp = state2;
if (newstate == 3) temp = state3;
if (newstate == 4) temp = state4;
if (newstate == 5) temp = state5;
if (newstate == 6) temp = state6;
if (newstate == 7) temp = state7;
if (newstate == 8) temp = state8;

prev_state = state; // dont realy need it but it might be handy for future expansion
prev_currentGC = currentGC; // dont realy need it but it might be handy for future expansion

if (state != 0) 
	{
	if (currentGC!=NULL) currentGC->cleanUp();
	}

currentGC=temp;
state=newstate;

if (state != 8)
	{
	if (currentGC!=NULL) currentGC->init();
	}
UC_renderON();
}

void StateEngine_class::transitFromDebug()
{
state=prev_state;
currentGC=prev_currentGC;
}

void StateEngine_class::transitToDebug()
{
prev_state = state;
prev_currentGC = currentGC;
state = 6;
currentGC = state6;
}


UC_GameClass *StateEngine_class::getCurrentGC()
{
	return currentGC;
}

void StateEngine_class::setCurrentGC(UC_GameClass *c)
{
currentGC=c;
}

StateEngine_class::StateEngine_class()
{
	state=0;
	currentGC=NULL;
}

StateEngine_class::~StateEngine_class()
{
}
myButton::myButton(UC_GUIControl *parent)
:UC_GUIButton(parent)
{
}
void myButton::pressed()
{
	if (st->getState() == 2)
		((state2_class *) state2)->doIt();
	else if (st->getState() == 3)
		((state3_class *) state3)->doIt();
	else if (st->getState() == 4)
		((state4_class *) state4)->doIt();
	else if (st->getState() == 6)
		((state6_class *) state6)->doIt();
	else if (st->getState() == 7)
		((state7_class *) state7)->doIt();
}

// end