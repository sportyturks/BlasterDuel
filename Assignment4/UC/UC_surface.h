#ifndef UC_surface_z11
#define UC_surface_z11
// include file for the UC_surface class

#include <windows.h>
#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>

class UC_surface
{	
private:	
	HRESULT rc;

public:
	IDirect3DSurface8* bitmapData;
    char fname[255];
	D3DXIMAGE_INFO info;
	//char id[16];
	UC_surface();
	UC_surface(char *fullFileName, int width, int height);
	UC_surface(char *fullFileName, int width, int height, D3DCOLOR transColor);
	~UC_surface();
	bool LoadSurface(char *fullFileName, int width, int height);
	bool LoadSurface(char *fullFileName, int width, int height, D3DCOLOR transColor);
};

class UC_texture
{	
private:	
	HRESULT rc;

public:
	IDirect3DTexture8* textureData;
	D3DLOCKED_RECT LockedRect; // when we lock it
    D3DCOLOR * pData;
	bool locked;

    char fname[255];
	
	int imageWidth; // as passed in by constructor
	int imageHeight; // as passed in by constructor
	int trueWidth; // as read from the file
	int trueHeight; // as read from the file

	//char id[16];
	UC_texture();
	UC_texture(char *fullFileName, int width, int height);
	UC_texture(char *fullFileName, int width, int height, D3DCOLOR transColor);
	UC_texture(char *fullFileName, int width, int height, D3DCOLOR transColor, int alphaVal);
	~UC_texture();
	bool LoadTexture(char *fullFileName, int width, int height);
	bool LoadTexture(char *fullFileName, int width, int height, D3DCOLOR transColor);
	bool LoadTexture(char *fullFileName, int width, int height, D3DCOLOR transColor, int alphaVal);
	
	HRESULT saveTexture(char *fullFileName);

	void lock();
	void unlock();

	D3DCOLOR getPixelFast(int x, int y);
	D3DCOLOR getPixelSafe(int x, int y);
	void setPixelFast(int x, int y, D3DCOLOR pixColor);
	bool setPixelSafe(int x, int y, D3DCOLOR pixColor);
};


#endif