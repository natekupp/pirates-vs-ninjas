#include "CCharacter.h"

#include <fstream>

using namespace std;

CCharacter::CCharacter(const char* filename, CGame* game, int suit, float x_i, float y_i)
{
	cGame = game;

	x = x_i;
	y = y_i;

	cModel = new MilkshapeModel();
	if ( cModel->loadModelData( filename ) == false )
	{
		MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
		exit(0);
	}

	if (cGame->CharacterType == PIRATE) {

		cModel->setSuite(suit);
		cModel->addState(1, 14, LOOP);			// NINJA_WALKING
		cModel->addState(45,59,LOOP);			// NINJA_ATTACK
		cModel->addState(166, 173, NO_LOOP);	// NINJA_DEAD
		cModel->addState(184,205, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); //nate n00b if visible is TRUE then collision detection is applied
								  //doesn't do anything about the actual visibility of the object

		cBehavior	= AGGRESSIVE;
		cType		= NINJA;

	}
	else {

		cModel->setSuite(0);
		cModel->addState(2, 14, LOOP);			// NINJA_WALKING
		cModel->addState(112, 126,LOOP);		// NINJA_ATTACK
		cModel->addState(230, 251, NO_LOOP);	// NINJA_DEAD
		cModel->addState(292, 325, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); //nate n00b if visible is TRUE then collision detection is applied
								  //doesn't do anything about the actual visibility of the object

		cBehavior	= AGGRESSIVE;
		cType		= PIRATE;

	}

	currentPosition[0] = x;
	currentPosition[2] = y;
	currentPosition[1] = cGame->getHMTrans(x,y)+10;
	setNewEndPosition();

	attackTime = (float)cGame->timer->getTicks_mS();
}

CCharacter::~CCharacter(void)
{
	delete cModel;
}



void CCharacter::Draw()
{
	// Decide what the character is doing, then draw that.
	switch(cBehavior)
	{
		case WANDER:
			wander();
			break;
		case AGGRESSIVE:
			attack();
			break;
		case DEFENSIVE:
			defend();
			break;
		case DEAD:
			//do nothing
			break;
		default:
			break;
	}

	// put our movements over the past dt into gl form
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(currentPosition[0], currentPosition[1], currentPosition[2]);
	glRotatef(rotation, 0,1,0);

	//dwarf model is bigger than the ninja, so needs scaling
	if (cGame->CharacterType == NINJA)
		glScalef(0.18, 0.2, 0.18);

	//MUST call this function for updating collision detection matrices
	//this function must be called after ALL tranformations are applied
	cModel->updateTransfMatrix();

	//debugging purposes
	//cModel->drawBoundingBox();
	cModel->draw();

	glPopMatrix();
}

void CCharacter::die()
{
	cModel->setState(NINJA_DEAD);
	cModel->setVisible(false);
	cBehavior = DEAD;
	cGame->numEnemiesKilled++;
	FSOUND_PlaySound (FSOUND_FREE,cGame->g_death);
}


void CCharacter::wander()
{
	cModel->setState(NINJA_WALKING);

	lastPosition = currentPosition;		// save the last spot we were at
	
	// decide whether we've reached our destination point
	Vec3d check = endPosition - currentPosition;
	if ( check.length() < DEST_RADIUS )
		setNewEndPosition();	// Update destination point
	
	Vec3d delta = endPosition - startPosition;
	delta.normalize();
	float t = ((float)cGame->timer->getTicks_mS() - startTime)/80.0;
	
	currentPosition = startPosition + delta * t;
	currentPosition[1] = cGame->getHMTrans((float)currentPosition[0],(float)currentPosition[2])+9;
	
	Vec3d newDirection = (currentPosition - lastPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = -90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = -90 + 180 / PI * acosf( (float)newDirection[0] );
}

void CCharacter::attack()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		defend();
	}
	else
		wander();
}

void CCharacter::defend()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);

	// decide whether we've reached our destination point
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		cModel->setState(NINJA_ATTACK);
		if ( cGame->timer->getTicks_mS() - attackTime > ATTACK_TIME )
		{			
			cGame->CharacterHealth -= 10;	// comment this out for invulnerability
			attackTime = (float)cGame->timer->getTicks_mS();
			FSOUND_PlaySound (FSOUND_FREE,cGame->g_attack);
		}
	}
	else
		cModel->setState(NINJA_IDLE);
	
	// make the ninja look at the camera
	Vec3d newDirection = (currentPosition - cameraPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = 90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = 90 + 180 / PI * acosf( (float)newDirection[0] );

}

void CCharacter::setNewEndPosition()
{
	if ( cGame->CharacterType == PIRATE )
	{
		endPosition[0] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	else
	{
		endPosition[0] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	startPosition = currentPosition;
	startTime = (float)cGame->timer->getTicks_mS();
}