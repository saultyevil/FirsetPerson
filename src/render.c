/* ************************************************************************** */
/**
 *	@file     render.c
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "firstPerson.h"

/* ************************************************************************** */
/** 
 * @brief
 *
 * @details
 * 
 * ************************************************************************** */

void
refreshScreen (void)
{
  int      x, y;
  int      testX, testY;
  int      ceilingHeight, floorHeight;
  bool     hitWall, hitBoundary;
  float    distance, distanceToWall;
  float    eyeX, eyeY;
  float    rayAngle;
  wchar_t  shade;

  int      screenWidth     = gameConfig.screenWidth;
  int      screenHeight    = gameConfig.screenHeight;
  int      mapWidth        = gameConfig.gameMap.mapWidth;
  int      mapHeight       = gameConfig.gameMap.mapHeight;
  float    renderDepth     = gameConfig.renderDepth;
  float    rayStepSize     = gameConfig.rayStepSize;
  float    playerFOV       = gameConfig.playerFOV;
  float    playerX         = gameConfig.playerX;
  float    playerY         = gameConfig.playerY;
  float    playerDirection = gameConfig.playerDirection;
  char    *map             = gameConfig.gameMap.map;
  wchar_t *screen          = gameConfig.screen;
  WINDOW  *window          = gameConfig.window;

  for (x = 0; x < screenWidth; ++x)
  {
    rayAngle = (playerDirection - playerFOV / 2.0) + ((float) x / (float) screenWidth) * playerFOV;
    eyeX = sin (rayAngle);
    eyeY = cos (rayAngle);

    hitWall = false;
    hitBoundary = false;
    distanceToWall = 0.0;

    // Increment Ray until it hits a wall HitBoundary
    while (!hitWall && distanceToWall < renderDepth)
    {
      distanceToWall += rayStepSize;
      testX = (int) (playerX + eyeX * distanceToWall);
      testY = (int) (playerY + eyeY * distanceToWall);

      // If the Ray is out of bounds, set distance to renderDepth and break
      if (testX < 0 || testX > mapWidth || testY < 0 || testY > mapHeight)
      {
        hitWall = true;
        distanceToWall = renderDepth;
      }
      // The Ray is in bounds and has hit a wall
      else
      {

        if (map[testY * mapWidth + testX] == '#')
        {
          hitWall = true;
          // TODO: test for wall boundaries
        }
      }
    }

    // Shade in the wall depending on distance
    if      (distanceToWall <= renderDepth / 4.0) shade = 0x2588;
    else if (distanceToWall <= renderDepth / 3.0) shade = 0x2593;
    else if (distanceToWall <= renderDepth / 2.0) shade = 0x2592;
    else if (distanceToWall <= renderDepth) shade = 0x2591;
    else shade = ' ';

    // Make wall boundaries stand out
    if (hitBoundary) shade = ' ';

    // Calculate the distance to the ceiling and floor
    ceilingHeight = screenHeight / 2.0 - screenHeight / distanceToWall;
    floorHeight = screenHeight - ceilingHeight;

    for (y = 0; y < screenHeight; ++y)
    {
      // Draw the ceiling - note that the ceiling starts at row 0
      if (y <= ceilingHeight)
      {
        screen[y * screenWidth + x] = ' ';
        mvwprintw (window, y, x, "%lc", ' ');
      }
      // Draw the wall
      else if (y > ceilingHeight && y <= floorHeight)
      {
        screen[y * screenWidth + x] = shade;
        mvwprintw (window, y, x, "%lc", shade);
      }
      // Draw the floor and shade depending on distance
      else
      {
        distance = 1.0 - ((float) y - screenHeight / 2.0) / (screenHeight / 2.0);
        if      (distance < 0.25) shade = '#';
        else if (distance < 0.50) shade = 'x';
        else if (distance < 0.75) shade = '.';
        else if (distance < 0.90) shade = '-';
        else shade = ' ';
        screen[y * screenWidth + x] = shade;
        mvwprintw (window, y, x, "%lc", shade);
      }
    }
  }

  wrefresh (window);
  screen[screenWidth * screenHeight] = '\0';
  gameConfig.screen = screen;
}
