#pragma once

#include "MilkshapeModel.h"
#include <windows.h>					// Header File For Windows
#include <math.h>
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include "fmod.h"
#include "fmod_errors.h"
#include "vec.h"
#include <time.h>
#include "CGame.h"

class CGame;

class CCharacter
{
public:
	CCharacter(const char* filename, CGame* game, int suit, float x_i, float y_i);
	~CCharacter(void);

	Vec3d startPosition;
	Vec3d endPosition;
	Vec3d currentPosition;
	Vec3d lastPosition;
	
	float startTime;

	float rotation;

	void Draw();
	void updateCharacter();
	void setNewEndPosition();

	void wander();
	void attack();
	void defend();
	void die();
	
	float attackTime;

	// Accessor methods
	void setType(unsigned int type) { cType = type; }
	unsigned int getType()			{ return cType; }

	MilkshapeModel* getModel() { return cModel; }; 

	void setBehavior(unsigned int behavior) { cBehavior = behavior; }
	unsigned int getBehavior()				{ return cBehavior;		}

	void setState(unsigned int state) { cModel->setState(state); }

private:
	
	unsigned int	cType;		// Character type
	unsigned int	cBehavior;	// Character behaviors
	MilkshapeModel*	cModel;		// Character model
	CGame*			cGame;

	float x, y;

};
