#ifndef UC_GUI_Z11
#define UC_GUI_Z11
// UC_GUI.h defines ALL gui classes

#include "UC_surface.h"

#define NUM_CONTROLS 100

class UC_GUIControl
{
protected:
int xpos,ypos,width,height;
bool focus; // true if have focus
bool visible;
UC_texture *tex;
UC_GUIControl *parent;

public:
// students must override these	
virtual void render()=0;

// students will probably want to override these
virtual bool keyhit(WPARAM wParam);
virtual void timerTick();
virtual bool mouseKlick(int newx, int newy); // return true if event is used

// these are genrealy usefull
bool isIn(int x, int y); // returns true if the point is in the control
void setBounds(int x, int y, int widthz, int heightz); 
void setPos(int x, int y); 
int getX();
int getY();
virtual int getW();
virtual int getH();
bool getFocus();
void setFocus(bool f);
bool getVisible();
void setVisible(bool v);

float getAdjustX(int x);
float getAdjustY(int y);

float getAdjustX();
float getAdjustY();

float getRight();
float getBottom();

void LoadBmp(char *fname,D3DCOLOR transColor, int alphaVal); 	

UC_GUIControl(UC_GUIControl *parentz);
~UC_GUIControl();
};


class UC_GUIFrame : public UC_GUIControl
{
public:
UC_GUIControl *controls[NUM_CONTROLS];

bool AddControl(UC_GUIControl *c);
bool RemoveControl(UC_GUIControl *c);
void Clear();
void ClearAndDelete();
void render();
void unSetFocus();
UC_GUIControl *whoHasFocus(); // could be NULL

virtual bool keyhit(WPARAM wParam);
virtual void timerTick();
virtual bool mouseKlick(int newx, int newy);

UC_GUIFrame();
~UC_GUIFrame();

};

class UC_GUIButton : public UC_GUIControl
{
public:
UC_GUIButton(UC_GUIControl *parent);
~UC_GUIButton();

virtual void render();
virtual void pressed()=0;
virtual bool keyhit(WPARAM wParam);
virtual bool mouseKlick(int newx, int newy);
};

class UC_GUIEdit : public UC_GUIControl
{
public:
char text[255];
char allowed[257];
int m_R, m_G, m_B;
int maxChars;

UC_GUIEdit(UC_GUIControl *parent);

void setMaxChars(int maxCh);
void setAllowedChars(char *c);

virtual void render();
virtual char * getText();
virtual void setText(char *textz);
virtual void setText(int i);
virtual bool keyhit(WPARAM wParam);
virtual bool mouseKlick(int newx, int newy);
};


// end
#endif