// UC_main.cpp

#include <stdio.h>
#include <time.h>
#include <dsound.h>

#include "UC_main.h"
#include "UC_UtilsV2.h"
#include "UC_surface.h"
#include "UC_gameClass.h"

#include "myClass.h"

#define UC_VersionTxt "Blaster Duel 0.01" 

// Function prototypes.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg,
    WPARAM wParam, LPARAM lParam);
void RegisterWindowClass(HINSTANCE hInstance);
void CreateAppWindow(HINSTANCE hInstance);
WPARAM StartMessageLoop();
HRESULT InitFullScreenDirect3D();
void Render();
void CleanUpDirect3D();

HRESULT g_hResult = D3D_OK;
char g_szErrorMsg[256];
bool canrender=false;

HWND g_hWnd;
IDirect3D8* g_pDirect3D = NULL;
IDirect3DDevice8* g_pDirect3DDevice = NULL;
IDirect3DSurface8* pBackBuffer = NULL;
char debugErrMsg[256];
UC_GameClass *myGame=NULL;
bool keys[256];
IDirectSound8* g_pDirectSoundObj = NULL;
LPDIRECTINPUT8 g_pDI = NULL; 
LPDIRECTINPUTDEVICE8 g_pMouse = NULL;
bool mouseReady=false;
bool mouseAquired=false;
bool usingMouse=false; // set to true if using mouse

int die = 1;
int kill = 2;
int round = 8;
int league = 6;
ShipData results[6];

bool renderNow;
int timerTicks;

//////////////////////////////////////////////////////
// WinMain()
//////////////////////////////////////////////////////
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
    RegisterWindowClass(hInstance);
    CreateAppWindow(hInstance);
    ShowWindow(g_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(g_hWnd);
    HRESULT hResult = InitFullScreenDirect3D();
    if (SUCCEEDED(hResult))
        WPARAM result = StartMessageLoop();
    CleanUpDirect3D();
    CloseWindow(g_hWnd);
    if (g_hResult != D3D_OK)
        DXTRACE_ERR(g_szErrorMsg, g_hResult);
    return 0;
}

void UC_aquireMouse()
{
if (mouseReady)
	{
		g_pMouse->Acquire();
		mouseAquired=true;
	}
}

void UC_unaquireMouse()
{
	if (mouseReady)
	{
		mouseAquired=false;
		g_pMouse->Unacquire();
	}
}


//////////////////////////////////////////////////////
// WndProc()
//////////////////////////////////////////////////////
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
int i;    
	switch(msg)
    {
	case WM_ENTERSIZEMOVE:
		UC_unaquireMouse();
		return 0;

	case WM_ENTERMENULOOP:
		UC_aquireMouse();
		return 0;

	case WM_ACTIVATE:

		if (WA_INACTIVE == wParam)
		   UC_unaquireMouse();
		else
		   UC_aquireMouse();
		// Set exclusive mode access to the mouse based on active state
		return 0; 

	case WM_LBUTTONDOWN:
		UC_aquireMouse();
		return 0;

    case WM_CREATE:
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;

    case WM_PAINT:
        ValidateRect(g_hWnd, NULL);
        return 0;

    case WM_TIMER:
		timerTicks++;
        //MessageBox(0, "Timer event arrived.", "Timer", MB_OK);

		if (canrender) myGame->timerTick();
		renderNow=true;
		return 0;

    case WM_KEYUP:
		i = (int)wParam % 256;
		keys[i]=false; 
		break;
    
	case WM_EXITSIZEMOVE:
		UC_aquireMouse();
		return 0;

    case WM_KEYDOWN:
        i = (int)wParam % 256;
		keys[i]=true; 
		switch(wParam)
        {
            case VK_ESCAPE:
                PostQuitMessage(WM_QUIT);
                break;
			default :
				{
					if (canrender) myGame->keyhit(wParam);
					break;
				}
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

//////////////////////////////////////////////////////
// RegisterWindowClass()
//////////////////////////////////////////////////////
void RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0; 
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "SurfaceApp";
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);
}

//////////////////////////////////////////////////////
// CreateAppWindow()
//////////////////////////////////////////////////////
void CreateAppWindow(HINSTANCE hInstance)
{
    g_hWnd = CreateWindowEx(
        NULL,
        "SurfaceApp",
        UC_version(), 
        WS_OVERLAPPEDWINDOW,
        50,
        50,
        648,
        507,
        GetDesktopWindow(),
        NULL,
        hInstance,
        NULL);
}

//////////////////////////////////////////////////////
// StartMessageLoop()
//////////////////////////////////////////////////////
WPARAM StartMessageLoop()
{
    MSG msg;
    while(1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Use idle time here.
			if (canrender) // allowed
			{
				if (renderNow) // time for next screen
				{
				renderNow=false;
				myGame->render();
				}
			}
        }
    }
    return msg.wParam;
}

