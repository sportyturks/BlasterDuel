//UC_Utils.cpp
// usefull graphics routines
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "UC_utilsV2.h"
#include "UC_main.h"
#include "UC_surface.h"

float orientU[]=
{
0,0,1,1,0,0,1,1, 1,1,0,0,1,1,0,0, 0,0,1,1,0,0,1,1
};

float orientV[]=
{
1,0,0,1,1,0,0,1, 1,0,0,1,1,0,0,1, 0,1,1,0,0,1,1,0
};


//LPD3DXFONT pFont0 = NULL; // unused
LPD3DXFONT pFont9 = NULL;
LPD3DXFONT pFont2 = NULL;
LPD3DXFONT pFont3 = NULL;


LOGFONT LogFont1 = {16, 0, 0, 0, FW_NORMAL, false, false, false,
        DEFAULT_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH, "Times New Roman"};

LOGFONT LogFont2 = {22, 0, 0, 0, FW_NORMAL, false, false, false,
        DEFAULT_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH, "Arial"};

LOGFONT LogFont3 = {18, 0, 0, 0, FW_NORMAL, false, false, false,
        DEFAULT_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH, "Courier New"};

void setUC_CustomVertex(UC_CustomVertex *v, float xx, float yy, 
             float uu, float vv)
    {
		v->x = xx;
		v->y = yy;
		v->z = 0;
		v->rhw = 1; //float rhw=1.0f/(z*990.0f+10.0f);
        v->tu = uu;
		v->tv = vv;
    }

UC_CustomVertex triangleVertices[] =
    {
        {10.0f, 74.0f, 0.0f, 1.0f, 0.0f, 1.0f,},
        {10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f,},
        {74.0f, 10.0f, 0.0f, 1.0f, 1.0f, 0.0f,},
        {10.0f, 74.0f, 0.0f, 1.0f, 0.0f, 1.0f,},
        {74.0f, 10.0f, 0.0f, 1.0f, 1.0f, 0.0f,},
        {74.0f, 74.0f, 0.0f, 1.0f, 1.0f, 1.0f,},
    };

UC_CustomVertex verts[4];

UC_CustVertWColor shapeVertices[] =
    {
        {400.0f, 180.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255,0,0),},
        {500.0f, 380.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0,255,0),},
        {300.0f, 380.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0,0,255),},
        {300.0f, 380.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0,0,255),},
        {300.0f, 380.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0,0,255),},
    };


void BasicBlit(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top)
{
	float right;
	float bottom;
    D3DSURFACE_DESC pDesc;
	HRESULT rc;
	if (lpSrc == NULL) 
	{
		UC_err("null texture pointer");
		return;
	}
    rc=lpSrc->GetLevelDesc(0,&pDesc);
	right=left+pDesc.Width;
	bottom=top+pDesc.Height;

    // set up rectangle

    setUC_CustomVertex(&verts[0], left-0.5f, top-0.5f,  0.0f, 0.0f); 
    setUC_CustomVertex(&verts[1], right-0.5f, top-0.5f,  1.0f, 0.0f); 
    setUC_CustomVertex(&verts[2], right-0.5f, bottom-0.5f,  1.0f, 1.0f); 
    setUC_CustomVertex(&verts[3], left-0.5f, bottom-0.5f,  0.0f, 1.0f); 

    // set the texture
    lpDevice->SetTexture(0,lpSrc);
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    // configure shader for vertex type
    lpDevice->SetVertexShader(D3DFVF_XYZRHW|D3DFVF_TEX1);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
    // draw the rectangle
    lpDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,verts,sizeof(UC_CustomVertex));
    lpDevice->EndScene();
    }
}


void BlitRect(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom)
{
BlitRectOr( lpDevice,
               lpSrc,
               left,  top,
               right,  bottom, false, 0);

}

void BlitRectTr(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom, bool trans)
{
BlitRectOr( lpDevice,
               lpSrc,
               left,  top,
               right,  bottom,
               trans,0);
}

