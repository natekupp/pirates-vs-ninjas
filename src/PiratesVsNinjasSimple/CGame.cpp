#include "CGame.h"

CGame::CGame(void)
{
	timer				= new CTimer();
	camera				= new CCamera();
	theMap				= new CHeightMap();
	
	
	// Initialize game state, character stats, camera
	currentState		= GAMESTATE_LOADING; // See Defines.h for the enumeration of game states.
	gameOver			= false;
	rickroll_Mode		= false;
	
	shoot_time			= 0;
	CharacterHealth		= 100;
	CharacterType		= PIRATE;
	numEnemiesKilled	= 0;
	CharacterWinLose	= YOU_LOSE;

	camera->Position_Camera(0.0f, getHMTrans(0, 0) + 70.0f, 0.0f,	
						    0.0f, getHMTrans(0, 0) + 70.0f, -1.0f,
							0.0f, 1.0f, 0.0f);
}

CGame::~CGame(void)
{
	delete timer;
	delete camera;
	delete theMap;
}

void CGame::initializeGameSounds()
{
	// initialize fmod, 44000 Hz, 64 channels
	FSOUND_Init(44000,64,0);

	g_splash_stream = FSOUND_Stream_Open( "../sounds/Barbossa.mp3",				FSOUND_2D , 0 , 0 );
	g_rick_stream   = FSOUND_Stream_Open( "../sounds/NeverGonnaGiveYouUp.mp3" , FSOUND_2D , 0 , 0 );
	g_lose			= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/Death.wav",	0,0,0);
	g_win			= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/Yeah_baby.wav",0,0,0);
	g_headshot		= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/headshot2.wav",0,0,0);
	g_death			= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/Death.wav",	0,0,0);
	g_attack		= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/Ha.wav",	0,0,0);
	g_next			= FSOUND_Sample_Load (FSOUND_FREE,"../sounds/Who_is_next.wav",	0,0,0);
	FSOUND_Stream_Play(1,g_splash_stream);
	FSOUND_Stream_SetLoopCount(g_splash_stream, -1);
}

void CGame::killAllSounds()
{
	FSOUND_Stream_Close(  g_splash_stream );
	FSOUND_Stream_Close(  g_rick_stream );
}

void CGame::setState(int newState)
{
	currentState = newState;

	switch(newState) {

		case GAMESTATE_END:
			FSOUND_Stream_Stop( g_rick_stream );
			FSOUND_Stream_Stop( g_splash_stream );
			if ( CharacterWinLose == YOU_WIN )
				FSOUND_PlaySound (0,g_win);
			else
				FSOUND_PlaySound (0,g_lose);
			break;
		case GAMESTATE_ABOUT:
			FSOUND_Stream_Play( 1, g_rick_stream );
			break;

		default:
			break;
	}
}

void CGame::setGameOver()
{

	if ( CharacterHealth <= 0 )
	{
		gameOver = true;
		CharacterWinLose = YOU_LOSE;
		setState(GAMESTATE_END);
	}
	else if ( numEnemiesKilled >= ENEMIES_KILLED_WIN )
	{
		gameOver = true;
		CharacterWinLose = YOU_WIN;
		setState(GAMESTATE_END);
	}
}

int CGame::getHMTrans(float x, float y)
{
	return theMap->Height(x + int(MAP_SIZE/2), y + int(MAP_SIZE/2)) - HM_DISPLACEMENT - 20;
}

void CGame::handleInput(bool fullscreen)
{
	keyboardInput();
	camera->Mouse_Move(640,480, fullscreen);
}

void CGame::keyboardInput()
{
	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80))
		camera->Move_Camera( CAMERASPEED, theMap);

	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80))
		camera->Move_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80))
		camera->Strafe_Camera(-CAMERASPEED, theMap);

	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80))
		camera->Strafe_Camera( CAMERASPEED, theMap);
}

void CGame::setText(int time, GLuint mask, GLuint text) {

	text_time = time;
	t_mask = mask;
	t_text = text;

}

bool CGame::displayText() {

	if (text_time > 0) {
		text_time--;
		return true;
	}

	return false;

}