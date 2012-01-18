// ----------------------------------------------------------------------------------------------------------------------------------
//
//
//
//         /*--------------------------------------*\
//		   *										*
//		   |										|
//		   |  PIRATES			VS.			NINJAS  |	
//		   |										|
//		   *										*
//         \*--------------------------------------*/
//
//
//			Programmed by:
//				- Nate Kupp
//				- Mihalis Maniatakos
//
//			Thanks to:
//				- NeHe tutorials
//				- Apron tutorials	(base for camera class)
//				- Brett Porter		(matrix/vector classes and milkshape animation/model class)
//				- Jonathan Dummer	(SOIL image library)
//				- L3DT (used to generate terrain textures and heightmap)
//
// ----------------------------------------------------------------------------------------------------------------------------------

#include "Main.h"

bool loadUpEverything()
{
	staticImages.loadStaticTextures();		// Load Static Textures
	staticImages.loadSkyBoxTextures();		// Load the Skybox textures		
	staticImages.loadHeightMapTextures();	// Load heightmap textures
	loadModels();							// Load models
	game.initializeGameSounds();			// Initialize audio streams

	// Random trees
	for ( int i = 0; i < NUM_TREES; i ++ )
	{
		for (int j = 0; j < NUM_TREES; j++ )
		{
			TreeTranslationi[NUM_TREES*i + j] = (( (float)rand() / RAND_MAX ) - 0.5) * MAP_SIZE;
			TreeTranslationj[NUM_TREES*i + j] = (( (float)rand() / RAND_MAX ) - 0.5) * MAP_SIZE;
		}
	}


	return true;
}




