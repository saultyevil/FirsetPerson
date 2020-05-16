/* ************************************************************************** */
/**
 *	@file     fps.h
 *  @author   E. J. Parkinson
 *  @date     May 2020
 *
 * ************************************************************************** */

#include <curses.h>

/* ************************************************************************** 
 * Map structure
 * ************************************************************************** */

#define FIXED_MAP_WIDTH  16
#define FIXED_MAP_HEIGHT 16

struct GameMap
{
	int   MapWidth;
	int   MapHeight;
	int   MapPoints;
	char *Map;
};

#define MAP_INIT {0, 0, 0, NULL}

/* ************************************************************************** 
 * Global configuration structure
 * ************************************************************************** */

#define MAX_FPS 60

struct GameConfig
{
	int             ScreenWidth;        // Terminal number of columns
	int             ScreenHeight;       // Terminal number of rows
	wchar_t        *Screen;             // Screen buffer 
    WINDOW         *Window;             // The window to draw to
    float           RenderDepth;        // Maximum rendering depth for ray
    float           RayStepSize;        // The step size for ray casting
    float           PlayerFOV;          // Player field of view
    float           PlayerX;            // Player X position
    float           PlayerY;            // Player Y position
    float           PlayerDirection;    // Player direction
    float           PlayerSpeed;        // Player walking speed
	struct GameMap  GameMap;            // Structure for the game map
} GameConfig;

#include "Functions.h"
