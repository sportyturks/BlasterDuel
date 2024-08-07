// UC_gui.cpp

#include <stdio.h>
#include <ctype.h>

#include "UC_main.h"
#include "UC_utilsV2.h"
#include "UC_gameClass.h"
#include "UC_surface.h"
#include "UC_gui.h"

// UC_GUIControl
bool UC_GUIControl::keyhit(WPARAM wParam) {return false;}
void UC_GUIControl::timerTick() {}
bool UC_GUIControl::mouseKlick(int newx, int newy){return false;}

bool UC_GUIControl::getFocus()
{
return focus;
}

void UC_GUIControl::setFocus(bool f)
{
focus=f;
}

bool UC_GUIControl::isIn(int x, int y)
{
// returns true if the point is in the control
if (x>=xpos &&
    y>=ypos &&
	y<=ypos+height &&
	x<=xpos+width) return true;
return false;
}

void UC_GUIControl::setBounds(int x, int y, int widthz, int heightz)
{
xpos=x;
ypos=y;
width=widthz;
height=heightz;	
}
void UC_GUIControl::setPos(int x, int y)
{
xpos=x;
ypos=y;
}

int UC_GUIControl::getX(){return xpos;}
int UC_GUIControl::getY(){return ypos;}
int UC_GUIControl::getW(){return width;}
int UC_GUIControl::getH(){return height;}

void UC_GUIControl::LoadBmp(char *fname,D3DCOLOR transColor, int alphaVal)
{
	if (tex !=NULL) delete tex;
	tex=new UC_texture(fname,D3DX_DEFAULT,D3DX_DEFAULT,transColor,alphaVal);
	if (height==0) height=tex->imageHeight;
	if (width==0) width=tex->imageWidth;
}

bool UC_GUIControl::getVisible()
{
	return visible;
}

void UC_GUIControl::setVisible(bool v)
{
	visible=v;
}

UC_GUIControl::UC_GUIControl(UC_GUIControl *parentz)
{
	tex=NULL;
	parent=parentz;
	xpos=0;
	ypos=0;
	width=0;
	height=0;
	focus=false;
}

UC_GUIControl::~UC_GUIControl()
{
	if (tex != NULL) delete tex;
	tex=NULL;
}


float UC_GUIControl::getAdjustX(int x)
{
	if (!parent) return (float)getX();
	return (float)(getX()+parent->getX());
}

float UC_GUIControl::getAdjustY(int y)
{
	if (!parent) return (float)getY();
	return (float)(getY()+parent->getY());
}

float UC_GUIControl::getAdjustX(){return getAdjustX(getX());}
float UC_GUIControl::getAdjustY(){return getAdjustY(getY());}

float UC_GUIControl::getRight() {return getAdjustX()+getW();}
float UC_GUIControl::getBottom(){return getAdjustY()+getH();}


// ----------------- UC_GUIFrame ------------------------------

bool UC_GUIFrame::keyhit(WPARAM wParam)
{
UC_GUIControl *c;
c=whoHasFocus();
if (c != NULL)
		{
		return c->keyhit(wParam);
		}
return false;
}

void UC_GUIFrame::timerTick()
{
// Should pass on timer ticks to allow animations
for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL)
		{
		if (controls[i]->getVisible())
			{
				controls[i]->timerTick();
			}
		}
	}
}

bool UC_GUIFrame::mouseKlick(int newx, int newy)
{
int xx,yy;
xx=newx-getX();
yy=newy-getY();
// xx,yy now adjusted mouse click pos

for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL)
		{
		if (controls[i]->getVisible())
			{
			if (controls[i]->isIn(xx,yy))
				{
					return controls[i]->mouseKlick(xx,yy);
				}
			}
		}
	}
return false;
}


void UC_GUIFrame::render()
{
if (tex!=NULL)
	{
	// blit the sucker
	BlitRectTr(g_pDirect3DDevice,
              tex->textureData,
              (float)getX(),(float)getY(),
              (float)(getX()+getW()), (float)(getY()+getH()),
              true);
	}

for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL)
		{
			if (controls[i]->getVisible()) controls[i]->render();
		}
	}
}