void BlitRectOr(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom,
              bool trans, int orient)
{
// orient 0 = normal
// orient 1 = 90 deg anti clockwise
// orient 2 = 180 deg anti clockwise
// orient 3 = 270 deg anti clockwise
// orient 8 = flip left to right
// orient 16 = flip top to bottom
//
if (lpSrc == NULL) 
		{
		UC_err("null texture pointer");
		return;
		}

if (right==0 || bottom == 0)
	{
    D3DSURFACE_DESC pDesc;
	HRESULT rc;
    rc=lpSrc->GetLevelDesc(0,&pDesc);
	if (right == 0) right=left+pDesc.Width;
	if (bottom == 0) bottom=top+pDesc.Height;
	}

setUC_CustomVertex(&triangleVertices[0], left-0.5f, bottom-0.5f, orientU[0+orient],orientV[0+orient]);
setUC_CustomVertex(&triangleVertices[1], left-0.5f, top-0.5f, orientU[1+orient],orientV[1+orient]);
setUC_CustomVertex(&triangleVertices[2], right-0.5f, top-0.5f, orientU[2+orient],orientV[2+orient]);
setUC_CustomVertex(&triangleVertices[3], left-0.5f, bottom-0.5f,  orientU[0+orient],orientV[0+orient]);
setUC_CustomVertex(&triangleVertices[4], right-0.5f, top-0.5f,  orientU[2+orient],orientV[2+orient]);
setUC_CustomVertex(&triangleVertices[5], right-0.5f, bottom-0.5f, orientU[3+orient],orientV[3+orient]);

lpDevice->SetTextureStageState(0,D3DTSS_COLOROP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_COLORARG1, D3DTA_TEXTURE);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
if (trans)
	{
	lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}
else
	{
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
lpDevice->SetVertexShader(D3DFVF_XYZRHW|D3DFVF_TEX1);
lpDevice->SetTexture(0, lpSrc);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
        lpDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,triangleVertices,sizeof(UC_CustomVertex));
        lpDevice->EndScene();
    }

}

void BlitPart(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float srcLeft, float srcTop,
              float srcRight, float srcBottom,
              float destLeft, float destTop,
              float destRight, float destBottom,
              bool trans)
{
float srcUleft=0;
float srcVtop=0;
float srcUright=1;
float srcVbot=1;
float h;
float w;

D3DSURFACE_DESC pDesc;
HRESULT rc;
rc=lpSrc->GetLevelDesc(0,&pDesc);
w=(float)pDesc.Width;
h=(float)pDesc.Height;

srcUleft=srcLeft/w;
srcVtop=srcTop/h;
srcUright=srcRight/w;
srcVbot=srcBottom/h;

setUC_CustomVertex(&verts[0], destLeft-0.5f, destTop-0.5f,  srcUleft, srcVtop); 
setUC_CustomVertex(&verts[1], destRight-0.5f, destTop-0.5f,  srcUright, srcVtop); 
setUC_CustomVertex(&verts[2], destRight-0.5f, destBottom-0.5f,  srcUright, srcVbot); 
setUC_CustomVertex(&verts[3], destLeft-0.5f, destBottom-0.5f,  srcUleft, srcVbot); 

lpDevice->SetTextureStageState(0,D3DTSS_COLOROP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_COLORARG1, D3DTA_TEXTURE);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
if (trans)
	{
	lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}
else
	{
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
lpDevice->SetVertexShader(D3DFVF_XYZRHW|D3DFVF_TEX1);
lpDevice->SetTexture(0, lpSrc);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
        lpDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,verts,sizeof(UC_CustomVertex));
        lpDevice->EndScene();
    }

}

void BlitFrame(LPDIRECT3DDEVICE8 lpDevice,
              UC_texture *tex,
              int frameNum, int NumofFrames,
              float destLeft, float destTop,
              float destRight, float destBottom,
              bool trans)
{
	// WARNING frame number start at 0
float h;
float w;
w=(float)tex->imageWidth;
h=(float)tex->imageHeight;

float srcLeft;
float srcTop;
float srcRight;
float srcBottom;

srcLeft=(frameNum)*(w/NumofFrames);

srcTop=0;
srcRight=srcLeft+(w/NumofFrames);
srcBottom=h;
//UC_err2("w",w);

BlitPart( lpDevice,
		 tex->textureData,
          srcLeft,  srcTop,
          srcRight,  srcBottom,
          destLeft,  destTop,
          destRight,  destBottom,
          trans);
}

