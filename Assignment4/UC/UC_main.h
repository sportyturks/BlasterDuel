#ifndef main_Z11
#define main_Z11
// include file for the main program


#include <windows.h>
#include <dsound.h>
#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>
#include <dinput.h>

#include "UC_gameclass.h"
#include "UC_gui.h"

typedef struct 
{
	char pilotName[24];
	int leaguePoints;
	int roundPoints;
	bool selected;
	int selectedShip;
	int playerNo;
} ShipData;

extern HWND g_hWnd;
extern IDirect3D8* g_pDirect3D;
extern IDirect3DDevice8* g_pDirect3DDevice;
extern IDirect3DSurface8* pBackBuffer;
extern char debugErrMsg[256];
extern int timerTicks;
extern UC_GameClass *myGame;
extern bool keys[256];
extern IDirectSound8* g_pDirectSoundObj;
extern LPDIRECTINPUT8 g_pDI;
extern LPDIRECTINPUTDEVICE8 g_pMouse;     
extern bool mouseAquired;
extern bool usingMouse; // set to true if using mouse

extern int die;
extern int kill;
extern int round;
extern int league;
extern ShipData results[6];

void UC_err(char *errmess);
void UC_err2(char *errmess1, char *errmess2);
void UC_err2(char *errmess1, double d);
void UC_renderON();
void UC_renderOFF();

char *UC_version();
void UC_unaquireMouse();
void UC_aquireMouse();
void UC_initDImouse();

//end
#endif