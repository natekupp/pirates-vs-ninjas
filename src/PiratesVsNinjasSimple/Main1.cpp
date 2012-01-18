/************************************************************
*	APRON TUTORIALS PRESENTED BY MORROWLAND					*
*************************************************************
*	Project Name			: Camera 3B						*
*	Project Description		: 1ST Person Camera with strafe	*
*	Project Type			: OpenGL						*
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
*	Version					: English (UK)					*
*	Date					: 24.03.2004					*
************************************************************/

// Strafe function created by Christophe Messager

#include "Main.h"
#include "CModel.h"
#include "CHeightMap.h"
#include "Timer.h"
#include "MilkshapeModel.h"
#include <fstream>

// Game Demo bools ----------------------------------------
bool debug					= false;
bool draw_Trees				= !debug;
bool draw_Skybox			= !debug;
bool draw_Terrain			= !debug;
bool draw_TexturedTerrain	= !debug;
bool draw_StaticModels		= !debug;
bool draw_AnimModels		= !debug;
bool draw_Static			= !debug;
// --------------------------------------------------------


// Globals ----------------------------------------------------------------------------------------------------------------------------------

// Windows stuff
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
CCamera objCamera; 

// fmod mp3 streams
FSOUND_STREAM	*g_splash_stream;
FSOUND_STREAM	*g_game_stream;
FSOUND_STREAM	*g_rick_stream;


// Models
CModel	Castle;
CModel	Rocket;
CModel	Temple;
CModel	Dancer;
CModel  Pirate;
CModel	Tree;

float	DancerAngles[NUM_DANCERS*NUM_DANCERS];
float	DancerTranslationi[NUM_DANCERS*NUM_DANCERS];
float	DancerTranslationj[NUM_DANCERS*NUM_DANCERS];
float	TreeTranslationi[NUM_TREES * NUM_TREES];
float	TreeTranslationj[NUM_TREES * NUM_TREES];

// Lighting
static	GLfloat lightPosition0[] = { 0, 0, 0, 0 };
static	GLfloat lightDiffuse0[]  = { 1,1,1,1 };
static	GLfloat lightPosition1[] = { -2, 10, 5, 0 };
static	GLfloat lightDiffuse1[]  = { 1, 1, 1, 1 };
static	GLfloat lightSpecular1[] = { 0.6, 0.6, 0.6, 1};
static	GLfloat model_ambient[]  = {0.4f, 0.4f, 0.4f, 1.0f};

// Skybox textures
GLuint	SkyboxTexture[6];

// Height map
CHeightMap *theMap;

// Static textures
GLuint	statics[8];	

// Animated models
Model *g_pModel = NULL;			// Holds the model data
Model *g_pModel2 = NULL;		// Holds the model data

// how many Gldraws an animations lasts
volatile int anim_time = 0;

// Timer class
CTimer timer;

// Modes
bool splash_screen = true;
bool rickroll_Mode = false;

// Function Prototypes
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void	setAmbientColor(float r, float g, float b);
void	setDiffuseColor(float r, float g, float b);
void	setSpecularColor(float r, float g, float b);
void	setShininess(float s);
void	DrawSkybox(float x, float y, float z, float width, float height, float length);
void	Keyboard_Input();

void renderString(float x, float y, void *font,char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c=string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();		

}

int loadSkyBoxTextures() {

	SkyboxTexture[SKYFRONT] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_west.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	SkyboxTexture[SKYBACK] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_east.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y  | SOIL_FLAG_TEXTURE_REPEATS
	);

	SkyboxTexture[SKYLEFT] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_north.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	SkyboxTexture[SKYRIGHT] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_south.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	SkyboxTexture[SKYUP] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_up.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y  | SOIL_FLAG_TEXTURE_REPEATS
	);

	SkyboxTexture[SKYDOWN] = SOIL_load_OGL_texture
	(
		"../images/texture/reef_down.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
	);

	// Make sure Skybox loaded OK
	if( 0 == SkyboxTexture[SKYFRONT] || 0 == SkyboxTexture[SKYBACK] || 0 == SkyboxTexture[SKYLEFT] || 
		0 == SkyboxTexture[SKYRIGHT] || 0 == SkyboxTexture[SKYUP]   || 0 == SkyboxTexture[SKYDOWN]  ) {
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
		return FALSE;
	}

	return TRUE;

}

