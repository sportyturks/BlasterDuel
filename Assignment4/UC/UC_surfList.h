#ifndef UC_texture_z11
#define UC_texture_z11
// include file for the UC_lists class

#include "UC_surface.h"

class UC_texture_list
{	
public:
	const static int maxTexture=200;
	UC_texture_list();
	~UC_texture_list();
	void loadTexture(int i, char *fname, D3DCOLOR colorKey);
    IDirect3DTexture8* getD8Texture(int i);
    UC_texture* getUC_Texture(int i);

private:	
	HRESULT rc;
    UC_texture *t[maxTexture];
};




class UC_surface_list
{	
public:
	const static int maxSurface=200;
	UC_surface_list();
	~UC_surface_list();
    IDirect3DSurface8* getSurface(int i);

private:	
	HRESULT rc;
    UC_surface *t[maxSurface];
};

#endif