void BigBlitRotate(LPDIRECT3DDEVICE8 lpDevice,
              UC_texture *tex,
              float srcLeft, float srcTop,
              float srcRight, float srcBottom,
              float destLeft, float destTop,
              float destRight, float destBottom,
              bool trans, int orient,
			  float centerX, float centerY,
			  float angleInRadians,
			  UC_rect *srcBoundBox,
			  UC_rect *destBoundBox, 
			  bool showBB
			  )
{
// WARNING THIS IS NOT REALLY A BLIT BECAUSE IT IS NOT USING AXIS ALIGNED
// RECTANGLES IN ITS DESTINATION
//
// lpDevice, the direct 3D device
// lpSrc, The texture data of type LPDIRECT3DTEXTURE8
// srcLeft, srcTop, Source rectangle top left co-ordinates
// srcRight, srcBottom, 0 or Source rectangle top left co-ordinates
// destLeft, destTop, Destination rectangle before rotation
// destRight, destBottom, 0 or Destination rectangle bottom right co-ords before
// trans, true= transparent blit  false=opaque blit
// orient, 0=normal 8 = flip left to right 16 = flip top to bottom 24=both flips
// centerX, centerY, point to rotate about
// angleInRadians, angle to rotate
// *srcBoundBox, NULL or a pointer to a bounding box
// *destBoundBox, NULL or a pointer to a bounding box in which
//                a transformed form of srcBoundBox will be put
// 
// showBB - set this to true to show the resultant bounding box
//          this is for debugging/demonstration only

float srcUVleft;
float srcUVtop;
float srcUVright;
float srcUVbot;
float tempUV;
float h;
float w;
float tempX,tempY;
float x1,y1,x2,y2,x3,y3,x4,y4;
UC_rect tempRect;

if (tex == NULL) 
		{
		UC_err("null texture pointer");
		return;
		}

if (srcRight == 0) srcRight=srcLeft+tex->imageWidth;
if (srcBottom == 0) srcBottom=srcTop+tex->imageHeight;
if (destRight == 0) destRight=destLeft+tex->imageWidth;
if (destBottom == 0) destBottom=destTop+tex->imageHeight;

w=(float)tex->trueWidth;
h=(float)tex->trueHeight;

srcUVleft=srcLeft/w;
srcUVtop=srcTop/h;
srcUVright=srcRight/w;
srcUVbot=srcBottom/h;

if (orient == 8 || orient == 24) 
	{
	// flip left to right
	tempUV=srcUVleft;
	srcUVleft=srcUVright;
	srcUVright=tempUV;
	}
if (orient == 16 || orient == 24) 
	{
	// flip top to bottom
	tempUV = srcUVtop;
	srcUVtop=srcUVbot;
    srcUVbot=tempUV;
	}
	
if (destBoundBox != NULL)
		{
		if (srcBoundBox == NULL)
			{
			tempRect.top=destTop;
			tempRect.bottom=destBottom;
			tempRect.left=destLeft;
			tempRect.right=destRight;
			}
		else
			{
			tempRect = *srcBoundBox;
			}
		}

x1 = destLeft-0.5f;
y1 = destTop-0.5f;
x2 = destRight-0.5f;
y2 = destTop-0.5f;
x3 = destRight-0.5f;
y3 = destBottom-0.5f;
x4 = destLeft-0.5f;
y4 = destBottom-0.5f;

if (angleInRadians != 0)
	{
    rotatePoint(x1,y1, centerX, centerY, angleInRadians, &x1,&y1);
    rotatePoint(x2,y2, centerX, centerY, angleInRadians, &x2,&y2);
    rotatePoint(x3,y3, centerX, centerY, angleInRadians, &x3,&y3);
    rotatePoint(x4,y4, centerX, centerY, angleInRadians, &x4,&y4);
	}

if (destBoundBox != NULL)
		{
		// UC_rect *destBoundBox
		if (angleInRadians != 0)
			{
			rotatePoint(tempRect.left,tempRect.top, centerX, centerY, angleInRadians, &tempX,&tempY);
			destBoundBox->top=tempY;
			destBoundBox->bottom=tempY;
			destBoundBox->left=tempX;
			destBoundBox->right=tempX;
		
			rotatePoint(tempRect.right,tempRect.top, centerX, centerY, angleInRadians, &tempX,&tempY);
			if (tempY < destBoundBox->top) destBoundBox->top=tempY; 
			if (tempY > destBoundBox->bottom) destBoundBox->bottom=tempY; 
			if (tempX < destBoundBox->left) destBoundBox->left=tempX; 
			if (tempX > destBoundBox->right) destBoundBox->right=tempX; 
		
			rotatePoint(tempRect.right,tempRect.bottom, centerX, centerY, angleInRadians, &tempX,&tempY);
			if (tempY < destBoundBox->top) destBoundBox->top=tempY; 
			if (tempY > destBoundBox->bottom) destBoundBox->bottom=tempY; 
			if (tempX < destBoundBox->left) destBoundBox->left=tempX; 
			if (tempX > destBoundBox->right) destBoundBox->right=tempX; 
			
			rotatePoint(tempRect.left,tempRect.bottom, centerX, centerY, angleInRadians, &tempX,&tempY);
			if (tempY < destBoundBox->top) destBoundBox->top=tempY; 
			if (tempY > destBoundBox->bottom) destBoundBox->bottom=tempY; 
			if (tempX < destBoundBox->left) destBoundBox->left=tempX; 
			if (tempX > destBoundBox->right) destBoundBox->right=tempX; 
			}
		else
			{
				*destBoundBox = tempRect;
			}

		
	}

setUC_CustomVertex(&verts[0], x1, y1,  srcUVleft, srcUVtop); 
setUC_CustomVertex(&verts[1], x2, y2,  srcUVright, srcUVtop); 
setUC_CustomVertex(&verts[2], x3, y3,  srcUVright, srcUVbot); 
setUC_CustomVertex(&verts[3], x4, y4,  srcUVleft, srcUVbot); 

lpDevice->SetTextureStageState(0,D3DTSS_COLOROP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_COLORARG1, D3DTA_TEXTURE);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
lpDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
if (trans)
	{
	lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}
else
	{
	lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
lpDevice->SetVertexShader(D3DFVF_XYZRHW|D3DFVF_TEX1);
lpDevice->SetTexture(0, tex->textureData);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
        lpDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,verts,sizeof(UC_CustomVertex));
        lpDevice->EndScene();
    }