int loadStaticTextures() {

	statics[0] = SOIL_load_OGL_texture
	(
		"../images/static/hand1_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[1] = SOIL_load_OGL_texture
	(
		"../images/static/hand1_image.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[2] = SOIL_load_OGL_texture
	(
		"../images/static/hand2_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[3] = SOIL_load_OGL_texture
	(
		"../images/static/hand2_image.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	statics[4] = SOIL_load_OGL_texture
	(
		"../images/static/stereo_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[5] = SOIL_load_OGL_texture
	(
		"../images/static/stereo_img.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);


	statics[6] = SOIL_load_OGL_texture
	(
		"../images/static/splash_new_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	statics[7] = SOIL_load_OGL_texture
	(
		"../images/static/splash_new.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	return TRUE;
}

int loadHeightMapTextures() {

	theMap->heightMapTexture[0] = SOIL_load_OGL_texture
		(
			"../images/terrain/dirt.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	
	theMap->heightMapTexture[1] = SOIL_load_OGL_texture
		(
			"../images/terrain/water.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	theMap->heightMapTexture[2] = SOIL_load_OGL_texture
		(
			"../images/terrain/ice.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	theMap->heightMapTexture[3] = SOIL_load_OGL_texture
		(
			"../images/terrain/blank.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
		);
	return TRUE;

}

int loadModels() 
{
	//3ds
	/*Castle.m->Load("../models/castle.3ds");
	Temple.m->Load("../models/ionic_temple.3ds");
	Dancer.m->Load("../models/lara.3DS");
	Pirate.m->Load("../models/pirateboat.3ds");
	Tree.m->Load("../models/M_TREE1.3DS");*/

	//milkshape
	g_pModel = new MilkshapeModel();
	if ( g_pModel->loadModelData( "../models/milk/ninja.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	g_pModel->setSuite(2);
	g_pModel->addState(126, 133);
	g_pModel->addState(15, 30);
	g_pModel->setState(0);
	

	g_pModel2 = new MilkshapeModel();
	if ( g_pModel2->loadModelData( "../models/milk/ninja.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	g_pModel2->setSuite(4);
	g_pModel2->addState(1, 14);
	g_pModel2->addState(32, 44);
	g_pModel2->setState(1);
	return TRUE;
}


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	glEnable( GL_NORMALIZE );
	glEnable( GL_TEXTURE_2D);
	
	// Load the Skybox textures		
	loadSkyBoxTextures();

	// Load heightmap textures
	loadHeightMapTextures();

	// Static Textures
	loadStaticTextures();

	// Load models
	loadModels();

	objCamera.Position_Camera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);

	// Generate random initial placements of dudes and trees.
	for ( int i = 0; i < NUM_DANCERS; i++ )
	{
		for (int j = 0; j < NUM_DANCERS; j++ )
		{
			DancerAngles[NUM_DANCERS*i + j] = ( (float)rand() / RAND_MAX ) * 360;
			DancerTranslationi[NUM_DANCERS*i + j] = ( (float)rand() / RAND_MAX ) * 100;
			DancerTranslationj[NUM_DANCERS*i + j] = ( (float)rand() / RAND_MAX ) * 100;
		}
	}

	for ( int i = 0; i < NUM_TREES; i ++ )
	{
		for (int j = 0; j < NUM_TREES; j++ )
		{
			TreeTranslationi[NUM_TREES*i + j] = (( (float)rand() / RAND_MAX ) - 0.4) * 250;
			TreeTranslationj[NUM_TREES*i + j] = (( (float)rand() / RAND_MAX ) - 0.3) * 250;
		}
	}

	return TRUE;
}

int drawStatic() {

	int w = (long)GetSystemMetrics(SM_CXSCREEN);
	int h = (long)GetSystemMetrics(SM_CYSCREEN);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int j = 0;
	if (anim_time > 0) { 
		j = 2;
		anim_time--;
	}

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	if ( splash_screen )
		j = 6;
	if ( rickroll_Mode )
		j = 4;
	
	//load the mask
	glBlendFunc(GL_DST_COLOR,GL_ZERO);				// Blend Screen Color With Zero (Black)
	glBindTexture(GL_TEXTURE_2D, statics[0+j]);

	if (j == 4) {
		float f = ((float)rand() / (RAND_MAX + 1))*40;
		glRotatef(f-30, 0, 0, 0);
	}

	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3f(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3f(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	//now load the actual image
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, statics[1+j]);

	glBegin(GL_QUADS);									// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0,  0,  0);	// Bottom Left
		glTexCoord2f(1.0f, 0.0f); glVertex3f(w,  0,  0);	// Bottom Right
		glTexCoord2f(1.0f, 1.0f); glVertex3f(w,  h,  0);	// Top Right
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0,  h,  0);	// Top Left
	glEnd();											// Done Drawing The Quad

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	return TRUE;

}


int drawAnimModels() {

	glMatrixMode(GL_MODELVIEW);

	//model #1
	glPushMatrix();
	glRotatef(-90, 0,1,0);
	glTranslatef(0, -75, 50);
	glScalef(10,10,10);
	g_pModel->draw();
	glPopMatrix();


	glPushMatrix();
	glRotatef(90, 0,1,0);
	glTranslatef(-50, -75, 50);
	glScalef(10,10,10);
	g_pModel2->draw();
	glPopMatrix();

	return TRUE;

}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	if ( splash_screen )
		objCamera.Rotate_View(0.001);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// use this function for opengl target camera
	gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
			  objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
			  objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
    
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );
	glLightfv( GL_LIGHT1, GL_SPECULAR, lightSpecular1 );
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);


	if ( rickroll_Mode || draw_AnimModels )
		drawAnimModels();

	glPushMatrix();
	
	/*if ( draw_Trees || splash_screen )
	{
		for ( int i = 0; i < NUM_TREES; i ++ )
		{
			for (int j = 0; j < NUM_TREES; j++ )
			{
				Tree.translation[0] = TreeTranslationi[NUM_TREES*i + j];
				Tree.translation[2] = TreeTranslationj[NUM_TREES*i + j];
				Tree.translation[1] = 1.09 * theMap->Height(TreeTranslationi[NUM_TREES*i + j] + MAP_SIZE/2,TreeTranslationj[NUM_TREES*i + j] + MAP_SIZE/2) - 178;
				Tree.scale[0] = 0.1;
				Tree.scale[1] = 0.1;
				Tree.scale[2] = 0.1;
				Tree.Draw();
			}
		}
	}
	if ( draw_StaticModels || splash_screen )
	{
		setAmbientColor(0.7f, 0.7f, 0.7f);
		setDiffuseColor(.6f,.6f,.6f);
		setShininess(5);
		Castle.scale[0] = 2;
		Castle.scale[1] = 2;
		Castle.scale[2] = 2;
		Castle.translation[0] = 230;
		Castle.translation[2] = -200;
		Castle.translation[1] = -75;
		Castle.Draw();
		
		setAmbientColor(0.7f, 0.7f, 0.7f);
		setDiffuseColor(.5f,.5f,.5f);
		setShininess(2);
		Pirate.translation[0] = -230;
		Pirate.translation[2] = 190;
		Pirate.translation[1] = -50;
		Pirate.rotation[1] = 1;
		Pirate.rangle = -37;
		Pirate.scale[0] = 50;
		Pirate.scale[1] = 50;
		Pirate.scale[2] = 50;
		Pirate.Draw();


		Temple.translation[0] = -120; 
		Temple.translation[2] = -165;
		Temple.translation[1] = 40;
		Temple.rangle = 90;
		Temple.scale[0] = 3;
		Temple.scale[1] = 3;
		Temple.scale[2] = 3;
		Temple.rotation[0] = -1;
		Temple.Draw();
	}
	if ( rickroll_Mode )
	{	
		for ( int i = 0; i < NUM_DANCERS; i++ )
		{
			for (int j = 0; j < NUM_DANCERS; j++ )
			{
				Dancer.scale[0] = 0.1;
				Dancer.scale[1] = 0.1;
				Dancer.scale[2] = 0.1;

				Dancer.translation[0] = DancerTranslationi[NUM_DANCERS*i + j];
				Dancer.translation[2] = DancerTranslationj[NUM_DANCERS*i + j];
				Dancer.translation[1] = -170;

				Dancer.rangle		  =	DancerAngles[NUM_DANCERS*i + j];
				Dancer.rotation[1]	  = 1;
				Dancer.Draw();
			}
		}
	}
*/
	// Draw the skybox
	glDisable(GL_LIGHTING);
	if ( draw_Skybox || splash_screen )
		DrawSkybox(0,0,0,MAP_SIZE,MAP_SIZE,MAP_SIZE);

	glTranslatef(-MAP_SIZE/2,-170,- MAP_SIZE/2);	
	if ( draw_Terrain || splash_screen )
		theMap->RenderHeightMap(draw_TexturedTerrain, splash_screen);
	glEnable(GL_LIGHTING);

	glPopMatrix();

	
	if ( rickroll_Mode )
	{	
		int w = (long)GetSystemMetrics(SM_CXSCREEN);
		int h = (long)GetSystemMetrics(SM_CYSCREEN);

		glPushMatrix();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
		glScalef(1, -1, 1);
		glTranslatef(0, -h, 0);
		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		
		glLoadIdentity();
		renderString(GetSystemMetrics(SM_CXSCREEN)/2 - 50,GetSystemMetrics(SM_CYSCREEN)/2,GLUT_BITMAP_HELVETICA_18,"RICKROLL MODE");
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	
	for ( int i = 0; i < NUM_DANCERS; i ++ )
	{
		for (int j = 0; j < NUM_DANCERS; j++ )
		{
			DancerTranslationi[NUM_DANCERS*i + j] = DancerTranslationi[NUM_DANCERS*i + j]+  2*sinf(( (float)rand() / RAND_MAX - 0.5 ) * timer.getTicks_mS() / 2000);
			DancerTranslationj[NUM_DANCERS*i + j] = DancerTranslationj[NUM_DANCERS*i + j]+  2*sinf(( (float)rand() / RAND_MAX - 0.5 ) * timer.getTicks_mS() / 2000);
			DancerAngles[NUM_DANCERS*i + j]       = DancerAngles[NUM_DANCERS*i + j]      +360*sinf(( (float)rand() / RAND_MAX - 0.5 ) * timer.getTicks_mS() / 200);
		}
	}


	//finally, after the screen is drawn, draw static textures
	if ( draw_Static || splash_screen || rickroll_Mode )
		drawStatic();

	return TRUE;
}




GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}


BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	if (fullscreenflag)
		width = (long)GetSystemMetrics(SM_CXSCREEN);
	if (fullscreenflag)
		height = (long)GetSystemMetrics(SM_CYSCREEN);


	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","OPENGL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
				fullscreen=FALSE;
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;	
}


LRESULT CALLBACK WndProc(	HWND	hWnd,UINT	uMsg,WPARAM	wParam,	LPARAM	lParam)
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}
		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:

		  switch(wParam) 
		  {		  
			case VK_ESCAPE:
				PostQuitMessage(0);						
				break;
			case 'R':
				if ( !rickroll_Mode && !splash_screen )
				{
					FSOUND_Stream_Play(1,g_rick_stream);
					FSOUND_Stream_Stop(g_game_stream);
					rickroll_Mode = true;
				}
				else
				{
					if ( !splash_screen )
					{
						FSOUND_Stream_Play(1,g_game_stream);
						FSOUND_Stream_Stop(g_rick_stream);
						rickroll_Mode = false;
					}
				}
				break;
			case '1':
				draw_Skybox = !draw_Skybox;
				break;
			case '2':
				draw_Terrain = !draw_Terrain;
				break;
			case '3':
				draw_TexturedTerrain = !draw_TexturedTerrain;
				break;
			case '4':
				draw_Trees = !draw_Trees;
				break;
			case '5':
				draw_StaticModels = !draw_StaticModels;
				break;
			case '6':
				draw_AnimModels = !draw_AnimModels;
				break;
			case '7':
				draw_Static = !draw_Static;
				break;
			case VK_SPACE:
				if ( splash_screen )
				{
					objCamera.Position_Camera(0, theMap->Height(MAP_SIZE/2, MAP_SIZE/2) - HM_DISPLACEMENT, 0, 
											  0, theMap->Height(MAP_SIZE/2, MAP_SIZE/2) - HM_DISPLACEMENT, 100,   
											  0, 1, 0);
					//FSOUND_Stream_Play(1,g_game_stream);
					//FSOUND_Stream_Stop(g_splash_stream);
					splash_screen = false;
				}
				break;
		  }
		  break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		case WM_LBUTTONDOWN:
		{
			anim_time = 10;
			break;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


int WINAPI WinMain(	HINSTANCE	hInstance,HINSTANCE	hPrevInstance,LPSTR		lpCmdLine,int nCmdShow)
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop
	HWND	g_hSplash = NULL;
	theMap = new CHeightMap();

	// initialize fmod, 44000 Hz, 64 channels
	if( FSOUND_Init(44000,64,0) == FALSE )
		std::cerr << "[ERROR] Could not initialise fmod\n";

	// initialize audio streams
	g_splash_stream = FSOUND_Stream_Open( "../sounds/Barbossa.mp3" , FSOUND_2D , 0 , 0 );
	g_game_stream = FSOUND_Stream_Open( "../sounds/Down_to_Earth.mp3" , FSOUND_2D , 0 , 0 );
	g_rick_stream = FSOUND_Stream_Open( "../sounds/NeverGonnaGiveYouUp.mp3" , FSOUND_2D , 0 , 0 );

	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		fullscreen=FALSE;

	FSOUND_Stream_Play(1,g_splash_stream);
	
	if (!CreateGLWindow("Pirates Vs. Ninjas",640,480,16,fullscreen))
		return 0;

	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
				done=TRUE;			
			else
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}	
		else
		{
			if ( !splash_screen)
			{
				Keyboard_Input();
				objCamera.Mouse_Move(640,480, fullscreen);
			}
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	
				done=TRUE;		
			else
				SwapBuffers(hDC);	

			if (keys[VK_F1])
			{
				keys[VK_F1]=FALSE;
				KillGLWindow();
				fullscreen=!fullscreen;
				if (!CreateGLWindow("Pirates Vs. Ninjas",640,480,16,fullscreen))
					return 0;	
			}
		}
	}

	KillGLWindow();	
	FSOUND_Stream_Close(  g_splash_stream );
	delete theMap;
	return (msg.wParam);
}


void Keyboard_Input()
{

	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80))
		objCamera.Move_Camera( CAMERASPEED, theMap);

	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80))
		objCamera.Move_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80))
		objCamera.Strafe_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80))
		objCamera.Strafe_Camera( CAMERASPEED, theMap);


	if(GetKeyState('J') & 0x80)
		anim_time = 10;
}

