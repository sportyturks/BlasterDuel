// 999999.cpp

#include <stdio.h>
#include <dsound.h>

#include "UC_main.h"
#include "UC_Dir.h"
#include "UC_UtilsV2.h"
#include "UC_A2_gameCode.h"
#include "888888.h"
#include "CWave.h"


void u888888_class::init()
{
	//score=0;
	background = new UC_texture(getFileName("playerBackground.bmp"),1024,128,(0, 0, 0));
	bang = new UC_texture(getFileName("explosion256x2048.bmp"),2048,256,D3DCOLOR_XRGB(0, 0, 0), 200);
	shield = new UC_texture(getFileName("shield.bmp"),64,64,D3DCOLOR_XRGB(0, 0, 0), 160);
	exhaust = new UC_texture(getFileName("exhaust.bmp"),256,64,D3DCOLOR_XRGB(0, 0, 0), 200);
	helpTex = new UC_texture(getFileName("help.bmp"),1024,1024, NULL, 150);
	//stary, stary night... 
	for (int i =0; i < numStars; i++)
	{
		backStars[i] = new Sprite(-100.0, -100.0, 270.0, 16.0, 16.0, 0.0); 
	}
	
	//Sounds
	explosion2 = new UC_CWave(getFileName("explosion2.wav"));
	endLaugh = new UC_CWave(getFileName("laugh.wav"));
	
	//***************************Players*****************************************//
	
	for (int i=0; i < numShips; i++)
	{
		if (i == 0) //player
		{
			player[0] = new Rebel_Ship(0, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, 0); //should be similar for all players
			
			if (results[i].selected)
			{
				setPlayer(0);
			}
			else
			{	
				player[0]->setTexture("x.bmp",1024, 64, 0, 0, 0);
				player[0]->setSounds("x-wing.wav", "xlaser.wav");
				computer[0]= new EnemyAI(0);
			}

		}
		else if (i == 1)
		{
			player[1] = new Rebel_Ship(1, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, 1); //should be similar for all players
			
			if (results[1].selected)
			{
				setPlayer(1);
			}
			else
			{	
				player[1]->setTexture("x.bmp",1024, 64, 0, 0, 0);
				player[1]->setSounds("x-wing.wav", "xlaser.wav");
				computer[1]= new EnemyAI(1);
			}
		}
		else if (i == 2)
		{
			player[2] = new Rebel_Ship(2, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, 2); //should be similar for all players
			
			if (results[2].selected)
			{
				setPlayer(2);
			}
			else
			{	
				player[2]->setTexture("ntie.bmp",1024, 64, 0, 0, 0);
				player[2]->setSounds("tlaunch2.wav", "lazer2.wav");
				computer[2]= new EnemyAI(2);
			}
		}
		else if (i == 3)
		{
			player[3] = new Rebel_Ship(3, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, 3); //should be similar for all players
			
			if (results[3].selected)
			{
				setPlayer(3);
			}
			else
			{	
				player[3]->setTexture("shuttle.bmp",1024, 64, 0, 0, 0);
				player[3]->setSounds("tlaunch2.wav", "lazer2.wav");
				computer[3]= new EnemyAI(3);
			}
		}
		else if (i == 4)
		{
			player[i] = new Rebel_Ship(i, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, i); //should be similar for all players
			player[i]->setTexture("btie.bmp",1024, 64, 0, 0, 0);
			player[i]->setSounds("tlaunch.wav", "lazer3.wav");
			computer[i]= new EnemyAI(i);
		}
		else if (i == 5)
		{
			player[i] = new Rebel_Ship(i, 100, 500.0, 750.0, 270.0, 60.0, 45, 6.0, i); //should be similar for all players
			player[i]->setTexture("a.bmp",1024, 64, 0, 0, 0);
			player[i]->setSounds("x-wing.wav", "lazer1.wav");
			computer[i]= new EnemyAI(i);
		}

		//set explosion sprites
		s_explosions[i] = new Sprite(-100, -100, 0.0, (128), 128, -1.0);
		m_particles[i] = new Particle("particle.bmp", 11);  
		m_particles2[i] = new Particle("particle.bmp", 11);
		m_particles3[i] = new Particle("particle.bmp", 11);

	}
	//***************************************************************************//
	
	timerCount = 0;
	endCount = 0;
	polling = false;
	pollFinished = false;
	endRound = false;
	endLeague = false;
	showWinner = false;
	helpScreen= false;
	pilotWinner = -1;
}

