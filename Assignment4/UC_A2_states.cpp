// UC_A2_states.cpp

#include <dinput.h>
#include "UC_main.h"
#include "UC_A2_states.h"
#include "UC_UtilsV2.h"
#include "UC_A2_gameCode.h"
#include "UC_dir.h"
#include "myclass.h"

void state1_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	if (boolState1a)
		BasicBlit(g_pDirect3DDevice, texState1a->textureData, 0.0, 0.0);	//rc = g_pDirect3DDevice->CopyRects(texState1a->bitmapData,NULL,0,pBackBuffer,NULL);
	else
	{
		if (boolState1b)
			BasicBlit(g_pDirect3DDevice, texState1b->textureData, 0.0, 0.0); 
		else
			BasicBlit(g_pDirect3DDevice, texState1c->textureData, 0.0, 0.0); 
	}

	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	if (pBackBuffer)
			pBackBuffer->Release();
}

void state1_class::init()
{
	texState1a = new UC_texture(getFileName("JDTPresent.bmp"), 1024, 1024, D3DCOLOR_XRGB(0,0,0));
	texState1b = new UC_texture(getFileName("JDTPresent.bmp"), 1024, 1024, D3DCOLOR_XRGB(0,0,0));
	texState1c = new UC_texture(getFileName("blasterDuel.bmp"), 1024, 1024, D3DCOLOR_XRGB(0,0,0));
	boolState1a = true;
	boolState1b = false;
	ticksElapsed=0;
}

void state1_class::cleanUp()
{
	delete texState1a;
	delete texState1b;
	delete texState1c;
}

void state1_class::timerTick()
{
	ticksElapsed++;
	//st->transitTo(2);
	if (ticksElapsed >= 60 && ticksElapsed < 120)
	{
		boolState1a = false;
		boolState1b = true;
	}
	else
	{
		if (ticksElapsed >= 120 && ticksElapsed < 180)
			boolState1b = false;
		else if (ticksElapsed >= 180)
			st->transitTo(2);
	}
}

// ---------- state 2 below ------------------
state2_class::state2_class()
{
}
void state2_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	
	if (help)
	{
		BasicBlit(g_pDirect3DDevice, texState2b->textureData, 0, 0);
		guiFrame2->render();
	}
	else
	{
		BasicBlit(g_pDirect3DDevice, texState2->textureData, 0, 0);
		guiFrame->render();
	}

	if(mouseAquired)
		BlitPart(g_pDirect3DDevice, texCursor->textureData, 0, 0, 32, 32, mouseX, mouseY, mouseX + 32, mouseY + 32, true);

	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

	if (pBackBuffer)
        pBackBuffer->Release();
}

void state2_class::init()
{
	texState2 = new UC_texture(getFileName("interface.bmp"),1024, 768, D3DCOLOR_XRGB(0, 0, 0));
	texState2b = new UC_texture(getFileName("help.bmp"),1024, 768, D3DCOLOR_XRGB(0, 0, 0));
	texCursor = new UC_texture(getFileName("cursor.bmp"), 32, 32, D3DCOLOR_XRGB(0, 0, 0));
	//showGui=false;
	UC_initDImouse();

	guiFrame=new UC_GUIFrame();
	guiFrame->LoadBmp(getFileName("frame.bmp"),UC_OPAQUE_BLACK,128);
	guiFrame->setBounds(0,0,1024,768);

	b=new myButton(guiFrame);
	b->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	b->setPos(275,213);
	guiFrame->AddControl(b);
	
	c=new myButton(guiFrame);
	c->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	c->setPos(275,308);
	guiFrame->AddControl(c);

	e=new myButton(guiFrame);
	e->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	e->setPos(275,403);
	guiFrame->AddControl(e);

	f=new myButton(guiFrame);
	f->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	f->setPos(275,498);
	guiFrame->AddControl(f);

	guiFrame2=new UC_GUIFrame();
	guiFrame2->LoadBmp(getFileName("frame.bmp"),UC_OPAQUE_BLACK,128);
	guiFrame2->setBounds(0,0,1024,768);

	back=new myButton(guiFrame);
	back->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	back->setPos(270,630);
	guiFrame->AddControl(back);

    mouseX = 300;
	mouseY = 300;

	help = false;

	intro = new UC_CWave(getFileName("intro.wav"));
	intro->play();
}

void state2_class::cleanUp()
{
	delete texState2;
	delete texState2b;
	delete texCursor;
	delete guiFrame;
	delete guiFrame2;
	intro->stop();
	delete intro;
}

void state2_class::keyhit(WPARAM wParam)
{
	if (wParam=='s' || wParam=='S') 
		{
			st->transitTo(3);
		}
	if (wParam=='p' || wParam=='P') 
		{
			st->transitTo(4);
		}
	if (wParam=='q' || wParam=='Q') 
			PostQuitMessage(WM_QUIT);
	if (wParam=='r' || wParam=='R') 
			help = false;
	if (wParam == VK_F1)
		help = !help;

}

void state2_class::timerTick()
{
	checkMouse();
}
void state2_class::doIt()
{
	if (help == false)
	{
		if (mouseY <= 270 && mouseY >=215)
			st->transitTo(4);
		else if (mouseY <= 360 && mouseY >= 310)
			st->transitTo(3);
		else if (mouseY <= 450 && mouseY >= 400)
			help = true;
		else if (mouseY <= 550 && mouseY >= 500)
			PostQuitMessage(WM_QUIT);
	}
	else
	{
		if (mouseY <=710  && mouseY >= 630)
			help = false;
	}
}
void state2_class::checkMouse()
{
	DIMOUSESTATE2 ms;
	HRESULT rc;

	if (!mouseAquired) return;

	rc=g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&ms);
	if (FAILED(rc))
	{
		UC_err("ERROR> The mouse is not working");
		UC_unaquireMouse();
	}

	mouseX=mouseX+ms.lX;
	mouseY=mouseY+ms.lY;
	if (mouseX<0) mouseX=0;
	if (mouseY<0) mouseY=0;
	if (mouseX>=1024) mouseX=1024-1;
	if (mouseY>=768) mouseY=768-1;

	if (prevButtonState !=0 && prevButtonState == ms.rgbButtons[0]) return;
	prevButtonState = ms.rgbButtons[0];

	if (ms.rgbButtons[0] != 0)
	{
		if ( guiFrame->isIn((int)mouseX,(int)mouseY))
		{
			bool rc;
			rc=guiFrame->mouseKlick((int)mouseX,(int)mouseY);
			if (rc) return;
		}
	}

	if (ms.rgbButtons[1] != 0)
	{
		UC_unaquireMouse();
	}
}
//STATE 3 BELOW -  Settings Menu
state3_class::state3_class()
{
}
void state3_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	BlitPart(g_pDirect3DDevice, texState3->textureData, 0, 0, 1024, 768, 0, 0, 1024, 768, false);

	guiFrame->render();

	if(mouseAquired)
		BlitPart(g_pDirect3DDevice, texCursor->textureData, 0, 0, 32, 32, mouseX, mouseY, mouseX + 32, mouseY + 32, true);

	UC_printf(g_pDirect3DDevice, 515, 266, D3DCOLOR_XRGB(255,255,0),3,"%d",die);
	UC_printf(g_pDirect3DDevice, 515, 345, D3DCOLOR_XRGB(255,255,0),3,"%d",kill);
	UC_printf(g_pDirect3DDevice, 515, 425, D3DCOLOR_XRGB(255,255,0),3,"%d",round);
	UC_printf(g_pDirect3DDevice, 515, 500, D3DCOLOR_XRGB(255,255,0),3,"%d",league);

	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

	if (pBackBuffer)
        pBackBuffer->Release();
}

