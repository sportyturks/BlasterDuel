#ifndef UC_STATES
#define UC_STATES

#include "UC_gameClass.h"
#include "UC_surface.h"
#include "UC_A2_gameCode.h"
#include "myClass.h"
#include "UC_gui.h"

class state1_class : public UC_GameClass
{
	bool boolState1a, boolState1b;
	UC_texture *texState1a;
	UC_texture *texState1b;
	UC_texture *texState1c;

	void render();
	void init();
	void cleanUp();
	//void keyhit(WPARAM wParam);
	void timerTick();
	int ticksElapsed;
};

class state2_class : public UC_GameClass
{

	public:
		UC_texture *texState2;
		UC_texture *texState2b;
		UC_texture *texCursor;
		UC_GUIFrame *guiFrame;
		UC_GUIFrame *guiFrame2;
		myButton *b;//play
		myButton *c;//settings
		myButton *d;//quit
		myButton *e;//help
		myButton *f;//credits
		myButton *back;
		float mouseX,mouseY;
		UC_CWave * intro;
		BYTE prevButtonState;
		bool help;

		state2_class();
		void render();
		void init();
		void cleanUp();
		void keyhit(WPARAM wParam);
		void timerTick();
		void doIt(); // click the button
		void checkMouse();
};
class state3_class : public UC_GameClass
{
	public:
		UC_CWave * intro;
		UC_texture *texState3;
		UC_texture *texCursor;
		UC_GUIFrame *guiFrame;

		myButton *upA;//death
		myButton *downA;//death
		myButton *upB;//kill
		myButton *downB;//kill
		myButton *upC;//round
		myButton *downC;//round
		myButton *upD;//leaque
		myButton *downD;//leaque
		myButton *back;

		float mouseX,mouseY;
		BYTE prevButtonState;

		state3_class();
		void render();
		void init();
		void cleanUp();
		void keyhit(WPARAM wParam);
		void timerTick();
		void doIt(); // click the button
		void checkMouse();
};

class state4_class : public UC_GameClass
{
	public:
		UC_CWave * duel;
		UC_texture *texShipEnabled;
		UC_texture *texShipDisabledLeft;
		UC_texture *texShipDisabledRight;
		UC_CWave * electroBang;
		
		UC_texture *texReady;
		UC_texture *texCursor;
		UC_texture *texSelectedAwing;
		UC_texture *texSelectedXwing;
		UC_texture *texSelectedFalcon;
		UC_texture *texSelectedTie;
		UC_texture *texSelectedNTie;
		UC_texture *texSelectedBTie;
		UC_texture *texSelectedShuttle;

		UC_texture *texAwing1;
		UC_texture *texXwing2;
		UC_texture *texFalcon3;
		UC_texture *texTie4;
		UC_texture *texBTie5;
		UC_texture *texNTie6;
		UC_texture *texShuttle7;

		UC_GUIFrame *guiFrame;
		UC_GUIEdit *pilotName;

		UC_GUIFrame *guiFrame2;
		UC_GUIEdit *pilotName2;

		UC_GUIFrame *guiFrame3;
		UC_GUIEdit *pilotName3;

		UC_GUIFrame *guiFrame4;
		UC_GUIEdit *pilotName4;

		bool displayPress;
		bool boolReady;
		int countTicks, internalState, currentShipNo, nextShipNo, previousShipNo;
		int internalState2, currentShipNo2, nextShipNo2, previousShipNo2;
		int internalState3, currentShipNo3, nextShipNo3, previousShipNo3;
		int internalState4, currentShipNo4, nextShipNo4, previousShipNo4;
		
		float mouseX,mouseY;
		BYTE prevButtonState;

		state4_class();
		void render();
		void init();
		void cleanUp();
		void keyhit(WPARAM wParam);
		void timerTick();
		void doIt(); // click the button
		void checkMouse();
		void setPilots();
};

class state5_class : public UC_GameClass
{

void render();
void init();
void cleanUp();
void keyhit(WPARAM wParam);
void timerTick();
MYLEVEL *myLevel;
};

class state6_class : public UC_GameClass
{
	public:
		UC_GUIFrame *guiFrame;
		myButton *next;//Next Round
		myButton *Quit;//Quit League
		ShipData standings[6];
		float mouseX,mouseY;
		BYTE prevButtonState;
		UC_texture *texCursor;
		UC_CWave * catana;

		state6_class();
		void render();
		void init();
		void cleanUp();
		void keyhit(WPARAM wParam);
		void timerTick();
		void doIt(); // click the button
		void checkMouse();

	private:
		void bubbleSort(ShipData c[6]);	
};

class state7_class : public UC_GameClass
{
	public:
		UC_CWave * victory;
		UC_GUIFrame *guiFrame;
		myButton *Quit;//Quit League
		ShipData standings[6];
		float mouseX,mouseY;
		BYTE prevButtonState;
		UC_texture *texCursor;

		state7_class();
		void render();
		void init();
		void cleanUp();
		void keyhit(WPARAM wParam);
		void timerTick();
		void doIt(); // click the button
		void checkMouse();

	private:
		void bubbleSort(ShipData c[6]);	
};

class state8_class : public UC_GameClass
{

void render();
void init();
void cleanUp();
void keyhit(WPARAM wParam);
};


#endif