void u888888_class::setPlayer(int i)
{
			if (results[i].selectedShip == 1)
			{
				player[i]->setTexture("a.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("x-wing.wav", "lazer1.wav");
			}
			else if (results[i].selectedShip == 2)
			{
				player[i]->setTexture("x.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("x-wing.wav", "xlaser.wav");
			}
			else if (results[i].selectedShip == 3)
			{
				player[i]->setTexture("falconNEW.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("x-wing.wav", "xlaser.wav");
			}
			else if (results[i].selectedShip == 4)
			{
				player[i]->setTexture("tie.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("tlaunch2.wav", "lazer2.wav");
			}
			else if (results[i].selectedShip == 5)
			{
				player[i]->setTexture("btie.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("tlaunch.wav", "lazer3.wav");
			}
			else if (results[i].selectedShip == 6)
			{
				player[i]->setTexture("ntie.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("tlaunch2.wav", "lazer2.wav");
			}
			else if (results[i].selectedShip == 7)
			{
				player[i]->setTexture("shuttle.bmp",1024, 64, 0, 0, 0);  //suits ntie
				player[i]->setSounds("tlaunch2.wav", "tlaser.wav");
			}
}


void u888888_class::cleanUp()
{

	endLaugh->stop();
	explosion2->stop();
	delete explosion2;
	delete endLaugh;
	delete shield;
	delete exhaust;
	delete helpTex;
	delete background;
	
	for (int i = 0; i < numShips; i++)
	{
		player[i]->cleanUp();
		delete player[i];
		delete s_explosions[i];
		m_particles[i]->cleanUp();
		delete m_particles[i];
		m_particles2[i]->cleanUp();
		delete m_particles2[i];
		m_particles3[i]->cleanUp();
		delete m_particles3[i];

		if (!results[i].selected)
			delete computer[i];
	}

	
	for (int i = 0; i < numStars; i++)
	{
		delete backStars[i];
	}

	//still to do delete paticles

}

//***********************************MENU DRIVEN KEYHITS*************************//

void u888888_class::keyhit(WPARAM wParam)
{
	if (wParam == 'q' || wParam == 'Q')
	{
		st->transitTo(2);
	}
	else if (wParam == VK_F1)
	{
		helpScreen = !helpScreen;
	}
}

//***************************************************************************//

void u888888_class::processKeys()
{
	if (endRound == false && endLeague == false)
	{
		bool *keys;
		keys = pollKeyboard();

		//*****************SHIP MOVEMENTS**************************//
		
		for (int i = 0; i < 4; i++)
		{
			if (i == 0 && results[i].selected)
			{
				if (player[i]->state == 1)
					if (keys[VK_RIGHT])
					{
						player[i]->turnRight = true;
					}
					else
					{
						player[i]->turnRight = false;
					}

				if (player[i]->state == 1)
					if (keys[VK_LEFT])
					{
						player[i]->turnLeft = true;
					}
					else
					{
						player[i]->turnLeft = false;
					}

				if (player[i]->state == 1)
					if (keys[VK_UP] && player[i]->m_x > 10 && player[i]->m_x < 1014)
					{
						player[i]->fireWeapon();
					}
				}
			else if (i == 1 && results[i].selected)
			{
				if (player[i]->state == 1)
					if (keys[68]) // d
					{
						player[i]->turnRight = true;
					}
					else
					{
						player[i]->turnRight = false;
					}

				if (player[i]->state == 1)
					if (keys[65]) // a
					{
						player[i]->turnLeft = true;
					}
					else
					{
						player[i]->turnLeft = false;
					}

				if (player[i]->state == 1&& player[i]->m_x > 10 && player[i]->m_x < 1014)
					if (keys[87])  // w
					{
						player[i]->fireWeapon();
					}
				}
				else if (i == 2 && results[i].selected)
				{
					if (player[i]->state == 1)
						if (keys[74])	//j 
						{
							player[i]->turnRight = true;
						}
						else
						{
							player[i]->turnRight = false;
						}

					if (player[i]->state == 1)
						if (keys[71])		// g
						{
							player[i]->turnLeft = true;
						}
						else
						{
							player[i]->turnLeft = false;
						}

					if (player[i]->state == 1&& player[i]->m_x > 10 && player[i]->m_x < 1014)
						if (keys[89])		// y
						{
							player[i]->fireWeapon();
						}
				}
				else if (i == 3 && results[i].selected)
				{
					if (player[i]->state == 1)
						if (keys[80])	//l
						{
							player[i]->turnRight = true;
						}
						else
						{
							player[i]->turnRight = false;
						}

					if (player[i]->state == 1)
						if (keys[76])		// p
						{
							player[i]->turnLeft = true;
						}
						else
						{
							player[i]->turnLeft = false;
						}

					if (player[i]->state == 1 && player[i]->m_x > 10 && player[i]->m_x < 1014)
						if (keys[77])	// m 
						{
							player[i]->fireWeapon();
						}
				}
		}
	}
	else if (endRound || endLeague)
	{
		updateResults();
	}
	//**********************************************************//

}

void u888888_class::render()
{
	rc = g_pDirect3DDevice->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	if (FAILED(rc)) UC_err("Error getting back buffer.");
    
	g_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	if (helpScreen)
	{
      BlitPart(g_pDirect3DDevice, helpTex->textureData, (float)0.0,  (float) 0.0,  (float)1024.0,  (float) 1024.0, (float) 0.0, (float) 0.0, (float) 1024.0, (float)1024.0, false);
	}
	else
	{
		for (int i = 0; i < numStars; i++)
		{
			if (backStars[i]->m_y < 700)
			{
				if (backStars[i]->m_y > 255)
				{
					UC_DrawLine2D(g_pDirect3DDevice, (int) (backStars[i]->m_x), (int) (backStars[i]->m_y), (int) (backStars[i]->m_x), 
					(int) (backStars[i]->m_y + backStars[i]->m_speed), D3DCOLOR_XRGB(255,(int)((backStars[i]->m_y)/756.0 * 255.0), 
					255), D3DCOLOR_XRGB(255,(int)((backStars[i]->m_y)/756.0 * 255.0), 
					255));
				}
				else
				{
					UC_DrawLine2D(g_pDirect3DDevice, (int) (backStars[i]->m_x), (int) (backStars[i]->m_y), (int) (backStars[i]->m_x), 
					(int) (backStars[i]->m_y + backStars[i]->m_speed), D3DCOLOR_XRGB(255,(int)((backStars[i]->m_y)/756.0 * 255.0), 
					(int)((backStars[i]->m_y)/756.0*255.0)), D3DCOLOR_XRGB(255,(int)((backStars[i]->m_y)/756.0 * 255.0), 
					(int)((backStars[i]->m_y)/756.0*255.0)));
				}
			}
		}

		//UC_printf(g_pDirect3DDevice, 0, 0, D3DCOLOR_XRGB(255,255,255),3, "%s", results[0].pilotName);
		BlitPart(g_pDirect3DDevice, background->textureData, (float)0.0,  (float) 0.0,  (float)1024,  (float) 84, (float) 0, (float) 768-84, (float) 1024, (float)768, false);

		//*****************************************Player Stuff ******************************************//
		for (int i=0; i < numShips; i++)
		{				
			if (s_explosions[i]->m_speed == 1.0 && (!(endRound || endLeague || polling)))
			{
				if (s_explosions[i]->s_frame < 12)
				{
					BlitPart(g_pDirect3DDevice, bang->textureData, (float) s_explosions[i]->s_frame*(128),  (float) 0.0,  (float)s_explosions[i]->s_frame*(128)+(128),  (float) 128, (float) s_explosions[i]->m_x-64, (float) s_explosions[i]->m_y-64, (float) s_explosions[i]->m_x + (64), (float)s_explosions[i]->m_y + 64, true);
				}
				else
				{
					BlitPart(g_pDirect3DDevice, bang->textureData, (float) (((s_explosions[i]->s_frame)%12)*128.0),  (float) 128.0,  (float) (((s_explosions[i]->s_frame)%12)*128.0+128.0), (float) 256.0, (float) ((s_explosions[i]->m_x)- 64.0), (float) ((s_explosions[i]->m_y)- 64.0), (float) ((s_explosions[i]->m_x) + (64.0)), (float)((s_explosions[i]->m_y) + 64.0), true);
				}
			}
						
			for (int j=0; j < player[i]->MAX_BLASTERS; j++)
			{	
				if (player[i]->m_weapon[j]->fired && !polling)
				{
						BigBlitRotate(g_pDirect3DDevice, player[i]->m_weapon[j]->m_weapon, (float) 0.0,  (float) 0.0,  (float)32,  (float) 16, 
						(float) player[i]->m_weapon[j]->m_x, (float) player[i]->m_weapon[j]->m_y, (float) player[i]->m_weapon[j]->m_x + 32, (float)player[i]->m_weapon[j]->m_y + 16, 
						true,  (int) 0, (float) player[i]->m_weapon[j]->m_x + 16, (float) player[i]->m_weapon[j]->m_y+8, (float)degToRad(player[i]->m_weapon[j]->m_direction)*-1, NULL, NULL, false);
					/*UC_DrawLine2D(g_pDirect3DDevice, player[i]->m_weapon[j]->boundBox.m_x0, player[i]->m_weapon[j]->boundBox.m_y0, player[i]->m_weapon[j]->boundBox.m_x1, player[i]->m_weapon[j]->boundBox.m_y0, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->m_weapon[j]->boundBox.m_x1, player[i]->m_weapon[j]->boundBox.m_y0, player[i]->m_weapon[j]->boundBox.m_x1, player[i]->m_weapon[j]->boundBox.m_y1, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->m_weapon[j]->boundBox.m_x1, player[i]->m_weapon[j]->boundBox.m_y1, player[i]->m_weapon[j]->boundBox.m_x0, player[i]->m_weapon[j]->boundBox.m_y1, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->m_weapon[j]->boundBox.m_x0, player[i]->m_weapon[j]->boundBox.m_y1, player[i]->m_weapon[j]->boundBox.m_x0, player[i]->m_weapon[j]->boundBox.m_y0, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
					*/
				}
			}
			
			//UC_DrawLine2D(g_pDirect3DDevice, computer[i]->m_targetX, computer[i]->m_targetY, computer[i]->m_targetX+2, computer[i]->m_targetY +2, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
			
			if (player[i]->m_energy > 50)
			{
				UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0, D3DCOLOR_XRGB(255,255,0), D3DCOLOR_XRGB(0,255,0));
			}
			else
			{
				UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0, D3DCOLOR_XRGB(255,0,0), D3DCOLOR_XRGB(255,255,0));
			}

			switch (i)
			{
				case 0: 
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(255,0,0), D3DCOLOR_XRGB(255,0,0));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(255,0,0), D3DCOLOR_XRGB(255,0,0));
					break;
				case 1:
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(0,255,0), D3DCOLOR_XRGB(0,255,0));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(0,255,0), D3DCOLOR_XRGB(0,255,0));
					break;
				case 2:
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(255,255,0), D3DCOLOR_XRGB(255,255,0));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(255,255,0), D3DCOLOR_XRGB(255,255,0));
					break;
				case 3:
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(0,0,255), D3DCOLOR_XRGB(0,0,255));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(0,0,255), D3DCOLOR_XRGB(0,0,255));
					break;
				case 4:
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(255,0,255), D3DCOLOR_XRGB(255,0,255));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(255,0,255), D3DCOLOR_XRGB(255,0,255));
					break;
				case 5:
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0+4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0+4, D3DCOLOR_XRGB(255,180,0), D3DCOLOR_XRGB(255,180,0));
					UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0-4, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0-4, D3DCOLOR_XRGB(255,180,0), D3DCOLOR_XRGB(255,180,0));
					break;
			}
			
			/*UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x1, player[i]->boundBox.m_y1, player[i]->boundBox.m_x0, player[i]->boundBox.m_y1, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
			UC_DrawLine2D(g_pDirect3DDevice, player[i]->boundBox.m_x0, player[i]->boundBox.m_y1, player[i]->boundBox.m_x0, player[i]->boundBox.m_y0, D3DCOLOR_XRGB(255,255,255), D3DCOLOR_XRGB(255,255,255));
			*/
			
			if (m_particles3[i]->playing)
			{
				for (int j = 0; j < (m_particles3[i]->numOfParticles); j++)
					{
						if (m_particles3[i]->particle[j]->showSprite)
							BlitPart(g_pDirect3DDevice, m_particles3[i]->m_particle->textureData, (float) (0.0),  (float) (0.0),  (float) (16.0), (float) (16.0), (float) (m_particles3[i]->particle[j]->m_x), (float) (m_particles3[i]->particle[j]->m_y), (float) ((m_particles3[i]->particle[j]->m_x)+(m_particles3[i]->particle[j]->m_width*0.5)), (float)((m_particles3[i]->particle[j]->m_y) + (m_particles3[i]->particle[j]->m_height*0.5)), true);
					}
			}


			BigBlitRotate(g_pDirect3DDevice, player[i]->m_body, (float) (player[i]->frame*60.0),  (float) 0.0,  (float)(player[i]->frame*60.0 + 60.0),  (float) 45.0, (float) player[i]->m_x, (float) player[i]->m_y, (float) (player[i]->m_x+ 60.0), (float)(player[i]->m_y + 45.0), true,  (int) 0, (float) (player[i]->m_x+ 30.0), (float) (player[i]->m_y + 26.0), (float)(degToRad(player[i]->m_direction+90)*-1.0), NULL, NULL, false);
			
			if (m_particles[i]->playing)
			{
				for (int j = 0; j < (m_particles[i]->numOfParticles); j++)
				{
					if (m_particles[i]->particle[j]->showSprite)
						BlitPart(g_pDirect3DDevice, m_particles[i]->m_particle->textureData, (float) ((i)*16.0),  (float) (48.0),  (float) ((i*16.0)+16.0), (float) (64.0), (float) (m_particles[i]->particle[j]->m_x), (float) (m_particles[i]->particle[j]->m_y), (float) ((m_particles[i]->particle[j]->m_x)+(m_particles[i]->particle[j]->m_width*0.5)), (float)((m_particles[i]->particle[j]->m_y) + (m_particles[i]->particle[j]->m_height*0.5)), true);
				}
			}

			if (m_particles2[i]->playing)
			{
				for (int j = 0; j < (m_particles2[i]->numOfParticles); j++)
				{
					if (m_particles2[i]->particle[j]->showSprite)
						BlitPart(g_pDirect3DDevice, m_particles2[i]->m_particle->textureData, (float) (((m_particles2[i]->particle[j]->s_frame%12)*16)),  (float) (32.0),  (float) (((m_particles2[i]->particle[j]->s_frame%12)*16)+16.0), (float) (48.0), (float) (m_particles2[i]->particle[j]->m_x), (float) (m_particles2[i]->particle[j]->m_y), (float) ((m_particles2[i]->particle[j]->m_x)+(m_particles2[i]->particle[j]->m_width*0.8)), (float)((m_particles2[i]->particle[j]->m_y) + (m_particles2[i]->particle[j]->m_height*0.8)), true);
				}
			}

			if ((player[i]->state ==0) && (timerCount % 2 == 0))
			{
				BlitPart(g_pDirect3DDevice, shield->textureData, (float) (0.0),  (float) (0.0),  (float) (64.0), (float) (64.0), (float) (player[i]->m_x), (float) (player[i]->m_y-8), (float) (player[i]->m_x+64), (float)((player[i]->m_y+64-8)), true);
			}
			
			//BlitPart(g_pDirect3DDevice, exhaust->textureData, (float) (32.0*(timerCount%8)),  (float) (0.0),  (float) (32.0*(timerCount%8)+32), (float) (64.0), (float) (player[i]->m_x), (float) (player[i]->m_y+16), (float) (player[i]->m_x+32), (float)((player[i]->m_y+64+16)), true);
			
			switch (player[i]->m_colour)
			{
				case 0: 
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(255,0,0),3, "%d", player[i]->m_score);
					break;
				case 1:
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(0,255,0),3, "%d", player[i]->m_score);
					break;
				case 2:
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(255,255,0),3, "%d", player[i]->m_score);
					break;
				case 3:
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(0,0,255),3, "%d", player[i]->m_score);
					break;
				case 4:
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(255,0,255),3, "%d", player[i]->m_score);
					break;
				case 5:
					UC_printf(g_pDirect3DDevice, (float) ((170 + i * player[i]->INTERVAL+i*7)), 730.0, D3DCOLOR_XRGB(255,180,0),3, "%d", player[i]->m_score);
					break;
			}
			if (showWinner && pilotWinner > -1)
			{
				switch (pilotWinner)
				{
					case 0: 
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(255,0,0),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
					case 1:
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(0,255,0),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
					case 2:
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(255,255,0),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
					case 3:
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(0,0,255),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
					case 4:
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(255,0,255),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
					case 5:
						UC_printf(g_pDirect3DDevice, 450.0, 50.0, D3DCOLOR_XRGB(255,180,0),3, "%s WINS!", results[pilotWinner].pilotName);
						break;
				}			
			}
		}
}
//************************************************************************************************//
//***********************************************************************************************//