void state3_class::init()
{
	texState3 = new UC_texture(getFileName("settings.bmp"),1024, 768, D3DCOLOR_XRGB(0, 0, 0));
	texCursor = new UC_texture(getFileName("cursor.bmp"), 32, 32, D3DCOLOR_XRGB(0, 0, 0));

	guiFrame=new UC_GUIFrame();
	guiFrame->LoadBmp(getFileName("frame2.bmp"),UC_OPAQUE_BLACK,0);
	guiFrame->setBounds(0,0,1024,768);

	back = new myButton(guiFrame);
	back->LoadBmp(getFileName("black.bmp"),UC_OPAQUE_BLACK,160);
	back->setPos(275,530);
	guiFrame->AddControl(back);

	upA = new myButton(guiFrame);
	upA->LoadBmp(getFileName("up.bmp"),UC_OPAQUE_BLACK,160);
	upA->setPos(450,250);
	guiFrame->AddControl(upA);

	downA = new myButton(guiFrame);
	downA->LoadBmp(getFileName("down.bmp"),UC_OPAQUE_BLACK,160);
	downA->setPos(575,250);
	guiFrame->AddControl(downA);

	upB = new myButton(guiFrame);
	upB->LoadBmp(getFileName("up.bmp"),UC_OPAQUE_BLACK,160);
	upB->setPos(450,329);
	guiFrame->AddControl(upB);

	downB = new myButton(guiFrame);
	downB->LoadBmp(getFileName("down.bmp"),UC_OPAQUE_BLACK,160);
	downB->setPos(575,329);
	guiFrame->AddControl(downB);

	upC = new myButton(guiFrame);
	upC->LoadBmp(getFileName("up.bmp"),UC_OPAQUE_BLACK,160);
	upC->setPos(450,409);
	guiFrame->AddControl(upC);

	downC = new myButton(guiFrame);
	downC->LoadBmp(getFileName("down.bmp"),UC_OPAQUE_BLACK,160);
	downC->setPos(575,409);
	guiFrame->AddControl(downC);

	upD = new myButton(guiFrame);
	upD->LoadBmp(getFileName("up.bmp"),UC_OPAQUE_BLACK,160);
	upD->setPos(450,484);
	guiFrame->AddControl(upD);

	downD = new myButton(guiFrame);
	downD->LoadBmp(getFileName("down.bmp"),UC_OPAQUE_BLACK,160);
	downD->setPos(575,484);
	guiFrame->AddControl(downD);

	intro = new UC_CWave(getFileName("intro.wav"));
	intro->play();

	mouseX = 300;
	mouseY = 300;
	UC_initDImouse();
}

void state3_class::cleanUp()
{
	delete texState3;
	delete texCursor;
	intro->stop();
	delete intro;
}

void state3_class::timerTick()
{
	checkMouse();
}

void  state3_class::keyhit(WPARAM wParam)
{
		if (wParam=='r' || wParam=='R') 
			st->transitTo(2);
}
void state3_class::checkMouse()
{
	DIMOUSESTATE2 ms;
	HRESULT rc;

	if (!mouseAquired) return;

	rc=g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&ms);
	if (FAILED(rc))
	{
		UC_err("ERROR> The mouse is not working");
		UC_unaquireMouse();
	}

	mouseX=mouseX+ms.lX;
	mouseY=mouseY+ms.lY;
	if (mouseX<0) mouseX=0;
	if (mouseY<0) mouseY=0;
	if (mouseX>=1024) mouseX=1024-1;
	if (mouseY>=768) mouseY=768-1;

	if (prevButtonState !=0 && prevButtonState == ms.rgbButtons[0]) return;
	prevButtonState = ms.rgbButtons[0];

	if (ms.rgbButtons[0] != 0)
	{
		if ( guiFrame->isIn((int)mouseX,(int)mouseY))
		{
			bool rc;
			rc=guiFrame->mouseKlick((int)mouseX,(int)mouseY);
			if (rc) return;
		}
	}

	if (ms.rgbButtons[1] != 0)
	{
		UC_unaquireMouse();
	}
}
void state3_class::doIt()
{
		if (mouseY <= 594 && mouseY >=530)
			st->transitTo(2);
		else if (mouseX>= 450 && mouseX<=482 && mouseY >= 250 && mouseY < 282)
		{
			if (die >= 5)
				die = 5;
			else
				die++;
		}
		else if (mouseX>= 575 && mouseX<=607 && mouseY >= 250 && mouseY <282)
		{
			if (die <=0)
				die =0;
			else
				die--;
		}
		else if (mouseX>= 450 && mouseX<=482 && mouseY >= 329 && mouseY < 361)
		{
			if (kill >= 5)
				kill = 5;
			else
				kill++;
		}
		else if (mouseX>= 575 && mouseX<=607 && mouseY >= 329 && mouseY < 361)
		{
			if (kill <=1)
				kill =1;
			else
				kill--;
		}
		else if (mouseX>= 450 && mouseX<=482 && mouseY >= 409 && mouseY < 431)
		{
			if (round >= 99)
				 round = 99;
			else
				round++;
		}
		else if (mouseX>= 575 && mouseX<=607 && mouseY >= 409 && mouseY < 431)
		{
			if (round <=5)
				round =5;
			else
				round--;
		}
		else if (mouseX>= 450 && mouseX<=482 && mouseY >= 484 && mouseY <= 516)
		{
			if (league >= 99)
				league = 99;
			else
				league++;
		}
		else if (mouseX>= 575 && mouseX<=607 && mouseY >= 484 && mouseY <=516)
		{
			if (league <=1)
				league = 1;
			else
				league--;
		}
}

