#pragma once

/*
Include all necessary headers for the raycaster
*/

#include "raylib.h"
#include "raymath.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
    Define all constants for the windows
*/

#define ASPECT_RATIO (16.0f / 9.0f)
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT (SCREEN_WIDTH / ASPECT_RATIO)
#define SCREEN_NAME "Raycaster"
#define MAX_FPS 60
#define FPS_INDICATOR_X 10
#define FPS_INDICATOR_Y 10

/*
    Define all math Constants for the raycaster
*/

#define PI 3.14159265358979323846f
#define DEG2RAD(deg) ((deg) * (PI / 180.0f))
#define RAD2DEG(rad) ((rad) * (180.0f / PI))

/*
    Define all constant for the raycaster
*/

#define DEFAULT_MAP "./maps/1.ray"

/*
    Define all value for the map
*/

#define MAP_TILE_EMPTY 0
#define MAP_TILE_WALL 1
#define MAP_TILE_WALL2 2
#define MAP_TILE_WALL3 3
#define MAP_TILE_WALL4 4
#define PLAYER_ORIENTATION_NORTH 5
#define PLAYER_ORIENTATION_SOUTH 6
#define PLAYER_ORIENTATION_WEST 7
#define PLAYER_ORIENTATION_EAST 8
#define MAP_IGNOR 9
#define MAP_ERROR 10

/*
    Define all player constants for the raycaster
*/
#define PLAYER_FOV DEG2RAD(70)
#define PLAYER_STEP 10
#define PLAYER_ROT_STEP DEG2RAD(5.0f)
#define PLAYER_SIZE_ON_MINI_MAP 8

/*
    Define constant about mini-map
*/

#define MINI_MAP_TILE_SIZE 64
#define MINI_MAP_MAX_X (SCREEN_WIDTH / MINI_MAP_TILE_SIZE)
#define MINI_MAP_MAX_Y (SCREEN_HEIGHT / MINI_MAP_TILE_SIZE)

/*
    Define all structs for the raycaster
*/

typedef struct map {
  int width;
  int height;
  std::vector<std::vector<u_int8_t>> data;
  std::string name;
} map_t;