if (showBB && destBoundBox != NULL)
	{
	UC_DrawLineQuad2D(lpDevice,
		(int)destBoundBox->left, (int)destBoundBox->top,
		(int)destBoundBox->right, (int)destBoundBox->top,
		(int)destBoundBox->right, (int)destBoundBox->bottom,
		(int)destBoundBox->left, (int)destBoundBox->bottom,
		UC_GREY,UC_GREY,UC_GREY,UC_GREY);
	//UC_printf(lpDevice, 10,10,UC_GREY, 0,18,
	//	  "bb %f %f %f %f",
	//	  destBoundBox->left, destBoundBox->top,
	//	  destBoundBox->right, destBoundBox->bottom
//		  );

	}

}

void UC_DrawText(LPDIRECT3DDEVICE8 lpDevice, int x, int y, char *text, D3DCOLOR c)
{
UC_DrawTextEx(lpDevice, x,  y, text, c, 0);
}

void UC_DrawTextEx(LPDIRECT3DDEVICE8 lpDevice, int x, int y, char *text,
				   D3DCOLOR c, int style)
{
HRESULT rc;
// Calculate the size of a rectangle that can hold the text.
RECT r;
if (style>3 || style < 1) style=1;
if (pFont9==NULL)
{
	UC_err2("You must run UC_UtilsCreateFonts to initialise this routine",
		    "You must run UC_UtilsDeleteFonts to release memory after");
	return;
}
r.left = 0;
r.top = 0;
r.right = 0;
r.bottom = 0;
if (style==1) pFont9->DrawText(text, -1, &r, DT_CALCRECT, 0xff000000);
if (style==2) pFont2->DrawText(text, -1, &r, DT_CALCRECT, 0xff000000);
if (style==3) pFont3->DrawText(text, -1, &r, DT_CALCRECT, 0xff000000);
int iWidth = r.right - r.left;
int iHeight = r.bottom - r.top;
if (x == -1)
	{
	// center of screen
	r.left = (640 - iWidth) / 2;
	r.right = r.left + iWidth;
	r.top = (480 - iHeight) / 2;
	r.bottom = r.top + iHeight;
	}
else
	{
	r.left = x;
	r.right = r.left + iWidth;
	r.top = y;
	r.bottom = r.top + iHeight;
	}

if(SUCCEEDED(lpDevice->BeginScene()))
    {
		if (style==1) rc=pFont9->DrawText(text, -1, &r, DT_CENTER,c);
		if (style==2) rc=pFont2->DrawText(text, -1, &r, DT_CENTER,c);
		if (style==3) rc=pFont3->DrawText(text, -1, &r, DT_CENTER,c);
		if (rc==0) UC_err("text not drawn");
        lpDevice->EndScene();
    }
   
}

