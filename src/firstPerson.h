/* ************************************************************************** */
/**
 *	@file     firstPerson.h
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <curses.h>

/* ************************************************************************** 
 * Map structure
 * ************************************************************************** */

#define FIXED_MAP_WIDTH  16
#define FIXED_MAP_HEIGHT 16

struct gameMap
{
	int      mapWidth;                  // The width of the map
	int      mapHeight;                 // The height of the map
	int      mapPoints;                 // The number of map points (width * height)
	char    *map;                       // The map stored as a 1D whcar_t array
};

#define MAP_INIT {0, 0, 0, NULL}

/* ************************************************************************** 
 * Global configuration structure
 * ************************************************************************** */

struct gameConfig
{
	int             screenWidth;        // Terminal number of columns
	int             screenHeight;       // Terminal number of rows
  wchar_t        *screen;             // Screen buffer
  WINDOW         *window;             // The window to draw to
  float           renderDepth;        // Maximum rendering depth for ray
  float           rayStepSize;        // The step size for ray casting
  float           playerFOV;          // Player field of view
  float           playerX;            // Player X position
  float           playerY;            // Player Y position
  float           playerDirection;    // Player direction
  float           playerSpeed;        // Player walking speed
  struct gameMap  gameMap;            // Structure for the game map
} gameConfig;

#include "functions.h"