int inline rangedRand(int range_min, int range_max)
{
   return (int)((double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min);
}

int loadModels() 
{
	//star
	shot_ninja = new MilkshapeModel();
	if ( shot_ninja->loadModelData( "../models/milk/star.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Star model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	shot_ninja->setState(NO_ANIMATION);

	//bullet
	shot_pirate = new MilkshapeModel();
	if ( shot_pirate->loadModelData( "../models/milk/bullet.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Bullet model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	shot_pirate->setState(NO_ANIMATION);
	
	// Cannon
	cannon = new MilkshapeModel();
	if ( cannon->loadModelData( "../models/milk/cannon.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Cannon model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	cannon->setState(NO_ANIMATION);

	japaneseTower = new MilkshapeModel();
	if ( japaneseTower->loadModelData( "../models/milk/japaneseTower.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Japanese Tower model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	japaneseTower->setState(NO_ANIMATION);

	pirateBoat = new MilkshapeModel();
	if ( pirateBoat->loadModelData( "../models/milk/pirateBoat.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Pirate Boat model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	pirateBoat->setState(NO_ANIMATION);

	tree = new MilkshapeModel();
	if ( tree->loadModelData( "../models/milk/tree.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the Tree  model", "Error", MB_OK | MB_ICONERROR );
		return FALSE;									// If model Didn't Load Quit
	}
	tree->setState(NO_ANIMATION);

	return TRUE;
}


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations              <-- Hey Mihali, why did we turn this off?  speed?

	glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	glEnable( GL_NORMALIZE );
	glEnable( GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)		// Check if your OpenGL version support Multitexturing
	{
		MessageBox(NULL, "This OpenGL version does not support Multitexturing!", "ERROR", MB_OK);
		PostQuitMessage(0);									// If not Exit
	}

	// Static Textures
	staticImages.statics[0] = SOIL_load_OGL_texture
	(
		"../images/static/loading.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);
	staticImages.statics[1] = SOIL_load_OGL_texture
	(
		"../images/static/loading_mask.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS 
	);

	return TRUE;
}



void shoot() 
{
	p = tVector3(game.camera->mPos.x,  game.camera->mPos.y,  game.camera->mPos.z);
	v = tVector3(game.camera->mView.x, game.camera->mView.y, game.camera->mView.z);
	t = 0;
	game.shoot_time = SHOOT_TIME;
	shot->setVisible(true);
}


bool inline CollisionBoxPoint(MilkshapeModel* obj1, tVector3 point) {

	float zm = min(obj1->getTBbox().zmin, obj1->getTBbox().zmax);
	float zx = max(obj1->getTBbox().zmin, obj1->getTBbox().zmax);

	if (zm < 0)
		zm *= CH;
	else
		zm /= CH;

	if (zx > 0)
		zx *= CH;
	else
		zx /= CH;

	if (
		point.x >= min(obj1->getTBbox().xmin, obj1->getTBbox().xmax) && point.x <= max(obj1->getTBbox().xmin, obj1->getTBbox().xmax) &&
		point.y >= min(obj1->getTBbox().ymin, obj1->getTBbox().ymax) && point.y <= max(obj1->getTBbox().ymin, obj1->getTBbox().ymax) &&
		point.z >= zm && point.z <= zx
		) {
			if (point.y > (min(obj1->getTBbox().ymin, obj1->getTBbox().ymax) + 6*max(obj1->getTBbox().ymin, obj1->getTBbox().ymax)) / 7) {
				//HEADSHOT!
				//A tribute to the hours spent on Unreal Tournament
				FSOUND_PlaySound (FSOUND_FREE,game.g_headshot);
				game.setText(50, staticImages.statics[8], staticImages.statics[9]);
			}
			else
				FSOUND_PlaySound (FSOUND_FREE,game.g_next);

			return true;
		}

	return false;

}

//Nate n00b: so far, this does collision detection of the
//first bbox with the point at the CENTER of the other bbox
//seems to be fine so far
//THAT MEANS THAT THE SEQUENCE OF THE OBJECTS DOES REALLY MATTER
//probably the smaller ones should be second
bool inline CollisionTest(MilkshapeModel* obj1, MilkshapeModel* obj2) {

	if (!obj1->getVisible() || !obj2->getVisible())
		return false;

	//bounding spheres collisions
	float xc2 = (obj2->getTBbox().xmin + obj2->getTBbox().xmax) / 2;
	float yc2 = (obj2->getTBbox().ymin + obj2->getTBbox().ymax) / 2;
	float zc2 = (obj2->getTBbox().zmin + obj2->getTBbox().zmax) / 2;

	float radius2 = (obj2->getTBbox().xmin-xc2)*(obj2->getTBbox().xmin-xc2) + (obj2->getTBbox().ymin-yc2)*(obj2->getTBbox().ymin-yc2) + (obj2->getTBbox().zmin-zc2)*(obj2->getTBbox().zmin-zc2);

	float xc1 = (obj1->getTBbox().xmin + obj1->getTBbox().xmax) / 2;
	float yc1 = (obj1->getTBbox().ymin + obj1->getTBbox().ymax) / 2;
	float zc1 = (obj1->getTBbox().zmin + obj1->getTBbox().zmax) / 2;

	float radius1 = (obj1->getTBbox().xmin-xc1)*(obj1->getTBbox().xmin-xc1) + (obj1->getTBbox().ymin-yc1)*(obj1->getTBbox().ymin-yc1) + (obj1->getTBbox().zmin-zc1)*(obj1->getTBbox().zmin-zc1);

	float distance = sqrt((xc2-xc1)*(xc2-xc1) + (yc2-yc1)*(yc2-yc1) + (zc2-zc1)*(zc2-zc1)  );

	if (distance < radius1+radius2)
		return CollisionBoxPoint(obj1, tVector3(xc2, yc2, zc2));
	else
		return false;

}



bool CheckBulletCollisions() 
{
	//check for collision detection
	float xc = (shot->getTBbox().xmin + shot->getTBbox().xmax) / 2;
	float yc = (shot->getTBbox().ymin + shot->getTBbox().ymax) / 2;
	float zc = (shot->getTBbox().zmin + shot->getTBbox().zmax) / 2;

	for (int i=0; i < ENEMIES; i++)
		if (enemies[i]->getModel()->getVisible() && CollisionBoxPoint(enemies[i]->getModel(), tVector3(xc, yc, zc)))
	{
		enemies[i]->die();
		shot->setVisible(false);
		return true;
	}

	return false;

}

void moveShot() {
	//shot object
	if (game.shoot_time > 0) {

		game.shoot_time--;
		//if not star visible return
		if (!shot->getVisible())
			return;

		e = ((v-p)*t)+p;
		t = t + SHOT_STEP;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslatef(e.x,  e.y,  e.z);
		glScalef(0.01,0.01,0.01);

		shot->updateTransfMatrix();
		//shot->drawBoundingBox();

		//draw the star after t passes a point
		if (t > STAR_DRAW_AFTER)
			shot->draw();

		glPopMatrix();

		CheckBulletCollisions();

	}
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

int drawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	if ( showLoadingScreen() )
		return TRUE;

	// If we're on the splash screen, rotate the camera for a cinematic effect
	if ( game.currentState == GAMESTATE_SPLASH_START || game.currentState == GAMESTATE_SPLASH_ABOUT || 
		 game.currentState == GAMESTATE_SPLASH_EXIT  || game.currentState == GAMESTATE_ABOUT )
		game.camera->Rotate_View(0.001);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(game.camera->mPos.x,  game.camera->mPos.y,  game.camera->mPos.z,	
			  game.camera->mView.x, game.camera->mView.y, game.camera->mView.z,	
			  game.camera->mUp.x,   game.camera->mUp.y,   game.camera->mUp.z);
    
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );
	glLightfv( GL_LIGHT1, GL_SPECULAR, lightSpecular1 );
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	
	if ( game.currentState == GAMESTATE_PLAY )
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			for (int i=0; i < ENEMIES; i++)
				enemies[i]->Draw();
		glPopMatrix();

	}
	moveShot();

	drawStaticModels();

	if (game.displayText())
		staticImages.drawStatic(game.t_mask, game.t_text);	

	//finally, after the screen is drawn, draw static textures
	staticImages.drawGLStatics();

	return TRUE;
}



GLvoid killGLWindow(GLvoid)								// Properly Kill The Window
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
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;	
	wc.lpszClassName	= "OpenGL";

	if (!RegisterClass(&wc))
		return FALSE;
		
	if (fullscreen)
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
	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"OpenGL",
								title,
								dwStyle |	
								WS_CLIPSIBLINGS |	
								WS_CLIPCHILDREN,
								0, 0,	
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,
								NULL,
								hInstance,
								NULL)))
	{
		killGLWindow();								// Reset The Display
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
	
	if (!(hDC=GetDC(hWnd)) || !(PixelFormat=ChoosePixelFormat(hDC,&pfd)) ||
		!SetPixelFormat(hDC,PixelFormat,&pfd) || !(hRC=wglCreateContext(hDC)) ||
		!wglMakeCurrent(hDC,hRC))	
	{
		killGLWindow();								// Reset The Display
		MessageBox(NULL,"OpenGL initialization error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		killGLWindow();								// Reset The Display
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
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active
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
			exit(0);
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:

		  switch(wParam) 
		  {		  
			case VK_ESCAPE:
				PostQuitMessage(0);						
				break;
			case 'R':
				if ( game.currentState == GAMESTATE_PLAY && !game.rickroll_Mode)
				{
					FSOUND_Stream_Play(2,game.g_rick_stream);
					FSOUND_Stream_Stop(game.g_splash_stream);
					game.rickroll_Mode = true;
					break;
				}
				if ( game.currentState == GAMESTATE_PLAY && game.rickroll_Mode)
				{
					FSOUND_Stream_Play(1,game.g_splash_stream);
					FSOUND_Stream_Stop(game.g_rick_stream);
					game.rickroll_Mode = false;
					break;
				}
				break;
			case 'U':
				if ( game.currentState == GAMESTATE_PLAY )
					game.CharacterHealth += 5;
				if ( game.CharacterHealth > 100 )
					game.CharacterHealth = 100;
				break;
			case 'J': 
				if ( game.currentState == GAMESTATE_PLAY )
					game.CharacterHealth -= 5;
				if ( game.CharacterHealth < 0 )
					game.CharacterHealth = 0;
				break;

			case VK_SPACE:
			case VK_RETURN:
				switch(game.currentState)
				{
					case GAMESTATE_SPLASH_START:
						game.camera->Position_Camera(0, game.theMap->Height(MAP_SIZE/2, MAP_SIZE/2) - HM_DISPLACEMENT, 0, 
												  0, game.theMap->Height(MAP_SIZE/2, MAP_SIZE/2) - HM_DISPLACEMENT, 100, 0, 1, 0);
						game.setState(GAMESTATE_SELECT_PIRATE);
						break;

					case GAMESTATE_SPLASH_ABOUT:
						game.setState(GAMESTATE_ABOUT);
						break;

					case GAMESTATE_SPLASH_EXIT:
						PostQuitMessage(0);						// Send A Quit Message
						return 0;								// Jump Back
						break;

					case GAMESTATE_SELECT_PIRATE:
						game.CharacterType = PIRATE;
						shot = shot_pirate;
						game.setState(GAMESTATE_PLAY);
						for (int i=0; i<ENEMIES; i++)
							enemies[i] = new CCharacter("../models/milk/ninja.ms3d", &game,  rangedRand(0, 5), (float)rangedRand(150, 300), (float)rangedRand(150, 300));
						break;

					case GAMESTATE_SELECT_NINJA:
						game.CharacterType = NINJA;
						shot = shot_ninja;
						game.setState(GAMESTATE_PLAY);
						for (int i=0; i<ENEMIES; i++)
							enemies[i] = new CCharacter("../models/milk/dwarf.ms3d", &game,  0, (float)rangedRand(-300, -200), (float)rangedRand(-300, -200));
						break;

					case GAMESTATE_ABOUT:
						if ( !game.gameOver )
						{
							FSOUND_Stream_Play( 1, game.g_splash_stream );
							FSOUND_Stream_Stop( game.g_rick_stream );
							game.setState(GAMESTATE_SPLASH_START);
						}
						else
							exit(0);
						break;
					case GAMESTATE_END:
						game.setState(GAMESTATE_ABOUT);
						break;
				}
				break;

			case VK_UP:
			case VK_LEFT:
				switch(game.currentState)
				{
					case GAMESTATE_SPLASH_START:
						game.setState(GAMESTATE_SPLASH_EXIT);
						break;

					case GAMESTATE_SPLASH_ABOUT:
						game.setState(GAMESTATE_SPLASH_START);
						break;

					case GAMESTATE_SPLASH_EXIT:
						game.setState(GAMESTATE_SPLASH_ABOUT);
						break;

					case GAMESTATE_SELECT_PIRATE:
						game.setState(GAMESTATE_SELECT_NINJA);
						break;

					case GAMESTATE_SELECT_NINJA:
						game.setState(GAMESTATE_SELECT_PIRATE);
						break;
				}
				break;
			case VK_DOWN:
			case VK_RIGHT:
				switch(game.currentState)
				{
					case GAMESTATE_SPLASH_START:
						game.setState(GAMESTATE_SPLASH_ABOUT);
						break;

					case GAMESTATE_SPLASH_ABOUT:
						game.setState(GAMESTATE_SPLASH_EXIT);
						break;

					case GAMESTATE_SPLASH_EXIT:
						game.setState(GAMESTATE_SPLASH_START);
						break;

					case GAMESTATE_SELECT_PIRATE:
						game.setState(GAMESTATE_SELECT_NINJA);
						break;

					case GAMESTATE_SELECT_NINJA:
						game.setState(GAMESTATE_SELECT_PIRATE);
						break;
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
			switch(game.currentState)
			{
			case GAMESTATE_PLAY:
				shoot();
				break;

			case GAMESTATE_END:
				game.setState(GAMESTATE_ABOUT);
				break;

			case GAMESTATE_ABOUT:
				if ( !game.gameOver )
				{
					FSOUND_Stream_Play( 1, game.g_splash_stream );
					FSOUND_Stream_Stop( game.g_rick_stream );
					game.setState(GAMESTATE_SPLASH_START);
				}
				else
					exit(0);
				break;
			}
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
	
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		fullscreen=FALSE;

    srand( (unsigned)time( NULL ) );

	// Reset timer start tick to game start time.
	game.timer->getTicks_mS();
	game.timer->startTick = game.timer->currentTick;
	game.setState(GAMESTATE_LOADING);

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
			if ( game.currentState == GAMESTATE_PLAY)
			{
				game.handleInput(fullscreen);
				game.setGameOver();
			}
			if ((active && !drawGLScene()) || keys[VK_ESCAPE])	
				done=TRUE;		
			else
				SwapBuffers(hDC);	
		}
	}
	killGLWindow();	
	game.killAllSounds();

	for (int i=0; i<ENEMIES; i++)
		delete enemies[i];
	
	//delete dwarf;

	return (msg.wParam);
}


void drawStaticModels()
{
	glMatrixMode(GL_MODELVIEW);

	// Draw the japanese tower
	glPushMatrix();
	glTranslatef( 200, game.getHMTrans(200, 180)-8, 180);
	japaneseTower->draw();
	glPopMatrix();

	// Draw the pirate boat
	glPushMatrix();
	glTranslatef( -350, game.getHMTrans(-350, -150) + 20, -150);
	glScalef(5.0f,5.0f,5.0f);
	glRotatef(-100,0,1,0);
	pirateBoat->draw();
	glPopMatrix();

	// Draw the cannons
	glPushMatrix();
	glTranslatef( -230, game.getHMTrans(-230, -175) + 10, -175);
	glScalef(0.05, 0.05, 0.05);
	cannon->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef( -210, game.getHMTrans(-210, -170) + 10, -170);
	glScalef(0.05, 0.05, 0.05);
	glRotatef(-52,0,1,0);
	cannon->draw();
	glPopMatrix();

	// Draw the tree
	for ( int i = 0; i < NUM_TREES; i ++ )
	{
		for (int j = 0; j < NUM_TREES; j++ )
		{	
			
			Vec3d treeLoc( TreeTranslationi[NUM_TREES*i + j], 
						   game.getHMTrans(TreeTranslationi[NUM_TREES*i + j], TreeTranslationj[NUM_TREES*i + j]) + 8, 
						   TreeTranslationj[NUM_TREES*i + j]);
			Vec3d treePos( treeLoc[0] - game.camera->mPos.x, treeLoc[1] - game.camera->mPos.y, treeLoc[2] - game.camera->mPos.z);

			Vec3d camLoc( game.camera->mView.x - game.camera->mPos.x,
						  game.camera->mView.y - game.camera->mPos.y,
						  game.camera->mView.z - game.camera->mPos.z);

			// This is a quick and dirty way to figure out what trees to draw trees 
			// are ~20,000 polys so drawing a lot of them kills fps pretty quickly...
			if ( treePos * camLoc > 0 )
			{
				if ( treePos.length2() < TREE_DRAW_DIST )
				{
					glPushMatrix();
					glTranslatef( treeLoc[0], treeLoc[1], treeLoc[2] );
					tree->draw();
					glPopMatrix();
				}
			}
			else
				continue;		
		}
	}
	
	// Draw the skybox
	glDisable(GL_LIGHTING);
	drawSkybox(0,0,0,MAP_SIZE,MAP_SIZE,MAP_SIZE);
	glTranslatef(-MAP_SIZE/2.0f,-20.0f,- MAP_SIZE/2.0f);	
	game.theMap->RenderHeightMap(glMultiTexCoord2fARB, glActiveTextureARB, staticImages.heightMapTexture);
	glEnable(GL_LIGHTING);

}

void drawSkybox(float x, float y, float z, float width, float height, float length)
{
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	glPushMatrix();
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side	
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side	
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, staticImages.skybox[5]);
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


bool showLoadingScreen()
{
	if( game.currentState == GAMESTATE_LOADING )
	{
		staticImages.drawStatic(staticImages.statics[1], staticImages.statics[0]);
		if ( game.timer->getTicks_mS() <= 2000 )
			return true;
		else if ( game.timer->getTicks_mS() > 2000 && game.timer->getTicks_mS() < 3000 && !stuff_loaded)
			stuff_loaded = loadUpEverything();
		else 
		{
			if (!stuff_loaded)
				stuff_loaded = loadUpEverything();
			game.setState(GAMESTATE_SPLASH_START);
		}
		return true;
	}
	else
		return false;
}