void setAmbientColor(float r, float g, float b)
{
    GLfloat m_ambientColor[4];
    
    m_ambientColor[0] = (GLfloat)r;
    m_ambientColor[1] = (GLfloat)g;
    m_ambientColor[2] = (GLfloat)b;
    m_ambientColor[3] = (GLfloat)1.0;
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, m_ambientColor);
}

void setDiffuseColor(float r, float g, float b)
{
	GLfloat m_diffuseColor[4];

    m_diffuseColor[0] = (GLfloat)r;
    m_diffuseColor[1] = (GLfloat)g;
    m_diffuseColor[2] = (GLfloat)b;
    m_diffuseColor[3] = (GLfloat)1.0;
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuseColor);
}

void setSpecularColor(float r, float g, float b)
{	
	GLfloat m_specularColor[4];

    m_specularColor[0] = (GLfloat)r;
    m_specularColor[1] = (GLfloat)g;
    m_specularColor[2] = (GLfloat)b;
    m_specularColor[3] = (GLfloat)1.0;
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, m_specularColor);
}

void setShininess(float s)
{
    GLfloat m_shininess = (GLfloat)s;
    glMaterialf( GL_FRONT, GL_SHININESS, m_shininess);
}

void DrawSkybox(float x, float y, float z, float width, float height, float length)
{
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	glPushMatrix();
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYFRONT]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side	
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYBACK]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYLEFT]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side	
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYRIGHT]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYUP]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYDOWN]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
	glPopMatrix();
}