bool UC_GUIFrame::AddControl(UC_GUIControl *c)
{
for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]==NULL)
		{
		controls[i]=c;
		return true;
		}
	}
return false;
}

UC_GUIControl *UC_GUIFrame::whoHasFocus()
{
// could be NULL
for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL) 
		{
		if (controls[i]->getFocus()) return controls[i];
		}
	}
return NULL;
}

void UC_GUIFrame::unSetFocus()
{
	for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL) controls[i]->setFocus(false);
	}
}

bool UC_GUIFrame::RemoveControl(UC_GUIControl *c)
{
//NOTE: does not delete the control;
for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]==c)
		{
		controls[i]=NULL;
		return true;
		}
	}
return false;
}

void UC_GUIFrame::Clear()
{
UC_renderOFF();
for (int i=0; i<NUM_CONTROLS; i++)
	controls[i]=NULL;
UC_renderON();
}

void UC_GUIFrame::ClearAndDelete()
{
UC_renderOFF();
for (int i=0; i<NUM_CONTROLS; i++)
	{
	if (controls[i]!=NULL)
		{
		delete controls[i];
		controls[i]=NULL;
		}
	}
UC_renderON();
}

UC_GUIFrame::UC_GUIFrame()
:UC_GUIControl(NULL)
{
Clear();
}

UC_GUIFrame::~UC_GUIFrame()
{
}

// ------------ class UC_GUIButton ---------------------------

UC_GUIButton::UC_GUIButton(UC_GUIControl *parent)
:UC_GUIControl(parent)
{
}

UC_GUIButton::~UC_GUIButton()
{
delete tex;
}

void UC_GUIButton::render()
{
if (tex!=NULL)
	{
	// blit the sucker
	BlitRectTr(g_pDirect3DDevice,
              tex->textureData,
              getAdjustX(),getAdjustY(),
              getRight(), getBottom(),
              true);
	}

}

bool UC_GUIButton::keyhit(WPARAM wParam)
{
pressed(); // run the passed in function
return true;
}

bool UC_GUIButton::mouseKlick(int newx, int newy)
{
pressed(); // run the passed in function
return true;
}

// ------------------- UC_GUIEdit ---------------------

UC_GUIEdit::UC_GUIEdit(UC_GUIControl *parent):
UC_GUIControl(parent)
{
	text[0]=0;
	strcpy(allowed,"abcdefghijklmnopqrstuvwxyz 1234567890-+.ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_R = 0;
	m_G = 0;
	m_B = 0;
}

void UC_GUIEdit::render()
{
char t[256];

if (tex!=NULL)
	{
	// blit the sucker
	BlitRectTr(g_pDirect3DDevice,
              tex->textureData,
              getAdjustX(),getAdjustY(),
              getRight(), getBottom(),
              true);
	}

float xx,yy;
xx=getAdjustX()+16;
yy=getAdjustY()+8;

strcpy(t,text);
if (focus && timerTicks%10 < 5) strcat(t,"_"); 
UC_printf(g_pDirect3DDevice, xx, yy, D3DCOLOR_XRGB(m_R,m_G,m_B),0,t);
}

char * UC_GUIEdit::getText()
{
	return text;
}

void UC_GUIEdit::setText(char *textz)
{
	strcpy(text,textz);
}

void UC_GUIEdit::setText(int i)
{
sprintf(text,"%d",i);
}

void UC_GUIEdit::setMaxChars(int maxCh)
{
maxChars=maxCh;
}

void UC_GUIEdit::setAllowedChars(char *c)
{
strcpy(allowed,c);
}

bool UC_GUIEdit::keyhit(WPARAM wParam)
{
int l;
l=(int)strlen(text);
if (wParam == VK_BACK ||
	wParam == VK_DELETE)
    {
    if (l>0) text[l-1]=0;
	return true;
    }

char c;
if (l >= maxChars) return true;
c=(char)wParam;
if (strchr(allowed,c) == NULL) return true;
text[l]=c;
text[l+1]=0;
return true;
}

bool UC_GUIEdit::mouseKlick(int newx, int newy)
{
	((UC_GUIFrame*)parent)->unSetFocus();
	focus=true;
	return true;
}


//  -------- end ---------------