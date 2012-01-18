#ifndef _MAIN_H
#define _MAIN_H

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "libSOIL.a")
#pragma comment(lib, "fmod.lib")

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include <gl\glaux.h>					// Header File For The Glaux Library
#include <gl\glut.h>
#include "glext.h"
#include <math.h>
#include <iostream>
#include <cstdlib> 
#include <string.h>

#include "Defines.h"
#include "Model.h"
#include "vec.h"

#include "CGame.h"
#include "CCharacter.h"
#include "CStaticImages.h"
#include "MilkshapeModel.h"

// OpenGL Multitexturing support - wow, aren't these awful datatype names, eh?
PFNGLMULTITEXCOORD2FARBPROC	 glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC	 glActiveTextureARB   = NULL;

// Window stuff
HDC			hDC=NULL;									// Private GDI Device Context
HGLRC		hRC=NULL;									// Permanent Rendering Context
HWND		hWnd=NULL;									// Holds Our Window Handle
HINSTANCE	hInstance;									// Holds The Instance Of The Application
static int	w = (long)GetSystemMetrics(SM_CXSCREEN);	// Screen width
static int	h = (long)GetSystemMetrics(SM_CYSCREEN);	// Screen height
bool		keys[256];									// Array Used For The Keyboard Routine
bool		active=TRUE;								// Window Active Flag Set To TRUE By Default
bool		fullscreen=TRUE;							// Fullscreen Flag Set To Fullscreen Mode By Default


// Lighting
static	GLfloat lightPosition0[] = { 0, 0, 0, 0 };
static	GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static	GLfloat lightPosition1[] = { -2, 10, 5, 0 };
static	GLfloat lightDiffuse1[]  = { 1, 1, 1, 1 };
static	GLfloat lightSpecular1[] = { 0.6, 0.6, 0.6, 1};
static	GLfloat model_ambient[]  = {0.4f, 0.4f, 0.4f, 1.0f};


// keep track of game variables all in one spot.
static CGame game;

// we handle textures in this class
CStaticImages staticImages(&game, w, h);

// Models
MilkshapeModel *shot_pirate = NULL;
MilkshapeModel *shot_ninja  = NULL;	
MilkshapeModel *shot		= NULL;	
MilkshapeModel *cannon		= NULL;	
MilkshapeModel *japaneseTower= NULL;
MilkshapeModel *pirateBoat	= NULL;
MilkshapeModel *tree		= NULL;

// Storage for random tree locations
float	TreeTranslationi[NUM_TREES * NUM_TREES];
float	TreeTranslationj[NUM_TREES * NUM_TREES];

// Animated characters
CCharacter* enemies[MAX_ENEMIES];

// Shooting object variables
tVector3 p, v, e; //store pos and view
float t;		  //t in ray

// Function Prototypes
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void	drawSkybox(float x, float y, float z, float width, float height, float length);
void	drawStaticModels();
int		loadModels();
bool	showLoadingScreen();

bool	stuff_loaded = false;

#endif
