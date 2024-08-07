///////////////////////////////////////////////////////////
// CWAVE.H: Header file for the WAVE class.
///////////////////////////////////////////////////////////

#ifndef __CWAVE_H
#define __CWAVE_H

#include <windows.h>
#include <mmsystem.h>

class CWave
{
protected:
    DWORD m_dwWaveSize;
    BOOL m_bWaveOK;
    char* m_pWave;
    WAVEFORMATEX m_waveFormatEx;

public:
    CWave(char* fileName);
    ~CWave();

    DWORD GetWaveSize();
    LPWAVEFORMATEX GetWaveFormatPtr();
    char* GetWaveDataPtr();
    BOOL WaveOK();

protected:
    BOOL LoadWaveFile(char* fileName);
};

#endif
