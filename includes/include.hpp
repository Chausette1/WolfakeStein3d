#pragma once

/*
Include all necessary headers for the raycaster
*/

#include <fstream>
#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

/*
    Define all constants for the windows
*/

constexpr int SCREEN_WIDTH = 800;
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr int SCREEN_HEIGHT = static_cast<int>(SCREEN_WIDTH / ASPECT_RATIO);
constexpr const char *SCREEN_NAME = "Raycaster";
constexpr u_int8_t MAX_FPS = 60;
constexpr int FPS_INDICATOR_X = 10;
constexpr int FPS_INDICATOR_Y = 10;
inline u_int8_t ACTION_KEY_DELAY = 4; // in frames

/*
Define all math Constants for the raycaster
*/

constexpr float MY_PI = 3.14159265358979323846f;
constexpr float Deg2Rad(float deg) { return deg * (MY_PI / 180.0f); }
constexpr float Rad2Deg(float rad) { return rad * (180.0f / MY_PI); }
constexpr Vector2 ROTATE_MAT_2D(float angle, Vector2 vec) {
    return {(cos(angle) * vec.x) - (sin(angle) * vec.y), (sin(angle) * vec.x) + (cos(angle) * vec.y)};
}

/*
    Define all constant for the raycaster
*/

constexpr Color FLOOR_COLOR = DARKGRAY;
constexpr Color CEILING_COLOR = GRAY;
constexpr Color WALL1_V_COLOR = {126, 0, 0, 255};
constexpr Color WALL1_H_COLOR = RED;
constexpr Color WALL2_V_COLOR = {0, 126, 0, 255};
constexpr Color WALL2_H_COLOR = GREEN;
constexpr Color WALL3_V_COLOR = {0, 0, 126, 255};
constexpr Color WALL3_H_COLOR = BLUE;
constexpr Color WALL4_V_COLOR = {126, 126, 0, 255};
constexpr Color WALL4_H_COLOR = YELLOW;
constexpr const char *DEFAULT_MAP = "./maps/7.ray";
constexpr float VISION_SCALE = 0.5f;

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

enum class WallSide { horizontal = 0, vertical = 1, none = 2 };
/*
    Define all player constants for the raycaster
*/
constexpr int PLAYER_FOV = 69;
constexpr int PLAYER_STEP = 10;
constexpr float PLAYER_ROT_STEP = 5.0f * (3.14159265358979323846f / 180.0f);
constexpr int PLAYER_SIZE_ON_MINI_MAP = 8;
constexpr int PLAYER_HITBOX_SIZE = 10;

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