g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

	if (pBackBuffer)
			pBackBuffer->Release();
}

bool u888888_class::put_in_class_game()
{
	return false;
}

void u888888_class::drawBackground()
{
	for (int i = 0; i < numStars; i++)
	{
		if (backStars[i]->m_y < 0)
		{
			backStars[i]->m_y = (float) (random(1068, 700));
			backStars[i]->m_x = (float) (random(0, 1024));
			backStars[i]->m_speed = (float) (random(1, 6));
		}

		backStars[i]->m_y = backStars[i]->m_y - backStars[i]->m_speed;
	}
}

int u888888_class::random(int min, int max)
{
	return (rand()%(max-min)+min);
}

void u888888_class::moveSprites()
{
	drawBackground();

	for (int i=0; i < numShips; i++)
	{
		if (!results[i].selected && !(endRound || endLeague))
		{
			// if ship has reached its target
			if (computer[i]->rallyPoint)
				computer[i]->destinReached(player[i]->boundBox.m_x0 - 20, player[i]->boundBox.m_x1+ 20, 
													player[i]->boundBox.m_y0 - 20, player[i]->boundBox.m_y1 + 20);
			for (int j =0; j < 6 ; j++)
			{
				computer[i]->setSprites(j, player[j]->m_x, player[j]->m_y, player[j]->m_direction, player[j]->state);
			}

			if (timerCount%15 ==0)
			{
				computer[i]->checkDuration();
			}

			if (player[i]->state == 1)
			{
				switch (computer[i]->moveShip())
				{
					case 0:	player[i]->turnLeft = true;
								player[i]->turnRight = false;
								break;
					
					case 1:	player[i]->turnRight = true;
								player[i]->turnLeft = false;
								break;

					case -1: player[i]->turnRight = false;
								player[i]->turnLeft = false;
								break;
				}

				if ((computer[i]->shoot || rand()%15==0) && player[i]->m_x > 10 && player[i]->m_x < 1014)
					player[i]->fireWeapon();
			}
		}
		else if (polling)
		{
			bool checkPolls= false;
			for (int d = 0; d < numShips; d++)
			{
				if (!(player[d]->m_x >= 1024))
				{
					checkPolls = true;
					d = numShips;
				}
			}

			if (!checkPolls)
			{
				pollFinished = true;
			}
		}


// boundary detection

			if (!(endRound || endLeague))
			{	
				if (player[i]->m_x > (1024 + 25))
					player[i]->m_x = -40;
				else if (player[i]-> m_x < (0 - 50))
					player[i]->m_x = 1024;

				if (player[i]->m_y < 0.0 || (player[i]->m_y > 660 && player[i]->state == 1))
				{
					if (s_explosions[i]->m_speed < 0.0)
					{
						explosion2->play();
						if (player[i]->m_score- die> 0)
							player[i]->m_score-= die;
						else
							player[i]->m_score= 0;

						s_explosions[i]->m_speed = 1.0;
						s_explosions[i]->s_frame = 0;
						s_explosions[i]->m_x = player[i]->m_x;
						s_explosions[i]->m_y = player[i]->m_y;
						m_particles[i]->setParticles(6.0,0.0, 360.0, player[i]->m_x,player[i]->m_y,16.0,16.0,10,500);
						m_particles2[i]->setParticles(6.0,0.0, 360.0, player[i]->m_x,player[i]->m_y,16.0,16.0,10,1000);
					}

					player[i]->initPlayer();
				}

	// change stage, for example from alive to dead ect....		
		
			switch (player[i]->state)
			{
				case 0: 
						player[i]->launchPlayer();
						if (!player[i]->playSound) //(i == 0 || i == 1 || i == 2) && !player[i]->playSound)
						{
							player[i]->launch->play();
							player[i]->playSound = true;
							//computer[i]->InitAI();
						}
						break;
				case 1:	
						player[i]->playSound = false;
						break;
			}
		}

		if (m_particles3[i]->playing)
		{
			if (!m_particles3[i]->moveParticles())
				m_particles3[i]->playing = false;
		}
	
		if (m_particles[i]->playing)
			m_particles[i]->moveParticles();

		if (m_particles2[i]->playing)
			m_particles2[i]->moveParticles();

		player[i]->newCoordinates();
	}
}