void setUC_CustomVertexWcol(UC_CustVertWColor *v, float xx, float yy, D3DCOLOR col)
{
	v->x=xx;
	v->y=yy;
	v->color=col;
	v->z=0;
	v->rhw=1;
}

void UC_DrawTriangle2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   int x2, int y2,
					   D3DCOLOR c0,D3DCOLOR c1,D3DCOLOR c2)
{
setUC_CustomVertexWcol(&shapeVertices[0], (float)x0, (float)y0,c0);
setUC_CustomVertexWcol(&shapeVertices[1], (float)x1, (float)y1,c1);
setUC_CustomVertexWcol(&shapeVertices[2], (float)x2, (float)y2,c2);

lpDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);   
lpDevice->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
lpDevice->SetTexture(0, NULL);
lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
        lpDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,1,shapeVertices,sizeof(UC_CustVertWColor));
        lpDevice->EndScene();
    }
}

void UC_DrawLine2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   D3DCOLOR c0,D3DCOLOR c1)
{
setUC_CustomVertexWcol(&shapeVertices[0], (float)x0, (float)y0,c0);
setUC_CustomVertexWcol(&shapeVertices[1], (float)x1, (float)y1,c1);

lpDevice->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
lpDevice->SetTexture(0, NULL);
lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
		lpDevice->DrawPrimitiveUP(D3DPT_LINESTRIP ,1,shapeVertices,sizeof(UC_CustVertWColor));
		lpDevice->EndScene();
    }
}

void UC_DrawLineQuad2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   int x2, int y2,
					   int x3, int y3,
					   D3DCOLOR c0,D3DCOLOR c1,
					   D3DCOLOR c2,D3DCOLOR c3)
{
setUC_CustomVertexWcol(&shapeVertices[0], (float)x0, (float)y0,c0);
setUC_CustomVertexWcol(&shapeVertices[1], (float)x1, (float)y1,c1);
setUC_CustomVertexWcol(&shapeVertices[2], (float)x2, (float)y2,c2);
setUC_CustomVertexWcol(&shapeVertices[3], (float)x3, (float)y3,c3);
setUC_CustomVertexWcol(&shapeVertices[4], (float)x0, (float)y0,c0);

lpDevice->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
lpDevice->SetTexture(0, NULL);
lpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
lpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
lpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

if(SUCCEEDED(lpDevice->BeginScene()))
    {
		lpDevice->DrawPrimitiveUP(D3DPT_LINESTRIP ,4,shapeVertices,sizeof(UC_CustVertWColor));
		lpDevice->EndScene();
    }
}

double degToRad(double deg)
{
return (deg * 3.14159/180.0);
}

void Move2DInDir(float oldx, float oldz,
                 float yaw, float speed,
                 float *resultx, float *resultz)
{
float tmpx,tmpz;
float newx,newz;

/* set to origin */
tmpx=0;
tmpz=speed; /* move us forward by speed */

newx=(tmpz * (float)sin(yaw)) + (tmpx * (float)cos(yaw));
newz=(tmpz * (float)cos(yaw)) - (tmpx * (float)sin(yaw));
tmpx=newx;
tmpz=newz;

newx=tmpx+oldx;
newz=tmpz+oldz;

*resultx=newx;
*resultz=newz;
}

void rotatePoint(float x, float y,
				 float centerX, float centerY,
				 float angleInRadians,
				 float *newx, float *newy)
{
float tmpx,tmpy,tx,ty;

/* set to origin */
tmpx=x-centerX;
tmpy=y-centerY;

// apply rotate
tx=(tmpy * (float)sin(angleInRadians)) + (tmpx * (float)cos(angleInRadians));
ty=(tmpy * (float)cos(angleInRadians)) - (tmpx * (float)sin(angleInRadians));

*newx=tx+centerX;
*newy=ty+centerY;
}

