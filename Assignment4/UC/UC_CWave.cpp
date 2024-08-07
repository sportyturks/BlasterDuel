// UC_CWave.cpp 

#include "UC_CWave.h"
#include "UC_main.h"

UC_CWave::UC_CWave()
{
sound = NULL;
g_pSoundBuffer=NULL;
ok=false;
}

UC_CWave::UC_CWave(char *filename)
{
//	CWave *sound;
//IDirectSoundBuffer* g_pSoundBuffer;
sound = NULL;
g_pSoundBuffer=NULL;
ok=false;
loadFile(filename);
}

UC_CWave::~UC_CWave()
{
if (g_pSoundBuffer) g_pSoundBuffer->Release();
if (sound != NULL) delete sound;
}

bool UC_CWave::loadFile(char * fname)
{
ok=false;
strcpy(sndFile,fname);
if (g_pSoundBuffer) g_pSoundBuffer->Release();
if (sound != NULL) delete sound;

sound = new CWave(fname);
if (!sound->WaveOK())
    {
        UC_err2("Could not load wave file...",fname);
        return false;
    }

LPWAVEFORMATEX pWaveFormatEx = sound->GetWaveFormatPtr();
char* pWaveData = sound->GetWaveDataPtr();
DWORD dwWaveSize = sound->GetWaveSize();

DSBUFFERDESC dsBufferDesc;
memset(&dsBufferDesc, 0, sizeof(DSBUFFERDESC));
dsBufferDesc.dwSize = sizeof(DSBUFFERDESC);
dsBufferDesc.dwBufferBytes = dwWaveSize;
dsBufferDesc.lpwfxFormat = (LPWAVEFORMATEX) pWaveFormatEx;
rc = g_pDirectSoundObj->
      CreateSoundBuffer(&dsBufferDesc, &g_pSoundBuffer, NULL);
if (FAILED(rc))
    {
    UC_err2("Could not create sound buffer.",fname);
    return false;
    }

LPVOID pSoundBlock1;
LPVOID pSoundBlock2;
DWORD dwBytesSoundBlock1;
DWORD dwBytesSoundBlock2;
rc = g_pSoundBuffer->Lock(0, dwWaveSize,
        &pSoundBlock1, &dwBytesSoundBlock1,
        &pSoundBlock2, &dwBytesSoundBlock2, 0);
if (FAILED(rc))
    {
        UC_err2("Could not lock sound buffer.",fname);
        return false;
    }
memcpy((void*)pSoundBlock1, pWaveData, dwWaveSize);
g_pSoundBuffer->Unlock(pSoundBlock1, dwBytesSoundBlock1,
        pSoundBlock2, dwBytesSoundBlock2);

delete sound;
sound = NULL;
ok=true;
return true;
}


bool UC_CWave::isOK()
{
return ok;
}

LONG UC_CWave::getVolume()
{
	LONG retv;
	g_pSoundBuffer->GetVolume(&retv);
	return retv;
}

void UC_CWave::setVolume(LONG v)
{
	g_pSoundBuffer->SetVolume(v);
}

void UC_CWave::stop()
{
	g_pSoundBuffer->Stop();
}

bool UC_CWave::play()
{
    rc = g_pSoundBuffer->SetCurrentPosition(0);
    if (FAILED(rc))
    {
        UC_err2("Could not set sound cursor position.",sndFile);
        return false;
    }

    //rc = g_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    rc = g_pSoundBuffer->Play(0, 0, 0);
    /*if (FAILED(rc))
    {
        UC_err2("Could not play sound buffer.",sndFile);
        return false;
    }*/
return true;
}

///////////////////////////////////////////////////////////
//  CWave::play_looping()
///////////////////////////////////////////////////////////
bool UC_CWave::play_looping()
{

    rc = g_pSoundBuffer->SetCurrentPosition(0);

    if (FAILED(rc))
    {
        UC_err2("Could not set sound cursor position.",sndFile);
        return false;
    }
     rc = g_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    if (FAILED(rc))
    {
        UC_err2("Could not play sound buffer.",sndFile);
        return false;
    }
return true;
}


///////////////////////////////////////////////////////////
//  CWave::playing()
///////////////////////////////////////////////////////////
bool UC_CWave::playing()
{
  DWORD s;
  g_pSoundBuffer->GetStatus(&s);
  return ((DSBSTATUS_PLAYING && s) == DSBSTATUS_PLAYING);
}



// end
