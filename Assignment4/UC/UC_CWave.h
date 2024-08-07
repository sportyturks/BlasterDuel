#ifndef UC_CCWAVE
#define UC_CCWAVE

#include <windows.h>
#include <dsound.h>
#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>
#include "CWave.h"

class UC_CWave 
{
private:
HRESULT rc;
bool ok;
char sndFile[256];

public:
CWave *sound;
IDirectSoundBuffer* g_pSoundBuffer;

bool isOK();
bool play();
void stop();
LONG getVolume();
void setVolume(LONG v);
bool play_looping();
bool playing();

UC_CWave();
UC_CWave(char *filename);
~UC_CWave();
bool loadFile(char * fname);
};

#endif