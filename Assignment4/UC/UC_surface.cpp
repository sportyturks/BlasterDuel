// surface class

#include "UC_surface.h"
#include "UC_main.h"
#include "UC_UtilsV2.h"
#include "UC_Dir.h"

UC_surface::UC_surface()
{
	bitmapData = NULL;
	rc = D3D_OK;
}

UC_surface::UC_surface(char *fullFileName, int width, int height)
{
	bitmapData = NULL;
	rc = D3D_OK;
	LoadSurface(fullFileName, width, height);
}

UC_surface::UC_surface(char *fullFileName, int width, int height, D3DCOLOR transColor)
{
	bitmapData = NULL;
	rc = D3D_OK;
	LoadSurface(fullFileName, width, height,transColor);
}

bool UC_surface::LoadSurface(char *fullFileName, int width, int height)
{
	strcpy(fname,fullFileName);
	rc = g_pDirect3DDevice->CreateImageSurface(width, height,
        D3DFMT_X8R8G8B8, &bitmapData);
	if (FAILED(rc)) {UC_err("Error creating bitmap surface."); return false;}
    
    rc = D3DXLoadSurfaceFromFile(bitmapData, NULL, NULL,
		fname, NULL, D3DX_DEFAULT, 0, &info);
	if (FAILED(rc)) {UC_err("Couldn’t load bitmap file."); return false;}
    return true;
}
bool UC_surface::LoadSurface(char *fullFileName, int width, int height, D3DCOLOR transColor)
{
	strcpy(fname,fullFileName);
	rc = g_pDirect3DDevice->CreateImageSurface(width, height,
        D3DFMT_X8R8G8B8, &bitmapData);
	if (FAILED(rc)) {UC_err("Error creating bitmap surface."); return false;}
    
    rc = D3DXLoadSurfaceFromFile(bitmapData, NULL, NULL,
		fname, NULL, D3DX_DEFAULT, transColor, &info);
	if (FAILED(rc)) {UC_err("Couldn’t load bitmap file."); return false;}
    return true;
}

UC_surface::~UC_surface()
{
if (bitmapData!=NULL) bitmapData->Release();
}

// --------------------- UC_texture routines below --------------

UC_texture::UC_texture()
{
	textureData = NULL;
	rc = D3D_OK;
	locked=false;
}

UC_texture::UC_texture(char *fullFileName, int width, int height)
{
	textureData = NULL;
	rc = D3D_OK;
	LoadTexture(fullFileName, width, height);
	locked=false;
}

UC_texture::UC_texture(char *fullFileName, int width, int height, D3DCOLOR transColor)
{
	textureData = NULL;
	rc = D3D_OK;
	LoadTexture(fullFileName, width, height,transColor);
}

UC_texture::UC_texture(char *fullFileName, int width, int height, D3DCOLOR transColor, int alphaVal)
{
	textureData = NULL;
	rc = D3D_OK;
	LoadTexture(fullFileName, width, height,transColor,alphaVal);
}

bool UC_texture::LoadTexture(char *fullFileName, int width, int height)
{
return UC_texture::LoadTexture(fullFileName, width, height,0,255);
}

bool UC_texture::LoadTexture(char *fullFileName, int width, int height, D3DCOLOR transColor)
{
	return UC_texture::LoadTexture(fullFileName, width, height,transColor,255);

}
bool UC_texture::LoadTexture(char *fullFileName, int width, int height, D3DCOLOR transColor, int alphaVal)
{
    strcpy(fname,fullFileName);
	rc = D3DXCreateTextureFromFileEx(g_pDirect3DDevice, fullFileName,
        D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, transColor,
        NULL, NULL, &textureData);

    if(FAILED(rc)) 
    {
		UC_err2("Couldn’t load texture file.",fullFileName);
        return false;
    }

	imageWidth=width;
	imageHeight=height;

    D3DSURFACE_DESC pDesc1;
    rc=textureData->GetLevelDesc(0,&pDesc1);

	if(FAILED(rc)) 
    {
		UC_err2("Couldn’t load texture file deatails.",fullFileName);
        return false;
    }

	trueWidth=pDesc1.Width;
	trueHeight=pDesc1.Height;

	if (imageWidth==0 || imageWidth == D3DX_DEFAULT) imageWidth=trueWidth; 
	if (imageHeight==0 || imageHeight == D3DX_DEFAULT) imageHeight=trueHeight; 

	if(textureData==NULL) 
    {
		UC_err2("Danger NULL textureData.",fullFileName);
        return false;
    }


if (alphaVal != 255)
	{
    D3DCOLOR temp;
	// post process to set alpha value
	lock();
	for (int x=0; x<= trueWidth; x++)
		for (int y=0; y<=trueHeight; y++)
		{
        temp=getPixelSafe(x,y);
        if (temp >> 24 != 0 )
			{
			setPixelSafe(x,y, D3DCOLOR_ARGB(alphaVal,UC_getRval(temp),UC_getGval(temp),UC_getBval(temp)));
			}
		}
	unlock();
	}

	return true;
}

UC_texture::~UC_texture()
{
	if (textureData!=NULL) textureData->Release();
}

void UC_texture::lock()
{
	textureData->LockRect(0,&LockedRect,NULL,0);
	//	D3DLOCKED_RECT LockedRect; // when we lock it
    pData=(D3DCOLOR *)(LockedRect.pBits);
	locked=true;
}

void UC_texture::unlock()
{
	textureData->UnlockRect(0);
	locked=false;
}

D3DCOLOR UC_texture::getPixelSafe(int x, int y)
{
if (!locked) return UC_OPAQUE_BLACK;
if (x < 0) return UC_OPAQUE_BLACK;
if (y < 0) return UC_OPAQUE_BLACK;
if (x >= trueWidth ) return UC_OPAQUE_BLACK;
if (y >= trueHeight) return UC_OPAQUE_BLACK;
return getPixelFast(x,y);
}

D3DCOLOR UC_texture::getPixelFast(int x, int y)
{
D3DCOLOR retv;
retv = pData[(LockedRect.Pitch/4) * y + x];
return retv;
}
	
bool UC_texture::setPixelSafe(int x, int y, D3DCOLOR pixColor)
{
if (!locked) {UC_err2("ERROR>> texture not locked ",fname); return false;}
if (x < 0) return false;
if (y < 0) return false;
if (x >= trueWidth ) return false;
if (y >= trueHeight) return false;
	
setPixelFast(x,y,pixColor);
return true;
}

void UC_texture::setPixelFast(int x, int y, D3DCOLOR pixColor)
{
pData[(LockedRect.Pitch/4) * y + x]=pixColor;
}

HRESULT UC_texture::saveTexture(char *fullFileName)
// set r to NULL for full texture save
{
HRESULT rc;
rc=D3DXSaveTextureToFile(fullFileName,D3DXIFF_BMP,
						 textureData ,NULL);
return rc;
}

// end
