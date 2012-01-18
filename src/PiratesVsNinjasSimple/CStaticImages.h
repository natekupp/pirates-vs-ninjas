#pragma once

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include <gl\glaux.h>					// Header File For The Glaux Library
#include "SOIL.h"
#include "Defines.h"
#include "CGame.h"

class CGame;


class CStaticImages
{
public:
	CStaticImages(CGame* game, int width, int height);
	~CStaticImages(void);

	void	drawStatic(GLuint mask, GLuint image);
	void	loadSkyBoxTextures();
	void	loadStaticTextures();
	void	loadHeightMapTextures();
	void	drawGLStatics();
	int		drawHealthStatic();
	int		drawCross();
	
	int	w, h; // Window width, height
	
	// Static textures
	GLuint	statics[10];	
	GLuint	splash[4];
	GLuint	selectClass[4];
	GLuint	about[2];
	GLuint	health[5];
	GLuint	gun[4];
	GLuint	endGame[2];
	GLuint	skybox[6];
	GLuint	heightMapTexture[2];

private:
	CGame*	cGame;
};