float dist(float x1, float y1, float x2, float y2)
{
/* calc the distance between 2 points */
float retv;
float d1,d2;
float temp;

d1=x1-x2;
d2=y1-y2;
temp=d1*d1+d2*d2;
retv=(float)sqrt(temp);
return(retv);
}


void direct(double xx1,double yy1,double xx2,double yy2,double *angle,double *distz)
/* calculate angle in degrees and distance to location */
{
double temp;
double ttt;
*distz=dist((float)xx1,(float)yy1,(float)xx2,(float)yy2);
//printf("dist=%f\n",(*distz));
if (*distz==0)
	{
	*angle=0;
	return;
	}
ttt=(xx2-xx1)/(*distz);

temp=asin(ttt);
*angle=temp*180/3.14159;
//printf("angle=%.4f xx1=%.4f xx2=%.4f yy1=%.4f yy2=%.4f\n",*angle,xx1,xx2,yy1,yy2);
if ((yy2<yy1))
	{
		*angle=180-*angle;
	}
if( *angle < 0 )
		*angle = *angle + 360;
if( *angle > 360 )
		*angle = *angle - 360;
}


void UC_kill(void **ptr)
{
  if ((*ptr) != NULL)
  {
    delete (*ptr);
	*ptr=NULL;
  }
}

bool isInRect(float x, float y, float t, float l, float b, float r)
{
	if (x > r) return false;
	if (x < l) return false;
	if (y < t) return false;
	if (y > b) return false;
	return true;
}

void setUC_rect(UC_rect *r, float utop,float uleft, float ubottom, float uright)
{
	r->top=utop;
	r->left=uleft;
	r->bottom=ubottom;
	r->right=uright;
}

void setUC_rectWH(UC_rect *r, float utop,float uleft, float uWidth, float uHeight)
{
	r->top=utop;
	r->left=uleft;
	r->bottom=utop+uHeight-1;
	r->right=uleft+uWidth-1;
}

void UC_printf(LPDIRECT3DDEVICE8 lpDevice, float x, float y,
			   D3DCOLOR c, int style,
			   char* format, ...)
// routine from the textbook
{
    va_list args;
    char buffer[512];
    
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    
    UC_DrawTextEx(lpDevice, (int) x, (int) y, buffer,
				   c, style);
}

void UC_UtilsCreateFonts(LPDIRECT3DDEVICE8 lpDevice)
{
HRESULT rc;
if (pFont9 != NULL) 
{
	UC_err("ERROR>> calling UC_UtilsCreateFonts twice");
	return; // already done it
}					
rc = D3DXCreateFontIndirect(lpDevice, &LogFont1, &pFont9);
if (rc != D3D_OK) UC_err("error > font it 1");
rc = D3DXCreateFontIndirect(lpDevice, &LogFont2, &pFont2);
if (rc != D3D_OK) UC_err("error > font it 2");
rc = D3DXCreateFontIndirect(lpDevice, &LogFont3, &pFont3);
if (rc != D3D_OK) UC_err("error > font it 3");
} 


void UC_UtilsDeleteFonts()
{
	if (pFont2 != NULL) 
		{pFont2->Release();pFont2=NULL;}
	if (pFont3 != NULL) 
		{pFont3->Release();pFont3=NULL;}
	if (pFont9 != NULL) 
		{pFont9->Release();pFont9=NULL;}
}

void UC_DrawLineCircle(LPDIRECT3DDEVICE8 lpDevice,
					   float centerX, float centerY,
					   float radius, int slices,
					   D3DCOLOR c)
{
float angle,deltaAngle,x,y,xx,yy;
angle=0;
x=centerX;
y=centerY-radius;
deltaAngle=360.0f/slices;
for (int i=0; i<slices; i++)
	{
    angle=i*deltaAngle; 
	rotatePoint(centerX, centerY-radius,
				centerX, centerY,
				(float)degToRad(angle),
				&xx,&yy);
    UC_DrawLine2D(lpDevice,(int)x,(int)y,(int)xx,(int)yy,c,c);
	x=xx; //remv
	y=yy; //remv
	}
UC_DrawLine2D(lpDevice,(int)x,(int)y,(int)centerX,(int)(centerY-radius),c,c);
}


//end

