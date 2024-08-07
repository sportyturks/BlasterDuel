#ifndef gameClass_Z11
#define gameClass_Z11
// include file for the game class program


#include <windows.h>
#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>
#include <dinput.h>

class UC_GameClass
{
protected:	
	HRESULT rc;

public:    
// students must override these	
virtual void init()=0;
virtual void cleanUp()=0;
virtual void render()=0;

// students will probably want to override these
virtual void keyhit(WPARAM wParam);
virtual void timerTick();
virtual void mouseMove(int newx, int newy, DIMOUSESTATE2 *ms);
virtual void mouseKlick(int newx, int newy, DIMOUSESTATE2 *ms);

// students will not normally override these
virtual bool *pollKeyboard();

// students should not call these
UC_GameClass();
~UC_GameClass();
};

// end
#endif