void u888888_class::timerTick()
{
	timerCount ++;
	
	if (helpScreen)
	{

	}
	else
	{
		processKeys();

		if (timerCount > 30)
			timerCount = 0;

		//*********************************PLAYER ACTIONS********************************//
		if (endRound == false && endLeague == false)
		{
			for (int i=0; i < numShips; i++)
			{
					if (player[i]->turnLeft)
					{
						if (player[i]->frame>0 && timerCount % 4 == 0)
						{
							player[i]->frame = player[i]->frame - 1;
						}

						player[i]->m_direction= player[i]->m_direction - 6; 
					}
					else if (player[i]->turnRight)
					{		
						if (player[i]->frame < 16 && timerCount % 4 == 0)
						{
							player[i]->frame = player[i]->frame + 1;
						}

						player[i]->m_direction= player[i]->m_direction + 6; 
					}
					else if (player[i]->frame != 8)
					{
						if (player[i]->frame < 8 && timerCount % 4 == 0)
							player[i]->frame= player[i]->frame + 1;
						else if (player[i]->frame > 8 && timerCount % 4 == 0)
							player[i]->frame= player[i]->frame - 1;
					}

					if ((s_explosions[i]->m_speed > 0.0) && (timerCount % 2 == 0))
					{
						if ((s_explosions[i]->s_frame < 23))
						{
							s_explosions[i]->s_frame= s_explosions[i]->s_frame + 1; 
						}
						else
						{
							s_explosions[i]->s_frame= 0;
							s_explosions[i]->m_speed= -1.0;
							s_explosions[i]->m_x = -100;
							s_explosions[i]->m_y = -100;
						}
					}
					
					if (timerCount%4==0 && m_particles[i]->playing)
						for (int j = 0; j < m_particles[i]->numOfParticles; j ++)
						{
							m_particles[i]->particle[j]->s_frame ++;
						}

					if (timerCount%2==0 && m_particles2[i]->playing)
						for (int j = 0; j < m_particles2[i]->numOfParticles; j ++)
						{
							m_particles2[i]->particle[j]->s_frame ++;
						}
					//****************************************************************************************//
			}
			
			performCollision();
			moveSprites();
		}
		else
		{
			moveSprites();

			if (endCount >= 100)
			{
				if (!polling)
				{
					polling= true;
					pollPosition();
				}

				if (pollFinished)
				{
					if (endLeague)
						st->transitTo(7);
					else
						st->transitTo(6);
				}
			}
			else
			{
				endCount++;
			}
		}
	}
}