//////////////////////////////////////////////////////
// InitDirectSound()
//////////////////////////////////////////////////////
void InitDirectSound()
{
    g_hResult = DirectSoundCreate8(NULL, &g_pDirectSoundObj, NULL);
    if (FAILED(g_hResult))
    {
        UC_err("Error creating DirectSound object.");
        return;
    }

    g_hResult = g_pDirectSoundObj->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL);
    if (FAILED(g_hResult))
    {
        UC_err("Could not set the cooperative level.");
        return;
    }

}

void UC_initDImouse()
{
HRESULT rc;
rc=DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,
    IID_IDirectInput8, (VOID**)&g_pDI, NULL );
if (FAILED(rc)) UC_err("Error> creating Direct Input");

rc = g_pDI->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);
if (FAILED(rc)) UC_err("Error> creating mouse");

// Set the data format to "mouse format" - a predefined data format 
//
// A data format specifies which controls on a device we
// are interested in, and how they should be reported.
//
// This tells DirectInput that we will be passing a
// DIMOUSESTATE2 structure to IDirectInputDevice::GetDeviceState.
rc = g_pMouse->SetDataFormat( &c_dfDIMouse2 );
if( FAILED( rc ) ) UC_err("Error> unable to set mouse format");

rc = g_pMouse->SetCooperativeLevel(g_hWnd,
					   DISCL_EXCLUSIVE | DISCL_FOREGROUND);
 
if (FAILED(rc)) UC_err("unable to set mouse co-operation level");

usingMouse=true;
mouseReady=true;
UC_aquireMouse();
}



//////////////////////////////////////////////////////
// InitFullScreenDirect3D()
//////////////////////////////////////////////////////
HRESULT InitFullScreenDirect3D()
{
    g_pDirect3D = Direct3DCreate8(D3D_SDK_VERSION);
    if (g_pDirect3D == NULL)
    {
        MessageBox(g_hWnd,
            "Couldn’t create DirectX object.",
            "DirectX Error", MB_OK);
        return E_FAIL;
    }

    HRESULT hResult = g_pDirect3D->CheckDeviceType(D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE);
    if (hResult != D3D_OK)
    {
        MessageBox(g_hWnd,
            "Sorry. This program won’t\nrun on your system.",
            "DirectX Error", MB_OK);
        return E_FAIL;
    }
    D3DPRESENT_PARAMETERS D3DPresentParams;
    ZeroMemory(&D3DPresentParams, sizeof(D3DPRESENT_PARAMETERS));
    D3DPresentParams.Windowed = !UC_FULLSCREEN;
    //D3DPresentParams.Windowed = FALSE;
    D3DPresentParams.BackBufferCount = 1;
    D3DPresentParams.BackBufferWidth = 1024;
    D3DPresentParams.BackBufferHeight = 768;
    D3DPresentParams.BackBufferFormat = D3DFMT_X8R8G8B8;
    D3DPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    D3DPresentParams.hDeviceWindow = g_hWnd;
    hResult = g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
    &D3DPresentParams, &g_pDirect3DDevice);
    if (FAILED(hResult))
    {
        MessageBox(g_hWnd,
            "Failed to create Direct3D device.",
            "DirectX Error", MB_OK);
        return E_FAIL;
    }
    
    InitDirectSound();

    srand( (unsigned)time( NULL ) );
    myGame = new MYCLASS();

	for (int i=0; i<256; i++) keys[i]=false;

	myGame->init();

	timerTicks=0;
	SetTimer(g_hWnd, 1, 15, NULL);
	canrender=true;
    renderNow=true;

    return D3D_OK;
}

//////////////////////////////////////////////////////
// CleanUpDirect3D()
//////////////////////////////////////////////////////
void CleanUpDirect3D()
{
	UC_renderOFF();
	KillTimer(g_hWnd, 1);
    myGame->cleanUp();
	if( g_pMouse ) 
        g_pMouse->Unacquire();
	if (g_pDirect3DDevice)
        g_pDirect3DDevice->Release();
    if (g_pDirectSoundObj)
        g_pDirectSoundObj->Release();
	if( g_pMouse ) 
        g_pMouse->Release();
	if (g_pDI)
		g_pDI->Release();
    if (g_pDirect3D)
        g_pDirect3D->Release();

}


// -----------------------------------
// error handling routine
// -----------------------------------
void UC_err(char *errmess) 
    {
        strcpy(g_szErrorMsg, errmess);
		MessageBox(g_hWnd,g_szErrorMsg,"Message called by UC_err()",MB_OK);
		PostQuitMessage(WM_QUIT);
    }

void UC_err2(char *errmess1, double d)
{
	char temp[500];
	sprintf(temp,"%s %f",errmess1,d );
	UC_err(temp);
}

void UC_err2(char *errmess1, char *errmess2)

{
char temp[500];
strcpy(temp,errmess1);
strcat(temp,"  ");
strcat(temp,errmess2);
UC_err(temp);
}

void UC_renderON()
{
	canrender=true;
}

void UC_renderOFF()
{
	canrender=false;
}


char *UC_version()
{
	return UC_VersionTxt;
}



// end