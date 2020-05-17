/* ************************************************************************** */
/**
 *  @file     render.c
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <wchar.h>
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
  int      boundaryTestX, boundaryTestY;
  int      boundaryIndex;
  bool     hitWall, hitBoundary;
  float    distanceToFloor, distanceToWall;
  float    distance, dotProduct;
  float    eyeX, eyeY;
  float    rayAngle;
  float    vX, vY;
  wchar_t  shade;
  struct   bTest boundaryTest[N_BOUNDARY_TESTS];

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
  float    boundLimit      = 0.005;
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
        // Now test to see if the Ray has hit a  boundary of a block
        if (map[testY * mapWidth + testX] == '#')
        {
          hitWall = true;

          // To find boundaries, cast a ray to each corner of a block and
          // measure the angle between this ray and the player's ray
          boundaryIndex = 0;
          
          for (boundaryTestX = 0; boundaryTestX < 2; ++boundaryTestX)
          {
            for (boundaryTestY = 0; boundaryTestY < 2; ++boundaryTestY)
            {
              vY         = (float) testY + boundaryTestY - playerY;
              vX         = (float) testX + boundaryTestX - playerX;
              distance   = sqrt (vX * vX + vY * vY);
              dotProduct = (eyeX * vX / distance) + (eyeY * vY / distance);
              boundaryTest[boundaryIndex].distance   = distance;
              boundaryTest[boundaryIndex].dotProduct = dotProduct;
              boundaryIndex++;
            }

            // Sort from closest to farthest
            sortBoundaryTest (boundaryTest);

            // If the angle is less than some predefined limit, the ray is at
            // a boundary. Note, the player can never see all four corners
            if (acos (boundaryTest[0].dotProduct) < boundLimit) hitBoundary = true;
            if (acos (boundaryTest[1].dotProduct) < boundLimit) hitBoundary = true;
            if (acos (boundaryTest[2].dotProduct) < boundLimit) hitBoundary = true;
          }                  
        }
      }
    }

    // Shade in the wall depending on distance
    if      (distanceToWall <= renderDepth / 4.0) shade = 0x2588;
    else if (distanceToWall <= renderDepth / 3.0) shade = 0x2593;
    else if (distanceToWall <= renderDepth / 2.0) shade = 0x2592;
    else if (distanceToWall <= renderDepth)       shade = 0x2591;
    else                                          shade = ' ';

    // Make wall boundaries stand out
    if (hitBoundary)                              shade = ' ';

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
        distanceToFloor = 1.0 - ((float) y - screenHeight / 2.0) / (screenHeight / 2.0);
        if      (distanceToFloor < 0.25) shade = '#';
        else if (distanceToFloor < 0.50) shade = 'x';
        else if (distanceToFloor < 0.75) shade = '.';
        else if (distanceToFloor < 0.90) shade = '-';
        else                             shade = ' ';
        screen[y * screenWidth + x] = shade;
        mvwprintw (window, y, x, "%lc", shade);
      }
    }
  }

  // Add map to the top right of the screen 
  for (x = 0; x < mapWidth; ++x)
  {
    for (y = 0; y < mapHeight; ++y)
    {
      mvwprintw (window, y, x, "%c", map[y * mapWidth + x]);
    }
  }

  // Add P on the map to show where the player is
  mvwprintw (window, (int) playerY, (int) playerX, "P");

  // Refresh the NCurses window and NULL terminate the screen buffer
  wrefresh (window);
  screen[screenWidth * screenHeight] = '\0';
  gameConfig.screen = screen;
}