bool u888888_class::collision(int m_x0, int m_x1, int m_y0, int m_y1, int m_x2, int m_x3, int m_y2, int m_y3)
{
	int x0 = m_x0;
	int y0 = m_y0;
	int x1 = m_x1;
	int y1 = m_y1;

	int x2 = m_x2;
	int y2 = m_y2;
	int x3 = m_x3;
	int y3 = m_y3;

	return !(x1<x2 || x3<x0 || y1<y2 || y3<y0);
}

void u888888_class::performCollision()
{
	for (int i= 0; i < numShips; i++) 
	{
			for (int j = 0; j  < player[i]->MAX_BLASTERS; j++)
			{

	// Collision with bullets

				for (int k = 0; k < numShips; k++)
				{
					if ((k != i) && (player[k]->state == 1))
						if ((player[i]->m_weapon[j]->fired) && 
							collision(
							player[i]->m_weapon[j]->boundBox.m_x0, player[i]->m_weapon[j]->boundBox.m_x1, player[i]->m_weapon[j]->boundBox.m_y0, player[i]->m_weapon[j]->boundBox.m_y1,
							player[k]->boundBox.m_x0, player[k]->boundBox.m_x1,player[k]->boundBox.m_y0, player[k]->boundBox.m_y1))
						{
							if (player[k]->decreaseEnery(60))
							{
								m_particles3[i]->setParticles(2.0, (float) (player[k]->m_direction-50+180), (float) (player[k]->m_direction+50+180), (float) (player[k]->m_x + player[k]->m_width/2.0), (float) (player[k]->m_y + player[k]->m_width),16.0,16.0,3,200);
								player[i]->m_weapon[j]->resetWeapon(player[i]->m_x,player[i]->m_y, player[i]->m_direction);
								player[i]->bulletCheck= player[i]->bulletCheck-1;
							}
							else
							{
								explosion2->play();

								s_explosions[i]->m_speed = 1.0;
								s_explosions[i]->s_frame = 0;
								s_explosions[i]->m_x = player[k]->m_x;
								s_explosions[i]->m_y = player[k]->m_y;
								m_particles[k]->setParticles(6.0,0.0, 360.0, player[k]->m_x,player[k]->m_y,16.0,16.0,10,5000);
								m_particles2[k]->setParticles(6.0,0.0, 360.0, player[k]->m_x,player[k]->m_y,16.0,16.0,10,10000);

								player[i]->m_weapon[j]->resetWeapon(player[i]->m_x,player[i]->m_y, player[i]->m_direction);
								player[i]->bulletCheck= player[i]->bulletCheck-1;
								player[k]->initPlayer();

									if (player[k]->m_score- die> 0)
										player[k]->m_score-= die;
									else
										player[k]->m_score= 0;

								player[i]->m_score+= kill;
														
								if (player[i]->m_score >= round)
								{
									endLaugh->play();
									pilotWinner = i;
									freezePlay();
									
									if (results[i].leaguePoints >= league - 1)
									{
										endLeague = true;
									}
									else
									{
										endRound = true;
									}
								}
							}
						}
						else
						{
							if (player[i]->m_weapon[j]->m_y > 690 && (player[i]->state == 1))
							{
								m_particles3[i]->setParticles(2.0,180,270, player[i]->m_weapon[j]->m_x, player[i]->m_weapon[j]->m_y,16.0,16.0,3,200);
								player[i]->m_weapon[j]->resetWeapon(player[i]->m_x,player[i]->m_y, player[i]->m_direction);
								player[i]->bulletCheck= player[i]->bulletCheck-1;
							}
						}
				}
			}

			for (int k = 0; k < numShips; k++)
			{
				if (k != i && (player[k]->state == 1) && (player[i]->state == 1) && collision(
					player[i]->boundBox.m_x0, player[i]->boundBox.m_x1, player[i]->boundBox.m_y0, player[i]->boundBox.m_y1,
					player[k]->boundBox.m_x0, player[k]->boundBox.m_x1, player[k]->boundBox.m_y0, player[k]->boundBox.m_y1))
				{
					explosion2->play();
					if (player[i]->state != 0 && player[k]->state != 0)
					{
						s_explosions[i]->m_speed = 1.0;
						s_explosions[i]->s_frame = 0;
						s_explosions[i]->m_x = player[i]->m_x;
						s_explosions[i]->m_y = player[i]->m_y;
					}

					m_particles[i]->setParticles(6.0,0.0, 360.0, player[i]->m_x,player[i]->m_y,16.0,16.0,10,5000);
					m_particles2[i]->setParticles(6.0,0.0, 360.0, player[i]->m_x,player[i]->m_y,16.0,16.0,10,10000);
					m_particles[k]->setParticles(6.0,0.0, 360.0, player[k]->m_x,player[k]->m_y,16.0,16.0,10,5000);
					m_particles2[k]->setParticles(6.0,0.0, 360.0, player[k]->m_x,player[k]->m_y,16.0,16.0,10,10000);
				
					if (player[k]->m_score- die> 0)
						player[k]->m_score-= die;
					else
						player[k]->m_score= 0;

					if (player[i]->m_score- die> 0)
						player[i]->m_score-= die;
					else
						player[i]->m_score= 0;
					
					player[i]->initPlayer();
					player[k]->initPlayer();
				}
			}
		}	
}

char *u888888_class::levelName()
{
	return "";
}

char *u888888_class::StudentNames()
{
	return "";
}

char *u888888_class::StudentIDs()
{
	return "";
}

void u888888_class::help()
{
	// render help screen
}
void u888888_class::updateResults()
{
	for (int i = 0; i<6; i++)
	{
		results[i].roundPoints = player[i]->m_score;
	}
}
void u888888_class::freezePlay()
{
	for (int i = 0; i < numShips; i++)
	{
		player[i]->currentSpeed= 0.5;
	}
}

void u888888_class::pollPosition()
{
	showWinner = true;
	for (int i = 0; i < numShips; i++)
	{
		player[i]->state= 1;
		player[i]->m_x = -100;
		player[i]->m_y = (float) (100 + i * 50);
		player[i]->m_speed = 0.0;  // 10 + player[i]->m_score/round + 3;
		player[i]->currentSpeed =(float) ( 9 *player[i]->m_score/round + 3);
		player[i]->m_direction = 0.0;
		player[i]->newCoordinates();	
	}
} 