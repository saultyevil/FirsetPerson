/* ************************************************************************** */
/**
 *	@file     Render.c
 *  @author   E. J. Parkinson
 *  @date     May 2020
 *
 * ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "SimpleFP.h"

/* ************************************************************************** */
/** 
 * @brief
 *
 * @details
 * 
 * ************************************************************************** */

void
RefreshScreen (void)
{
  int      X, Y;
  int      TestX, TestY;
  int      CeilingHeight, FloorHeight;
  bool     HitWall, HitBoundary;
  float    Distance, DistanceToWall; 
  float    EyeX, EyeY;
  float    RayAngle;
  wchar_t  Shade;

  int      ScreenWidth     = GameConfig.ScreenWidth;
  int      ScreenHeight    = GameConfig.ScreenHeight;
  int      MapWidth        = GameConfig.GameMap.MapWidth;
  int      MapHeight       = GameConfig.GameMap.MapHeight;
  float    RenderDepth     = GameConfig.RenderDepth;
  float    RayStepSize     = GameConfig.RayStepSize; 
  float    PlayerFOV       = GameConfig.PlayerFOV;
  float    PlayerX         = GameConfig.PlayerX;
  float    PlayerY         = GameConfig.PlayerY;
  float    PlayerDirection = GameConfig.PlayerDirection;
  char    *Map             = GameConfig.GameMap.Map;
  wchar_t *Screen          = GameConfig.Screen;
  WINDOW  *Window          = GameConfig.Window;

  for (X = 0; X < ScreenWidth; ++X)
  {
    RayAngle = (PlayerDirection - PlayerFOV / 2.0) + ((float) X / (float) ScreenWidth) * PlayerFOV;
    EyeX = sin (RayAngle);
    EyeY = cos (RayAngle);

    HitWall = false;
    HitBoundary = false;
    DistanceToWall = 0.0;

    // Increment Ray until it hits a wall HitBoundary
    while (!HitWall && DistanceToWall < RenderDepth)
    {
      DistanceToWall += RayStepSize;
      TestX = (int) (PlayerX + EyeX * DistanceToWall);
      TestY = (int) (PlayerY + EyeY * DistanceToWall);

      // If the Ray is out of bounds, set distance to RenderDepth and break
      if (TestX < 0 || TestX > MapWidth || TestY < 0 || TestY > MapHeight)
      {
        HitWall = true;
        DistanceToWall = RenderDepth;
      }
      // The Ray is in bounds and has hit a wall
      else
      {

        if (Map[TestY * MapWidth + TestX] == '#')
        {
          HitWall = true;
          // TODO: test for wall boundaries
        }
      }
    }

    // Shade in the wall depending on distance
    if      (DistanceToWall <= RenderDepth / 4.0) Shade = 0x2588;
    else if (DistanceToWall <= RenderDepth / 3.0) Shade = 0x2593;
    else if (DistanceToWall <= RenderDepth / 2.0) Shade = 0x2592;
    else if (DistanceToWall <= RenderDepth)       Shade = 0x2591;
    else                                          Shade = ' ';

    // Make wall boundaries stand out
    if (HitBoundary)                              Shade = ' ';

    // Calculate the distance to the ceiling and floor
    CeilingHeight = ScreenHeight / 2.0 - ScreenHeight / DistanceToWall;
    FloorHeight = ScreenHeight - CeilingHeight;
  
    for (Y = 0; Y < ScreenHeight; ++Y)
    {
      // Draw the ceiling - note that the ceiling starts at row 0
      if (Y <= CeilingHeight)
      {
        Screen[Y * ScreenWidth + X] = ' ';
        mvwprintw (Window, Y, X, "%lc", ' ');
      }
      // Draw the wall
      else if (Y > CeilingHeight && Y <= FloorHeight)
      {  
        Screen[Y * ScreenWidth + X] = Shade;
        mvwprintw (Window, Y, X, "%lc", Shade);
      }
      // Draw the floor and shade depending on distance
      else
      {
        Distance = 1.0 - ((float) Y - ScreenHeight / 2.0) / (ScreenHeight / 2.0);
        if      (Distance < 0.25) Shade = '#';
        else if (Distance < 0.50) Shade = 'x';
        else if (Distance < 0.75) Shade = '.';
        else if (Distance < 0.90) Shade = '-';
        else                      Shade = ' ';
        Screen[Y * ScreenWidth + X] = Shade; 
        mvwprintw (Window, Y, X, "%lc", Shade);
      }
    }
  }

  wrefresh (Window);
  Screen[ScreenWidth * ScreenHeight] = '\0';
  GameConfig.Screen = Screen;
}
