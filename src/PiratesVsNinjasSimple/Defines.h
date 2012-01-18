#pragma once 

#define		CAMERASPEED			0.015f			// The Camera Speed
#define		MAP_SIZE			1024
#define		STEP_SIZE			16				// This controls the resolution of the terrain. 
#define		HM_DISPLACEMENT		10				// A hack magic number to position models correctly w.r.t. the heightmap along the y-axis
#define		NUM_TREES			10
#define		TREE_DRAW_DIST		100000

#define		SHOT_STEP			0.2
#define		SHOOT_TIME			150
#define		CROSS_RADIUS		15

#define		TEXT_TIME			40

#define		MAX_ENEMIES			25				// Maximum number of permissible enemies.
#define		ENEMIES				25				// Number of enemies actually generated.
#define		ENEMIES_KILLED_WIN	ENEMIES			// Number of enemies you must kill to win.
#define		CH					3				// Mihali, I can't believe you used 'CH' as a define name =P.

#define		NO_ANIMATION		-1
#define		NO_LOOP				0
#define		LOOP				1

#define		STAR_DRAW_AFTER		2*SHOT_STEP

#define		DEST_RADIUS			20				// NPC decides he's at his destination when within this radius.
#define		ATTACK_RADIUS		40				// NPC decides to attack when within this radius of player.
#define		ATTACK_TIME			1000			// Number of milliseconds between attacks.

// Ninja states
enum {NINJA_WALKING, NINJA_ATTACK, NINJA_DEAD, NINJA_IDLE};

// For some reason this isn't defined anywhere else, needed to make texture borders disappear.
#ifndef		GL_CLAMP_TO_EDGE
#define		GL_CLAMP_TO_EDGE        0x812F
#endif

// Game State Machine
enum {GAMESTATE_LOADING, GAMESTATE_SPLASH_START, GAMESTATE_SPLASH_ABOUT, GAMESTATE_SPLASH_EXIT, GAMESTATE_ABOUT, GAMESTATE_SELECT_NINJA, 
	  GAMESTATE_SELECT_PIRATE, GAMESTATE_PLAY, GAMESTATE_DEBUG, GAMESTATE_END}; 
enum {YOU_LOSE, YOU_WIN};

// Character enums
enum {PIRATE, NINJA};
enum {WANDER, DEFENSIVE, AGGRESSIVE, DEAD}; 
