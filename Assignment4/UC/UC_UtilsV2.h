#ifndef UC_Utils
#define UC_Utils
// utility and general purpose graphics routines 

#include "UC_surface.h"

#define UC_OPAQUE_BLACK 0xFF000000
#define UC_OPAQUE_WHITE 0xFFFFFFFF
#define UC_BLACK 0xFF000000
#define UC_WHITE 0xFFFFFFFF
#define UC_TRANS_BLACK  0x00000000
#define UC_TRANS_WHITE  0x00FFFFFF

#define UC_RED 0xFFFF0000
#define UC_BLUE 0xFF0000FF
#define UC_LBLUE 0xFF9090FF
#define UC_GREEN 0xFF00FF00
#define UC_GREY 0xFF7F7F7F
#define UC_GRAY 0xFF9F9F9F

#define UC_getAval(c) ((unsigned char) (c>>24) & 0xff)
#define UC_getRval(c) ((unsigned char) (c>>16) & 0xff)
#define UC_getGval(c) ((unsigned char) (c>>8) & 0xff)
#define UC_getBval(c) ((unsigned char) (c) & 0xff)



struct UC_rect
{
	float top,left,bottom,right;
};

struct UC_point
{
	float x,y;
};

struct UC_CustomVertex
{
    float x, y, z, rhw;
    float tu,tv;
};

struct UC_CustVertWColor
{
    FLOAT x, y, z, rhw;
    D3DCOLOR color;
};

void setUC_rect(UC_rect *r, float utop,float uleft, float ubottom, float uright);
void setUC_rectWH(UC_rect *r, float utop,float uleft, float uWidth, float uHeight);

void setUC_CustomVertex(UC_CustomVertex *v, float xx, float yy, 
             float uu, float vv);

void setUC_CustomVertexWcol(UC_CustVertWColor *v, float xx, float yy, D3DCOLOR col);

void BasicBlit(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top);

void BlitRect(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom);

void BlitRectTr(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom,
              bool trans);

void BlitRectOr(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float left, float top,
              float right, float bottom,
              bool trans, int orient);

void BlitPart(LPDIRECT3DDEVICE8 lpDevice,
              LPDIRECT3DTEXTURE8 lpSrc,
              float srcLeft, float srcTop,
              float srcRight, float srcBottom,
              float destLeft, float destTop,
              float destRight, float destBottom,
              bool trans);

void BlitFrame(LPDIRECT3DDEVICE8 lpDevice,
              UC_texture *tex,
              int frameNum, int NumofFrames,
              float destLeft, float destTop,
              float destRight, float destBottom,
              bool trans);

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
			  );

void UC_UtilsCreateFonts(LPDIRECT3DDEVICE8 lpDevice);
void UC_UtilsDeleteFonts();
void UC_DrawText(LPDIRECT3DDEVICE8 lpDevice, int x, int y, char *text, D3DCOLOR c);

void UC_DrawTextEx(LPDIRECT3DDEVICE8 lpDevice, int x, int y, char *text,
				   D3DCOLOR c, int style);

void UC_printf(LPDIRECT3DDEVICE8 lpDevice, float x, float y,
			   D3DCOLOR c, int style,
			   char* format, ...);

void UC_DrawTriangle2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   int x2, int y2,
					   D3DCOLOR c0,
					   D3DCOLOR c1,
					   D3DCOLOR c2
					   );

void UC_DrawLineQuad2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   int x2, int y2,
					   int x3, int y3,
					   D3DCOLOR c0,D3DCOLOR c1,
					   D3DCOLOR c2,D3DCOLOR c3);

void UC_DrawLineCircle(LPDIRECT3DDEVICE8 lpDevice,
					   float centerX, float centerY,
					   float radius, int slices,
					   D3DCOLOR c);

void UC_DrawLine2D(LPDIRECT3DDEVICE8 lpDevice,
					   int x0, int y0,
					   int x1, int y1,
					   D3DCOLOR c0,D3DCOLOR c1);

float dist(float x1, float y1, float x2, float y2);
double degToRad(double deg);
void UC_kill(void ** ptr);
void direct(double xx1,double yy1,double xx2,double yy2,double *angle,double *distz);
void Move2DInDir(float oldx, float oldz,
                 float yaw, float speed,
                 float *resultx, float *resultz);
void rotatePoint(float x, float y,
				 float centerX, float centerY,
				 float angleInRadians,
				 float *newx, float *newy);

bool isInRect(float x, float y, float t, float l, float b, float r);



// end
#endif