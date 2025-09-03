#pragma once

/*
Include all necessary headers for the raycaster
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "raylib.h"
#include "raymath.h"

/*
    Define all constants for the windows
*/

constexpr int SCREEN_WIDTH = 800;
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH / ASPECT_RATIO);
constexpr const char* SCREEN_NAME = "Raycaster";
constexpr u_int8_t MAX_FPS = 60;
constexpr int FPS_INDICATOR_X = 10;
constexpr int FPS_INDICATOR_Y = 10;
constexpr u_int8_t ACTION_KEY_DELAY = 6;  // in frames

/*
    Define all math Constants for the raycaster
*/

constexpr float MY_PI = 3.14159265358979323846f;
constexpr float Deg2Rad(float deg) { return deg * (MY_PI / 180.0f); }
constexpr float Rad2Deg(float rad) { return rad * (180.0f / MY_PI); }

/*
    Define all constant for the raycaster
*/

constexpr const char* DEFAULT_MAP = "./maps/1.ray";

/*
    Define all value for the map
*/

enum class MapTile {
  Empty = 0,
  Wall = 1,
  Wall2 = 2,
  Wall3 = 3,
  Wall4 = 4,
  Player_North = 5,
  Player_South = 6,
  Player_West = 7,
  Player_East = 8,
  Ignore = 9,
  Error = 10
};
/*
    Define all player constants for the raycaster
*/
constexpr float PLAYER_FOV = 70.0f * (3.14159265358979323846f / 180.0f);
constexpr int PLAYER_STEP = 10;
constexpr float PLAYER_ROT_STEP = 5.0f * (3.14159265358979323846f / 180.0f);
constexpr int PLAYER_SIZE_ON_MINI_MAP = 8;

/*
    Define constant about mini-map
*/

constexpr int MINI_MAP_TILE_SIZE = 64;

/*
    Define all structs for the raycaster
*/

typedef struct map {
  int width;
  int height;
  std::vector<std::vector<MapTile>> data;
  std::string name;
} map_t;
