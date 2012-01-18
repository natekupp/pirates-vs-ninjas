#pragma once

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include <gl\glaux.h>					// Header File For The Glaux Library
#include "Glext.h"
#include <math.h>
#include <iostream>
#include "SOIL.h"
#include "Defines.h"

using namespace std;

class CHeightMap
{
public:
	CHeightMap(void);
	~CHeightMap(void);

	// Heightmap rendering functions
	void	RenderHeightMap(PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB, PFNGLACTIVETEXTUREARBPROC glActiveTextureARB, GLuint* heightMapTexture);
	int		Height(int X, int Y);
	void	SetVertexColor(int x, int y);
	void	SetupTextures(bool draw_TexturedTerrain, bool splash_screen, int x, int y, int i);

private:
	// Heightmap storage
	unsigned char*	g_HeightMap;	
	
};