// ------------------ state4 -----------------------
state4_class::state4_class()
{
}
void state4_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	
	if (displayPress && internalState == 0)
		UC_printf(g_pDirect3DDevice, 170, 186, D3DCOLOR_XRGB(255,0,0),3,"1UP Press Start");
	else if (internalState == 1)
	{
		BigBlitRotate(g_pDirect3DDevice, texShipEnabled, (float) 171*(currentShipNo-1),  (float) 0, (float) currentShipNo*171,  (float) 128, (float) 171, (float) 0, (float) 343, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledLeft, (float) 171*(previousShipNo-1),  (float) 0, (float) previousShipNo*171,  (float) 128, (float) 0, (float) 0, (float) 171*1, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledRight, (float) 171*(nextShipNo-1),  (float) 0, (float) nextShipNo*171,  (float) 128, (float) 342, (float) 0, (float) 512, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		
		if (currentShipNo == 1)
			BlitPart(g_pDirect3DDevice, texAwing1->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);
		else if (currentShipNo == 2)
			BlitPart(g_pDirect3DDevice, texXwing2->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);
		else if (currentShipNo == 3)
			BlitPart(g_pDirect3DDevice, texFalcon3->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);
		else if (currentShipNo == 4)
			BlitPart(g_pDirect3DDevice, texTie4->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);	
		else if (currentShipNo == 5)
			BlitPart(g_pDirect3DDevice, texBTie5->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);	
		else if (currentShipNo == 6)
			BlitPart(g_pDirect3DDevice, texNTie6->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);	
		else 
			BlitPart(g_pDirect3DDevice, texShuttle7->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171, (float) 512, (float) 384, false);	
	}
	else if (internalState == 2)
	{
		if (currentShipNo == 1)
		{
			BlitPart(g_pDirect3DDevice, texSelectedAwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 1;
		}
		else if (currentShipNo == 2)
		{
			BlitPart(g_pDirect3DDevice, texSelectedXwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 2;
		}
		else if (currentShipNo == 3)
		{
			BlitPart(g_pDirect3DDevice, texSelectedFalcon->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 3;
		}
		else if (currentShipNo == 4)
		{
			BlitPart(g_pDirect3DDevice, texSelectedTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 4;
		}
		else if (currentShipNo == 5)
		{
			BlitPart(g_pDirect3DDevice, texSelectedBTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 5;

		}
		else if (currentShipNo == 6)
		{
			BlitPart(g_pDirect3DDevice, texSelectedNTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 6;
		}
		else //(currentShipNo == 7)
		{
			BlitPart(g_pDirect3DDevice, texSelectedShuttle->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0, (float) 512, (float) 384, true);
			results[0].playerNo = 1;
			results[0].selected = true;
			results[0].selectedShip = 7;
		}
		guiFrame->render();
	}

	if (displayPress && internalState2 == 0)
		UC_printf(g_pDirect3DDevice, 682, 186, D3DCOLOR_XRGB(0,255,0),3,"2UP Press Start");
	else if (internalState2 == 1)
	{
		BigBlitRotate(g_pDirect3DDevice, texShipEnabled, (float) 171*(currentShipNo2-1),  (float) 0, (float) currentShipNo2*171,  (float) 128, (float) 171+512, (float) 0, (float) 343+512, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledLeft, (float) 171*(previousShipNo2-1),  (float) 0, (float) previousShipNo2*171,  (float) 128, (float) 0+512, (float) 0, (float) 171*1 + 512, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledRight, (float) 171*(nextShipNo2-1),  (float) 0, (float) nextShipNo2*171,  (float) 128, (float) 342+512, (float) 0, (float) 512+512, (float) 128, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);

		if (currentShipNo2 == 1)
			BlitPart(g_pDirect3DDevice, texAwing1->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);
		else if (currentShipNo2 == 2)
			BlitPart(g_pDirect3DDevice, texXwing2->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);
		else if (currentShipNo2 == 3)
			BlitPart(g_pDirect3DDevice, texFalcon3->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);
		else if (currentShipNo2 == 4)
			BlitPart(g_pDirect3DDevice, texTie4->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);	
		else if (currentShipNo2 == 5)
			BlitPart(g_pDirect3DDevice, texBTie5->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);	
		else if (currentShipNo2 == 6)
			BlitPart(g_pDirect3DDevice, texNTie6->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);	
		else 
			BlitPart(g_pDirect3DDevice, texShuttle7->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171, (float) 512+512, (float) 384, false);	
	}
	else if (internalState2 == 2)
	{
		if (currentShipNo2 == 1)
		{
			BlitPart(g_pDirect3DDevice, texSelectedAwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 1;
		}
		else if (currentShipNo2 == 2)
		{
			BlitPart(g_pDirect3DDevice, texSelectedXwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 2;
		}
		else if (currentShipNo2 == 3)
		{
			BlitPart(g_pDirect3DDevice, texSelectedFalcon->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 3;
		}
		else if (currentShipNo2 == 4)
		{
			BlitPart(g_pDirect3DDevice, texSelectedTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 4;
		}
		else if (currentShipNo2 == 5)
		{
			BlitPart(g_pDirect3DDevice, texSelectedBTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 5;

		}
		else if (currentShipNo2 == 6)
		{
			BlitPart(g_pDirect3DDevice, texSelectedNTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 6;
		}
		else //(currentShipNo == 7)
		{
			BlitPart(g_pDirect3DDevice, texSelectedShuttle->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 512, (float) 0, (float) 1024, (float) 384, true);
			results[1].playerNo = 2;
			results[1].selected = true;
			results[1].selectedShip = 7;
		}
		guiFrame2->render();
	}

	if (displayPress && internalState3 == 0)
		UC_printf(g_pDirect3DDevice, 170, 186+384, D3DCOLOR_XRGB(255,255,0),3,"3UP Press Start");
	else if (internalState3 == 1)
	{
		BigBlitRotate(g_pDirect3DDevice, texShipEnabled, (float) 171*(currentShipNo3-1),  (float) 0, (float) currentShipNo3*171,  (float) 128, (float) 171, (float) 0+384, (float) 343, (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledLeft, (float) 171*(previousShipNo3-1),  (float) 0, (float) previousShipNo3*171,  (float) 128, (float) 0, (float) 0+384, (float) 171*1, (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledRight, (float) 171*(nextShipNo3-1),  (float) 0, (float) nextShipNo3*171,  (float) 128, (float) 342, (float) 0+384, (float) 512, (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		
		if (currentShipNo3 == 1)
			BlitPart(g_pDirect3DDevice, texAwing1->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);
		else if (currentShipNo3 == 2)
			BlitPart(g_pDirect3DDevice, texXwing2->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);
		else if (currentShipNo3 == 3)
			BlitPart(g_pDirect3DDevice, texFalcon3->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);
		else if (currentShipNo3 == 4)
			BlitPart(g_pDirect3DDevice, texTie4->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);	
		else if (currentShipNo3 == 5)
			BlitPart(g_pDirect3DDevice, texBTie5->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);	
		else if (currentShipNo3 == 6)
			BlitPart(g_pDirect3DDevice, texNTie6->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);	
		else 
			BlitPart(g_pDirect3DDevice, texShuttle7->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0, (float) 171+384, (float) 512, (float) 384+384, false);	
	}
	else if (internalState3 == 2)
	{
		if (currentShipNo3 == 1)
		{
			BlitPart(g_pDirect3DDevice, texSelectedAwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 1;
		}
		else if (currentShipNo3 == 2)
		{
			BlitPart(g_pDirect3DDevice, texSelectedXwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 2;
		}
		else if (currentShipNo3 == 3)
		{
			BlitPart(g_pDirect3DDevice, texSelectedFalcon->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 3;
		}
		else if (currentShipNo3 == 4)
		{
			BlitPart(g_pDirect3DDevice, texSelectedTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 4;
		}
		else if (currentShipNo3 == 5)
		{
			BlitPart(g_pDirect3DDevice, texSelectedBTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 5;

		}
		else if (currentShipNo3 == 6)
		{
			BlitPart(g_pDirect3DDevice, texSelectedNTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 6;
		}
		else //(currentShipNo == 7)
		{
			BlitPart(g_pDirect3DDevice, texSelectedShuttle->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0, (float) 0+384, (float) 512, (float) 384+384, true);
			results[2].playerNo = 3;
			results[2].selected = true;
			results[2].selectedShip = 7;
		}
		guiFrame3->render();
	}

	if (displayPress && internalState4 == 0)
		UC_printf(g_pDirect3DDevice, 170+512, 186+384, D3DCOLOR_XRGB(0,0,255),3,"4UP Press Start");
	else if (internalState4 == 1)
	{
		BigBlitRotate(g_pDirect3DDevice, texShipEnabled, (float) 171*(currentShipNo4-1),  (float) 0, (float) currentShipNo4*171,  (float) 128, (float) 171+512, (float) 0+384, (float) 343+512, (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledLeft, (float) 171*(previousShipNo4-1),  (float) 0, (float) previousShipNo4*171,  (float) 128, (float) 0+512, (float) 0+384, (float) 171*1 +512 , (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		BigBlitRotate(g_pDirect3DDevice, texShipDisabledRight, (float) 171*(nextShipNo4-1),  (float) 0, (float) nextShipNo4*171,  (float) 128, (float) 342+512, (float) 0+384, (float) 512+512, (float) 128+384, true, 0, (float)86, (float) 64,  (float) 0, NULL, NULL, false);
		
		if (currentShipNo4 == 1)
			BlitPart(g_pDirect3DDevice, texAwing1->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);
		else if (currentShipNo4 == 2)
			BlitPart(g_pDirect3DDevice, texXwing2->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);
		else if (currentShipNo4 == 3)
			BlitPart(g_pDirect3DDevice, texFalcon3->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);
		else if (currentShipNo4 == 4)
			BlitPart(g_pDirect3DDevice, texTie4->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);	
		else if (currentShipNo4 == 5)
			BlitPart(g_pDirect3DDevice, texBTie5->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);	
		else if (currentShipNo4 == 6)
			BlitPart(g_pDirect3DDevice, texNTie6->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);	
		else 
			BlitPart(g_pDirect3DDevice, texShuttle7->textureData, (float) 0,  (float) 0, (float) 512,  213, (float) 0+512, (float) 171+384, (float) 512+512, (float) 384+384, false);	
	}
	else if (internalState4 == 2)
	{
		if (currentShipNo4 == 1)
		{
			BlitPart(g_pDirect3DDevice, texSelectedAwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 1;
		}
		else if (currentShipNo4 == 2)
		{
			BlitPart(g_pDirect3DDevice, texSelectedXwing->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 2;
		}
		else if (currentShipNo4 == 3)
		{
			BlitPart(g_pDirect3DDevice, texSelectedFalcon->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 3;
		}
		else if (currentShipNo4 == 4)
		{
			BlitPart(g_pDirect3DDevice, texSelectedTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 4;
		}
		else if (currentShipNo4 == 5)
		{
			BlitPart(g_pDirect3DDevice, texSelectedBTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 5;

		}
		else if (currentShipNo4 == 6)
		{
			BlitPart(g_pDirect3DDevice, texSelectedNTie->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 6;
		}
		else //(currentShipNo == 7)
		{
			BlitPart(g_pDirect3DDevice, texSelectedShuttle->textureData, (float) 0,  (float) 0, (float) 512,  384, (float) 0+512, (float) 0+384, (float) 512+512, (float) 384+384, true);
			results[3].playerNo = 4;
			results[3].selected = true;
			results[3].selectedShip = 7;
		}
		guiFrame4->render();
	}

	if (internalState4 == 3)
		UC_printf(g_pDirect3DDevice, 170+512, 186+384, D3DCOLOR_XRGB(0,0,255),3,"%s is ready!", results[3].pilotName);
	if (internalState3 == 3)
		UC_printf(g_pDirect3DDevice, 170, 186+384, D3DCOLOR_XRGB(255,255,0),3,"%s is ready!", results[2].pilotName);
	if (internalState2 == 3)
		UC_printf(g_pDirect3DDevice, 682, 186, D3DCOLOR_XRGB(0,255,0),3,"%s is ready!", results[1].pilotName);
	if (internalState == 3)
		UC_printf(g_pDirect3DDevice, 170, 186, D3DCOLOR_XRGB(255,0,0),3,"%s is ready!", results[0].pilotName);

	//if (displayPress)
	//{
	//	UC_printf(g_pDirect3DDevice, 682, 186, D3DCOLOR_XRGB(255,0,0),3,"2UP Press Start");
	//	UC_printf(g_pDirect3DDevice, 170, 570, D3DCOLOR_XRGB(255,255,0),3,"3UP Press Start");
	//	UC_printf(g_pDirect3DDevice, 682, 570, D3DCOLOR_XRGB(0,0,255),3,"4UP Press Start");
	//}
	
	UC_DrawLine2D(g_pDirect3DDevice, 512, 0, 512, 768 ,UC_BLUE,UC_BLUE);
   	UC_DrawLine2D(g_pDirect3DDevice,0,384, 1024, 384 ,UC_BLUE,UC_BLUE);
	
	BlitPart(g_pDirect3DDevice, texReady->textureData, 0.0, 0.0, 320.0, 64.0, 360.0, 352, 680.0, 416.0, false);
	//buttonFrame->render();

	if(mouseAquired)
	{
		/*UC_DrawLine2D(g_pDirect3DDevice,(int)(mouseX-5),(int)(mouseY),(int)(mouseX+5), (int)(mouseY),UC_BLUE,UC_BLUE);
   		UC_DrawLine2D(g_pDirect3DDevice,(int)(mouseX),(int)(mouseY-5),(int)(mouseX), (int)(mouseY+5),UC_BLUE,UC_BLUE);*/
		BlitPart(g_pDirect3DDevice, texCursor->textureData, 0, 0, 32, 32, mouseX, mouseY, mouseX + 32, mouseY + 32, true);
	}
	
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

	if (pBackBuffer)
        pBackBuffer->Release();
}

void state4_class::init()
{
	displayPress = true;
	boolReady = false;
	countTicks = 0;
	mouseX = 300;
	mouseY = 300;
	UC_initDImouse();
	internalState = 0;
	internalState2 = 0;
	internalState3 = 0;
	internalState4 = 0;
	
	texShipEnabled = new UC_texture(getFileName("7ShipsEnabled.jpg"),2048, 128, D3DCOLOR_XRGB(0, 0, 0));
	texShipDisabledLeft = new UC_texture(getFileName("7ShipsDisabled.jpg"),2048, 128, D3DCOLOR_XRGB(0, 0, 0));
	texShipDisabledRight = new UC_texture(getFileName("7ShipsDisabled.jpg"),2048, 128, D3DCOLOR_XRGB(0, 0, 0));
	texReady = new UC_texture(getFileName("space.bmp"), 512, 64, NULL, 255);
	texCursor = new UC_texture(getFileName("cursor.bmp"), 32, 32, D3DCOLOR_XRGB(0, 0, 0));

	texSelectedAwing = new UC_texture(getFileName("SelectedAwing.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedXwing = new UC_texture(getFileName("SelectedXwing.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedNTie = new UC_texture(getFileName("SelectedNTie.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedBTie = new UC_texture(getFileName("SelectedBTie.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedTie = new UC_texture(getFileName("SelectedTie.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedFalcon = new UC_texture(getFileName("SelectedFalcon.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));
	texSelectedShuttle = new UC_texture(getFileName("SelectedShuttle.jpg"), 512, 512, D3DCOLOR_XRGB(0, 0, 0));

	texAwing1 = new UC_texture(getFileName("Awing1.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texXwing2 = new UC_texture(getFileName("Xwing2.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texFalcon3 = new UC_texture(getFileName("Solo3.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texTie4 = new UC_texture(getFileName("Tie4.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texBTie5 = new UC_texture(getFileName("BTie5.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texNTie6 = new UC_texture(getFileName("NTie6.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));
	texShuttle7 = new UC_texture(getFileName("Shuttle7.jpg"), 512, 256, D3DCOLOR_XRGB(0, 0, 0));

	currentShipNo = 1;
	previousShipNo = 7;
	nextShipNo = 2;

	guiFrame=new UC_GUIFrame();
	guiFrame->LoadBmp(getFileName("frame1.bmp"),UC_OPAQUE_BLACK,0);
	guiFrame->setBounds(0,0,512,384);

	pilotName = new UC_GUIEdit(guiFrame);
	pilotName->LoadBmp(getFileName("edit1.bmp"),UC_OPAQUE_BLACK,150);
	pilotName->setBounds(135 ,100 + 100,256,32);
	guiFrame->AddControl(pilotName);
	pilotName->setFocus(true);
	pilotName->setMaxChars(24);
	pilotName->setText("PLAYER1");
	pilotName->m_R = 255;
	pilotName->m_G = 0;
	pilotName->m_B = 0;

	currentShipNo2 = 1;
	previousShipNo2 = 7;
	nextShipNo2 = 2;

	guiFrame2=new UC_GUIFrame();
	guiFrame2->LoadBmp(getFileName("frame1.bmp"),UC_OPAQUE_BLACK,0);
	guiFrame2->setBounds(512,0,1024,384);

	pilotName2 = new UC_GUIEdit(guiFrame2);
	pilotName2->LoadBmp(getFileName("edit1.bmp"),UC_OPAQUE_BLACK,150);
	pilotName2->setBounds(135 ,100 + 100,256,32);
	guiFrame2->AddControl(pilotName2);
	pilotName2->setFocus(true);
	pilotName2->setMaxChars(24);
	pilotName2->setText("PLAYER2");
	pilotName2->m_R = 0;
	pilotName2->m_G = 255;
	pilotName2->m_B = 0;

	currentShipNo3 = 1;
	previousShipNo3 = 7;
	nextShipNo3 = 2;

	guiFrame3 = new UC_GUIFrame();
	guiFrame3->LoadBmp(getFileName("frame1.bmp"),UC_OPAQUE_BLACK,0);
	guiFrame3->setBounds(0,384,512,384);

	pilotName3 = new UC_GUIEdit(guiFrame3);
	pilotName3->LoadBmp(getFileName("edit1.bmp"),UC_OPAQUE_BLACK,150);
	pilotName3->setBounds(135 ,100 + 100,256,32);
	guiFrame3->AddControl(pilotName3);
	pilotName3->setFocus(true);
	pilotName3->setMaxChars(24);
	pilotName3->setText("PLAYER3");
	pilotName3->m_R = 255;
	pilotName3->m_G = 255;
	pilotName3->m_B = 0;

	currentShipNo4 = 1;
	previousShipNo4 = 7;
	nextShipNo4= 2;

	guiFrame4=new UC_GUIFrame();
	guiFrame4->LoadBmp(getFileName("frame1.bmp"),UC_OPAQUE_BLACK,0);
	guiFrame4->setBounds(512,384,1024,768);

	pilotName4 = new UC_GUIEdit(guiFrame4);
	pilotName4->LoadBmp(getFileName("edit1.bmp"),UC_OPAQUE_BLACK,150);
	pilotName4->setBounds(135 ,100 + 100,256,32);
	guiFrame4->AddControl(pilotName4);
	pilotName4->setFocus(true);
	pilotName4->setMaxChars(24);
	pilotName4->setText("PLAYER4");
	pilotName4->m_R = 0;
	pilotName4->m_G = 0;
	pilotName4->m_B = 255;

	setPilots();

	electroBang = new UC_CWave(getFileName("electroBang.wav"));
	duel = new UC_CWave(getFileName("duelOfTheFates.wav"));
	duel->play_looping();
}

void state4_class::cleanUp()
{
		delete texShipEnabled;
		delete texShipDisabledLeft;
		delete texShipDisabledRight;

		delete texSelectedAwing;
		delete texReady;
		delete texCursor;
		delete texSelectedXwing;
		delete texSelectedFalcon;
		delete texSelectedTie;
		delete texSelectedNTie;
		delete texSelectedBTie;
		delete texSelectedShuttle;

		delete texAwing1;
		delete texXwing2;
		delete texFalcon3;
		delete texTie4;
		delete texBTie5;
		delete texNTie6;
		delete texShuttle7;
		
		delete guiFrame;
		delete pilotName;

		delete guiFrame2;
		delete pilotName2;

		delete guiFrame3;
		delete pilotName3;

		delete guiFrame4;
		delete pilotName4;
		
		electroBang->stop();
		delete electroBang;

		duel->stop();
		delete duel;
}

void state4_class::timerTick()
{
	countTicks ++;
	checkMouse();
	if (countTicks%20==0)
		displayPress = !displayPress;
	if (boolReady)
		st->transitTo(5);
}

void  state4_class::keyhit(WPARAM wParam)
{
	if (wParam=='q' || wParam=='Q') 
		st->transitTo(2);
	else if (internalState == 2 && wParam != VK_DOWN)
	{
		if (wParam == VK_RETURN)
		{ 
			strcpy(results[0].pilotName, pilotName->text);
			internalState++;
			electroBang->play();
		}
		else
		{
			bool rc; 
			rc=guiFrame->keyhit(wParam);
			if (rc) return; // key hit consumed
		}
	}	
	else if (internalState2 == 2 && (wParam != 's' || wParam != 'S'))
	{
		if (wParam == VK_RETURN)
		{ 
			strcpy(results[1].pilotName, pilotName2->text);
			internalState2++;
			electroBang->play();
		}
		else
		{
			bool rc;
			rc=guiFrame2->keyhit(wParam);
			if (rc) return; // key hit consumed
		}
	}	
	else if (internalState3 == 2 && (wParam != 'h' || wParam != 'H'))
	{
		//this->guiFrame->setFocus(false);
		//this->pilotName->setFocus(false);
		//this->guiFrame2->setFocus(false);
		//this->pilotName2->setFocus(false);
		//this->guiFrame3->setFocus(true);
		//this->guiFrame3->setFocus(true);
		//this->pilotName3->setFocus(true);
		if (wParam == VK_RETURN)
		{ 
			strcpy(results[2].pilotName, pilotName3->text);
			internalState3++;
			electroBang->play();
		}
		else
		{
			bool rc; 
			rc=guiFrame3->keyhit(wParam);
			if (rc) return; // key hit consumed
		}
	}	
	else if (internalState4 == 2 && (wParam != VK_RSHIFT))
	{
		if (wParam == VK_RETURN)
		{ 
			strcpy(results[3].pilotName, pilotName4->text);
			internalState4++;
			electroBang->play();
		}
		else
		{
			bool rc;
			rc=guiFrame4->keyhit(wParam);
			if (rc) return; // key hit consumed
		}
	}	
	if (wParam == VK_UP && internalState < 3)
	{
		internalState++;
	}
	if (internalState == 1)
	{
		if (wParam == VK_LEFT)
		{
			if (currentShipNo == 1)
			{
				currentShipNo = 7;
				previousShipNo--;
				nextShipNo --;
			}
			else if (currentShipNo ==7)
			{
				currentShipNo--;
				previousShipNo--;
				nextShipNo = 7;
			}
			else if (currentShipNo == 2)
			{
				currentShipNo--;
				previousShipNo = 7;
				nextShipNo--;
			}
			else
			{
				currentShipNo--;
				previousShipNo--;
				nextShipNo--;
			}
		}
		if (wParam == VK_RIGHT)
		{
			if (currentShipNo == 1)
			{
				currentShipNo++;
				previousShipNo = 1;
				nextShipNo++;
			}
			else if (currentShipNo ==7)
			{
				currentShipNo = 1;
				previousShipNo = 7;
				nextShipNo++;
			}
			else if (currentShipNo == 6)
			{
				currentShipNo++;
				previousShipNo++;
				nextShipNo=1;
			}
			else
			{
				currentShipNo++;
				previousShipNo++;
				nextShipNo++;
			}
		}
	}
	if (wParam == VK_DOWN)
	{
		if (internalState==0)
			internalState = 0;
		else
			internalState--;
	}
	if (wParam == 'w' || wParam == 'W' && internalState2 < 3)
	{
		internalState2++;
	}
	if (internalState2 == 1)
	{
		if (wParam == 'a' || wParam == 'A')
		{
			if (currentShipNo2 == 1)
			{
				currentShipNo2 = 7;
				previousShipNo2--;
				nextShipNo2 --;
			}
			else if (currentShipNo2 ==7)
			{
				currentShipNo2--;
				previousShipNo2--;
				nextShipNo2 = 7;
			}
			else if (currentShipNo2 == 2)
			{
				currentShipNo2--;
				previousShipNo2 = 7;
				nextShipNo2--;
			}
			else
			{
				currentShipNo2--;
				previousShipNo2--;
				nextShipNo2--;
			}
		}
		if (wParam == 'D' || wParam == 'd')
		{
			if (currentShipNo2 == 1)
			{
				currentShipNo2++;
				previousShipNo2 = 1;
				nextShipNo2++;
			}
			else if (currentShipNo2 ==7)
			{
				currentShipNo2 = 1;
				previousShipNo2 = 7;
				nextShipNo2++;
			}
			else if (currentShipNo2 == 6)
			{
				currentShipNo2++;
				previousShipNo2++;
				nextShipNo2=1;
			}
			else
			{
				currentShipNo2++;
				previousShipNo2++;
				nextShipNo2++;
			}
		}
	}
	if (wParam == 'y' || wParam == 'Y' && internalState3 < 3)
	{
		internalState3++;
	}
	if (internalState3 == 1)
	{
		if (wParam == 'g' || wParam == 'G')
		{
			if (currentShipNo3 == 1)
			{
				currentShipNo3 = 7;
				previousShipNo3--;
				nextShipNo3 --;
			}
			else if (currentShipNo3 ==7)
			{
				currentShipNo3--;
				previousShipNo3--;
				nextShipNo3 = 7;
			}
			else if (currentShipNo3 == 2)
			{
				currentShipNo3--;
				previousShipNo3 = 7;
				nextShipNo3--;
			}
			else
			{
				currentShipNo3--;
				previousShipNo3--;
				nextShipNo3--;
			}
		}
		if (wParam == 'j' || wParam == 'J')
		{
			if (currentShipNo3 == 1)
			{
				currentShipNo3++;
				previousShipNo3 = 1;
				nextShipNo3++;
			}
			else if (currentShipNo3 ==7)
			{
				currentShipNo3 = 1;
				previousShipNo3 = 7;
				nextShipNo3++;
			}
			else if (currentShipNo3 == 6)
			{
				currentShipNo3++;
				previousShipNo3++;
				nextShipNo3=1;
			}
			else
			{
				currentShipNo3++;
				previousShipNo3++;
				nextShipNo3++;
			}
		}
	}
	if ((wParam == 'm' || wParam == 'M' )&& internalState4 < 3)
	{
		internalState4++;
	}
	if (internalState4 == 1)
	{
		if (wParam == 'l' || wParam == 'L')
		{
			if (currentShipNo4 == 1)
			{
				currentShipNo4 = 7;
				previousShipNo4--;
				nextShipNo4 --;
			}
			else if (currentShipNo4 ==7)
			{
				currentShipNo4--;
				previousShipNo4--;
				nextShipNo4 = 7;
			}
			else if (currentShipNo4 == 2)
			{
				currentShipNo4--;
				previousShipNo4 = 7;
				nextShipNo4--;
			}
			else
			{
				currentShipNo4--;
				previousShipNo4--;
				nextShipNo4--;
			}
		}
		if (wParam == 'P' || wParam == 'p')
		{
			if (currentShipNo4 == 1)
			{
				currentShipNo4++;
				previousShipNo4 = 1;
				nextShipNo4++;
			}
			else if (currentShipNo4 ==7)
			{
				currentShipNo4 = 1;
				previousShipNo4 = 7;
				nextShipNo4++;
			}
			else if (currentShipNo4 == 6)
			{
				currentShipNo4++;
				previousShipNo4++;
				nextShipNo4=1;
			}
			else
			{
				currentShipNo4++;
				previousShipNo4++;
				nextShipNo4++;
			}
		}
	}
	if (wParam == VK_RSHIFT)
	{
		if (internalState4==0)
			internalState4 = 0;
		else
			internalState4--;
	}
	if (wParam == 'h' || wParam == 'H')
	{
		if (internalState3==0)
			internalState3 = 0;
		else
			internalState3--;
	}
	if (wParam == 's' || wParam == 'S')
	{
		if (internalState2==0)
			internalState2 = 0;
		else
			internalState2--;
	}
	if (wParam == VK_DOWN)
	{
		if (internalState==0)
			internalState = 0;
		else
			internalState--;
	}
	if (wParam == VK_SPACE)
		st->transitTo(5);
}
void state4_class::checkMouse()
{
	DIMOUSESTATE2 ms;
	HRESULT rc;

	if (!mouseAquired) return;

	rc=g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&ms);
	if (FAILED(rc))
	{
		UC_err("ERROR> The mouse is not working");
		UC_unaquireMouse();
	}

	mouseX=mouseX+ms.lX;
	mouseY=mouseY+ms.lY;
	if (mouseX<0) mouseX=0;
	if (mouseY<0) mouseY=0;
	if (mouseX>=1024) mouseX=1024-1;
	if (mouseY>=768) mouseY=768-1;

	if (prevButtonState !=0 && prevButtonState == ms.rgbButtons[0]) return;
	prevButtonState = ms.rgbButtons[0];

	if (ms.rgbButtons[0] != 0)
	{
		if ( guiFrame->isIn((int)mouseX,(int)mouseY))
		{
			bool rc;
			rc=guiFrame->mouseKlick((int)mouseX,(int)mouseY);
			if (rc) return;
		}
	}

	if (ms.rgbButtons[1] != 0)
	{
		UC_unaquireMouse();
	}
}
void state4_class::setPilots()
{
	for (int i = 0; i<6; i++)
	{
		results[i].leaguePoints = 0;
		results[i].playerNo = i+1;
		results[i].roundPoints = 0;
		results[i].selected = false;
		results[i].selectedShip = 0;

		if (i == 0)
			strcpy(results[i].pilotName, "LUKE");
		else if (i == 1)
			strcpy(results[i].pilotName, "EWOK");
		else if (i == 2)
			strcpy(results[i].pilotName, "BEN");
		else if (i == 3)
			strcpy(results[i].pilotName, "EMPEROR");
		else if (i == 4)
			strcpy(results[i].pilotName, "ANNAKIN");
		else if (i == 5)
			strcpy(results[i].pilotName, "BOBBA");
	}		
}
void state4_class::doIt()
{
	if (mouseX >500)
		boolReady = true;
}
// ------------------ state5 -----------------------

void state5_class::render()
{
	myLevel->render();
}

void state5_class::init()
{
	myLevel=new MYLEVEL();
	myLevel->init();
}

void state5_class::cleanUp()
{
	myLevel->cleanUp();
	delete myLevel;
}

void state5_class::timerTick()
{
	myLevel->timerTick();
}
void  state5_class::keyhit(WPARAM wParam)
{
	myLevel->keyhit(wParam);
}

// ------------ state 6 class Round Winner ----------------------


state6_class::state6_class()
{
}
void state6_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	
	UC_DrawLine2D(g_pDirect3DDevice,0,220,800, 220,UC_BLUE,UC_BLUE);
	UC_DrawLine2D(g_pDirect3DDevice,0,(6*70)+180 + 45, 800, (6*70)+180 +45,UC_BLUE,UC_BLUE);
	UC_printf(g_pDirect3DDevice, 135, 70+45, D3DCOLOR_XRGB(255,255,255),3, "%s", "C U R R E N T    L E A G U E    S T A N D I N G S");
	UC_printf(g_pDirect3DDevice, 200, 150+45, D3DCOLOR_XRGB(255,255,255),3, "%s", "PILOT NAME");
	UC_printf(g_pDirect3DDevice, 400, 150+45, D3DCOLOR_XRGB(255,255,255),3, "%s", "ROUND POINTS");
	UC_printf(g_pDirect3DDevice, 600, 150+45, D3DCOLOR_XRGB(255,255,255),3, "%s", "LEAGUE POINTS");

	for (int i = 0; i < 6; i++)
	{
		if (i==0)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FIRST");
		else 	if (i==1)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "SECOND");
		else 	if (i==2)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "THIRD");
		else 	if (i==3)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FOURTH");
		else 	if (i==4)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FIFTH");
		else
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "SIXTH");

			if (standings[i].playerNo == 1)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,0,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 2)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(0,255,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 3)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 4)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(0,0,255),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 5)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,0,255),3, "%s", standings[i].pilotName);
			else //if (standings[i].playerNo == 6)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,180,0),3, "%s", standings[i].pilotName);

		UC_printf(g_pDirect3DDevice, (float) (450), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%d", standings[i].roundPoints);
		UC_printf(g_pDirect3DDevice, (float) (660), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%d", standings[i].leaguePoints);
	}
	guiFrame->render();
	if(mouseAquired)
		BlitPart(g_pDirect3DDevice, texCursor->textureData, 0, 0, 32, 32, mouseX, mouseY, mouseX + 32, mouseY + 32, true);
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	if (pBackBuffer)
        pBackBuffer->Release();
}

void state6_class::init()
{
	texCursor = new UC_texture(getFileName("cursor.bmp"), 32, 32, D3DCOLOR_XRGB(0, 0, 0));
	UC_initDImouse();
	guiFrame=new UC_GUIFrame();
	guiFrame->LoadBmp(getFileName("backFrame.bmp"),UC_OPAQUE_WHITE,128);
	guiFrame->setBounds(800,395,256,128);

	next=new myButton(guiFrame);
	next->LoadBmp(getFileName("next.bmp"),UC_OPAQUE_BLACK,255);
	next->setPos(0,0);
	guiFrame->AddControl(next);
	
	Quit=new myButton(guiFrame);
	Quit->LoadBmp(getFileName("quit.bmp"),UC_OPAQUE_BLACK,255);
	Quit->setPos(0,40);
	guiFrame->AddControl(Quit);

	this->mouseX = 300;
	this->mouseY = 300;
	
	for (int p = 0; p < 6; p++)
	{
		if (results[p].roundPoints >= round)
			results[p].leaguePoints++;

		standings[p].leaguePoints = results[p].leaguePoints;
		standings[p].roundPoints = results[p].roundPoints;
		strcpy(standings[p].pilotName, results[p].pilotName);
		standings[p].playerNo = results[p].playerNo;
		standings[p].selected = results[p].selected;
		standings[p].selectedShip = results[p].selectedShip;
	}
	catana = new UC_CWave(getFileName("cantina.wav"));
	catana->play_looping();
	bubbleSort(standings);
}

void state6_class::cleanUp()
{
	delete guiFrame;
	delete this->texCursor;
	catana->stop();
	delete catana;
}

void state6_class::keyhit(WPARAM wParam)
{
	if (wParam=='n' || wParam=='N') 
	{
		st->transitTo(5);
	}
	if (wParam=='q' || wParam=='Q') 
	{
		st->transitTo(2);
	}
}

void state6_class::timerTick()
{
	checkMouse();
}
void state6_class::doIt()
{
	if (mouseY <= 434 && mouseY >=395)
		st->transitTo(5);
	else if (mouseY <=475  && mouseY >= 435)
		st->transitTo(2);
}
void state6_class::checkMouse()
{
	DIMOUSESTATE2 ms;
	HRESULT rc;

	if (!mouseAquired) return;

	rc=g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&ms);
	if (FAILED(rc))
	{
		UC_err("ERROR> The mouse is not working");
		UC_unaquireMouse();
	}

	mouseX=mouseX+ms.lX;
	mouseY=mouseY+ms.lY;
	if (mouseX<0) mouseX=0;
	if (mouseY<0) mouseY=0;
	if (mouseX>=1024) mouseX=1024-1;
	if (mouseY>=768) mouseY=768-1;

	if (prevButtonState !=0 && prevButtonState == ms.rgbButtons[0]) return;
	prevButtonState = ms.rgbButtons[0];

	if (ms.rgbButtons[0] != 0)
	{
		if ( guiFrame->isIn((int)mouseX,(int)mouseY))
		{
			bool rc;
			rc=guiFrame->mouseKlick((int)mouseX,(int)mouseY);
			if (rc) return;
		}
	}

	if (ms.rgbButtons[1] != 0)
	{
		UC_unaquireMouse();
	}
}
void state6_class::bubbleSort(ShipData b[6])
{
	ShipData temp;
	
	for (int pass = 1; pass < 6; pass++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (b[i].leaguePoints < b[i +1].leaguePoints)
			{
				temp = b[i];
				b[i] = b[i+1];
				b[i+1] = temp;
			}
		}
	}
}
// ------------ state 7 - Leaque Winner ---------------------------
state7_class::state7_class()
{
}
void state7_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	
	UC_DrawLine2D(g_pDirect3DDevice,0,220,800, 220,UC_BLUE,UC_BLUE);
	UC_DrawLine2D(g_pDirect3DDevice,0,(6*70)+180 + 45, 800, (6*70)+180 +45,UC_BLUE,UC_BLUE);
	//UC_printf(g_pDirect3DDevice, 135, 70+45, D3DCOLOR_XRGB(255,255,255),3, "%s", "C U R R E N T    L E A G U E    S T A N D I N G S");
	UC_printf(g_pDirect3DDevice, (float) (190), (float) (70+45), D3DCOLOR_XRGB(255,255,255),3, "%s", "F I N A L    L E A G U E    S T A N D I N G S");
	UC_printf(g_pDirect3DDevice, (float) (200), (float) (150+45), D3DCOLOR_XRGB(255,255,255),3, "%s", "PILOT NAME");
	UC_printf(g_pDirect3DDevice, (float) (400), (float) (150+45), D3DCOLOR_XRGB(255,255,255),3, "%s", "ROUND POINTS");
	UC_printf(g_pDirect3DDevice, (float) (600), (float) (150+45), D3DCOLOR_XRGB(255,255,255),3, "%s", "LEAGUE POINTS");

	for (int i = 0; i < 6; i++)
	{
		if (i==0)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FIRST");
		else 	if (i==1)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "SECOND");
		else 	if (i==2)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "THIRD");
		else 	if (i==3)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FOURTH");
		else 	if (i==4)
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "FIFTH");
		else
			UC_printf(g_pDirect3DDevice, (float) (50), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%s", "SIXTH");

			if (standings[i].playerNo == 1)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,0,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 2)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(0,255,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 3)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,0),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 4)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(0,0,255),3, "%s", standings[i].pilotName);
			else if (standings[i].playerNo == 5)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,0,255),3, "%s", standings[i].pilotName);
			else //if (standings[i].playerNo == 6)
				UC_printf(g_pDirect3DDevice, (float) (200), (float) ((i*70)+245), D3DCOLOR_XRGB(255,180,0),3, "%s", standings[i].pilotName);

		UC_printf(g_pDirect3DDevice, (float) (450), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%d", standings[i].roundPoints);
		UC_printf(g_pDirect3DDevice, (float) (660), (float) ((i*70)+245), D3DCOLOR_XRGB(255,255,255),3, "%d", standings[i].leaguePoints);
	}

	guiFrame->render();
	if(mouseAquired)
		BlitPart(g_pDirect3DDevice, texCursor->textureData, 0, 0, 32, 32, mouseX, mouseY, mouseX + 32, mouseY + 32, true);
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	if (pBackBuffer)
        pBackBuffer->Release();
}

void state7_class::init()
{
	texCursor = new UC_texture(getFileName("cursor.bmp"), 32, 32, D3DCOLOR_XRGB(0, 0, 0));
	UC_initDImouse();
	guiFrame=new UC_GUIFrame();
	guiFrame->LoadBmp(getFileName("backFrame.bmp"),UC_OPAQUE_WHITE,128);
	guiFrame->setBounds(800,395,256,128);
	
	Quit=new myButton(guiFrame);
	Quit->LoadBmp(getFileName("quit.bmp"),UC_OPAQUE_BLACK,255);
	Quit->setPos(0,20);
	guiFrame->AddControl(Quit);

	this->mouseX = 300;
	this->mouseY = 300;
	
	for (int p = 0; p < 6; p++)
	{
		if (results[p].roundPoints >= round)
			results[p].leaguePoints++;

		standings[p].leaguePoints = results[p].leaguePoints;
		standings[p].roundPoints = results[p].roundPoints;
		strcpy(standings[p].pilotName, results[p].pilotName);
		standings[p].playerNo = results[p].playerNo;
		standings[p].selected = results[p].selected;
		standings[p].selectedShip = results[p].selectedShip;
	}
	victory = new UC_CWave(getFileName("victcel.wav"));
	victory->play_looping();
	bubbleSort(standings);
}

void state7_class::cleanUp()
{
	delete guiFrame;
	delete this->texCursor;

	victory->stop();
	delete victory;
}

void state7_class::keyhit(WPARAM wParam)
{
	if (wParam=='q' || wParam=='Q') 
	{
		st->transitTo(2);
	}
}

void state7_class::timerTick()
{
	checkMouse();
}
void state7_class::doIt()
{
	if (mouseY <=455  && mouseY >= 415)
		st->transitTo(2);
}
void state7_class::checkMouse()
{
	DIMOUSESTATE2 ms;
	HRESULT rc;

	if (!mouseAquired) return;

	rc=g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&ms);
	if (FAILED(rc))
	{
		UC_err("ERROR> The mouse is not working");
		UC_unaquireMouse();
	}

	mouseX=mouseX+ms.lX;
	mouseY=mouseY+ms.lY;
	if (mouseX<0) mouseX=0;
	if (mouseY<0) mouseY=0;
	if (mouseX>=1024) mouseX=1024-1;
	if (mouseY>=768) mouseY=768-1;

	if (prevButtonState !=0 && prevButtonState == ms.rgbButtons[0]) return;
	prevButtonState = ms.rgbButtons[0];

	if (ms.rgbButtons[0] != 0)
	{
		if ( guiFrame->isIn((int)mouseX,(int)mouseY))
		{
			bool rc;
			rc=guiFrame->mouseKlick((int)mouseX,(int)mouseY);
			if (rc) return;
		}
	}

	if (ms.rgbButtons[1] != 0)
	{
		UC_unaquireMouse();
	}
}
void state7_class::bubbleSort(ShipData b[6])
{
	ShipData temp;
	
	for (int pass = 1; pass < 6; pass++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (b[i].leaguePoints < b[i +1].leaguePoints)
			{
				temp = b[i];
				b[i] = b[i+1];
				b[i+1] = temp;
			}
		}
	}
}
// ------------ state 8 - debug ---------------------------
void state8_class::render()
{
}

void state8_class::keyhit(WPARAM wParam)
{
}

void state8_class::init()
{
}

void state8_class::cleanUp()
{
}

// end