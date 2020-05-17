/* ************************************************************************** */
/**
 *	@file     map.c
 *  @date     May 2020
 *  @author   E. J. Parkinson
 *
 * ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "firstPerson.h"

/* ************************************************************************** */
/** 
 * @brief Initialise the map
 *
 * @details
 * 
 * ************************************************************************** */

void
mapInit (void)
{
  struct  gameMap map = MAP_INIT;
  char   *theMap      =
    "################"
    "#...........#..#"
    "#...........#..#"
    "#......#....#..#"
    "#......#....#..#"
    "#......#....#..#"
    "#......##..##..#"
    "#...####.......#"
    "#......#.......#"
    "#......#.......#"
    "#......#####...#"
    "#........#.....#"
    "#........#.....#"
    "#........#.....#"
    "#..............#"
    "################";

  //First check that the hardcoded map is the correct size
  if ((int) strlen (theMap) != FIXED_MAP_HEIGHT * FIXED_MAP_WIDTH)
  {
    printf ("MapInit : hardcoded map has incorrect number of cells %d when %d is expected (%ix%i)\n",
            (int) strlen (theMap), FIXED_MAP_WIDTH * FIXED_MAP_HEIGHT, FIXED_MAP_WIDTH, FIXED_MAP_HEIGHT);
    exit (EXIT_FAILURE);
  }

  // Initialise map variables and store in GameConfig
  map.mapWidth       = FIXED_MAP_WIDTH;
  map.mapHeight      = FIXED_MAP_HEIGHT;
  map.mapPoints      = map.mapWidth * map.mapHeight;
  map.map            = theMap;
  gameConfig.gameMap = map;
}
