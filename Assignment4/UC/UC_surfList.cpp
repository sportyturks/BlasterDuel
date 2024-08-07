// Texture class

#include "UC_surfList.h"
#include "UC_main.h"
#include "UC_UtilsV2.h"
#include "UC_Dir.h"


// --- now surface list rioutines below -------

	UC_surface_list::UC_surface_list()
	{
		int i;
		for (i=0;i<maxSurface;i++)
		{
			t[i]=NULL;
		}
	}


	UC_surface_list::~UC_surface_list()
	{
	int i;
	for (i=0;i<maxSurface;i++)
		{
			if (t[i]!=NULL) delete t[i];
		}

	}

    IDirect3DSurface8* UC_surface_list::getSurface(int i)
	{
	return t[i]->bitmapData;
	}

// --- now texture list rioutines below -------

	UC_texture_list::UC_texture_list()
	{
		int i;
		for (i=0;i<maxTexture;i++)
		{
			t[i]=NULL;
		}
	}

	void UC_texture_list::loadTexture(int i, char *fname, D3DCOLOR colorKey)
	{
	if (t[i] != NULL) 
		{
		delete t[i]; // stop memory leak
		}
	t[i]=new UC_texture(fname,D3DX_DEFAULT,D3DX_DEFAULT,colorKey);
	//if (i==0)UC_err("=0");
	if (t[i]->textureData == NULL) 
		{
		UC_err2("texture not loaded",fname);
		}
	}

	UC_texture_list::~UC_texture_list()
	{
	int i;
	for (i=0;i<maxTexture;i++)
		{
			if (t[i]!=NULL) delete t[i];
		}

	}

IDirect3DTexture8* UC_texture_list::getD8Texture(int i)
	{
	return t[i]->textureData;
	}

UC_texture* UC_texture_list::getUC_Texture(int i)
{
	return t[i];

}


// end
