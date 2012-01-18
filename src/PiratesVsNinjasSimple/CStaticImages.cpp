#include "CStaticImages.h"

CStaticImages::CStaticImages(CGame* game, int width, int height)
{
	cGame			= game;
	w				= width;
	h				= height;
}

CStaticImages::~CStaticImages(void)
{
}

void CStaticImages::loadSkyBoxTextures() 
{
	skybox[0] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_west.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	skybox[1] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_east.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y  | SOIL_FLAG_TEXTURE_REPEATS
	);

	skybox[2] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_north.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	skybox[3] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_south.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	skybox[4] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_up.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y  | SOIL_FLAG_TEXTURE_REPEATS
	);

	skybox[5] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_down.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);
}




void CStaticImages::loadStaticTextures()
{

	statics[2] = SOIL_load_OGL_texture
	(
		"../images/static/hand1_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[3] = SOIL_load_OGL_texture
	(
		"../images/static/hand1_image.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[4] = SOIL_load_OGL_texture
	(
		"../images/static/hand2_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[5] = SOIL_load_OGL_texture
	(
		"../images/static/hand2_image.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[6] = SOIL_load_OGL_texture
	(
		"../images/static/stereo_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[7] = SOIL_load_OGL_texture
	(
		"../images/static/stereo_img.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[8] = SOIL_load_OGL_texture
	(
		"../images/static/headshot_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[9] = SOIL_load_OGL_texture
	(
		"../images/static/headshot.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);



	splash[0] = SOIL_load_OGL_texture
	(
		"../images/static/splash_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	splash[1] = SOIL_load_OGL_texture
	(
		"../images/static/splash_start.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	
	splash[2] = SOIL_load_OGL_texture
	(
		"../images/static/splash_about.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	splash[3] = SOIL_load_OGL_texture
	(
		"../images/static/splash_exit.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);


	selectClass[0] = SOIL_load_OGL_texture
	(
		"../images/static/select_pirate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	
	selectClass[1] = SOIL_load_OGL_texture
	(
		"../images/static/select_ninja.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	about[0] = SOIL_load_OGL_texture
	(
		"../images/static/aboutscreen_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	about[1] = SOIL_load_OGL_texture
	(
		"../images/static/aboutscreen.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	health[0] = SOIL_load_OGL_texture
	(
		"../images/static/health_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	health[1] = SOIL_load_OGL_texture
	(
		"../images/static/health_low.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	health[2] = SOIL_load_OGL_texture
	(
		"../images/static/health_high.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	health[3] = SOIL_load_OGL_texture
	(
		"../images/static/health_man_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	health[4] = SOIL_load_OGL_texture
	(
		"../images/static/health_man.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	gun[0] = SOIL_load_OGL_texture
	(
		"../images/static/gun_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	gun[1] = SOIL_load_OGL_texture
	(
		"../images/static/gun.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	gun[2] = SOIL_load_OGL_texture
	(
		"../images/static/gunfiring_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	gun[3] = SOIL_load_OGL_texture
	(
		"../images/static/gunfiring.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	endGame[0] = SOIL_load_OGL_texture
	(
		"../images/static/youwin.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
	endGame[1] = SOIL_load_OGL_texture
	(
		"../images/static/youlose.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);
}


void CStaticImages::drawStatic(GLuint mask, GLuint image) 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -(float)h, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//load the mask
	glBlendFunc(GL_DST_COLOR,GL_ZERO);				// Blend Screen Color With Zero (Black)
	glBindTexture(GL_TEXTURE_2D, mask);

	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3i(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3i(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	//now load the actual image
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, image);

	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3i(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3i(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

}


void CStaticImages::drawGLStatics()
{
	switch(cGame->currentState)
	{
		case GAMESTATE_SPLASH_START:
			drawStatic(splash[0], splash[1]);
			break;

		case GAMESTATE_SPLASH_ABOUT:
			drawStatic(splash[0], splash[2]);
			break;

		case GAMESTATE_SPLASH_EXIT:
			drawStatic(splash[0], splash[3]);
			break;

		case GAMESTATE_SELECT_PIRATE:
			drawStatic(statics[1], selectClass[0]);
			break;

		case GAMESTATE_SELECT_NINJA:
			drawStatic(statics[1], selectClass[1]);
			break;
		case GAMESTATE_ABOUT:
			drawStatic(about[0], about[1]);
			break;

		case GAMESTATE_PLAY:
			if ( cGame->rickroll_Mode )
				drawStatic(statics[6], statics[7]);
			else
			{
				switch(cGame->CharacterType)
				{
				case PIRATE:
					if ( cGame->shoot_time < SHOOT_TIME-2 && cGame->shoot_time > SHOOT_TIME-10 )
						drawStatic(gun[2], gun[3]);
					else
						drawStatic(gun[0], gun[1]);
					break;
				case NINJA:
					if ( cGame->shoot_time < SHOOT_TIME-2 && cGame->shoot_time > SHOOT_TIME-10 )
						drawStatic(statics[4], statics[5]);
					else
						drawStatic(statics[2], statics[3]);
					break;
				}
			}
			drawCross();
			drawHealthStatic();
			break;
		case GAMESTATE_END:
			if ( cGame->CharacterWinLose == YOU_WIN )
				drawStatic(statics[1],endGame[0]);
			else
				drawStatic(statics[1],endGame[1]);
			break;
	}
}

int CStaticImages::drawHealthStatic() 
{
	if (cGame->CharacterHealth < 0)
		cGame->CharacterHealth = 0;
	if (cGame->CharacterHealth > 100)
		cGame->CharacterHealth = 100;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0.0f, -(float)h, 0.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//load the mask
	glBlendFunc(GL_DST_COLOR,GL_ZERO);				// Blend Screen Color With Zero (Black)
	glBindTexture(GL_TEXTURE_2D, health[0]);
	glTranslatef(0, h - 170.0f, 0);
	glScalef(0.1f, 0.15f, 0.2f);	
	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3i(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3i(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	//now load the actual image
	glColor4f(1.0,1.0,1.0, 1 - (float)cGame->CharacterHealth / 100 );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, health[1]);
	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3i(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3i(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	glColor4f(1.0,1.0,1.0, (float)cGame->CharacterHealth / 100 );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, health[2]);

	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3i(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3i(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3i(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3i(0,  h,  0);	// Top Left
	glEnd();	

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	
	return TRUE;
}

int CStaticImages::drawCross()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -(float)h, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	
	glBegin(GL_LINES);
		glVertex3i(w/2,  h/2-CROSS_RADIUS,  0);
		glVertex3i(w/2,  h/2+CROSS_RADIUS,  0);
		glVertex3i(w/2-CROSS_RADIUS,  h/2-1,  0);
		glVertex3i(w/2+CROSS_RADIUS,  h/2-1,  0);
	glEnd();
	
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	return TRUE;
}

void CStaticImages::loadHeightMapTextures() 
{
	heightMapTexture[0] = SOIL_load_OGL_texture
		(
			"../images/terrain/terrain.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
		);

	heightMapTexture[1] = SOIL_load_OGL_texture
		(
			"../images/terrain/detail.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
}