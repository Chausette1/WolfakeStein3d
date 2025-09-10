#pragma once

/*
Include all necessary headers for the raycaster
*/

#include <algorithm>
#include <array>
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
constexpr const char* SCREEN_NAME = "Raycaster";
constexpr u_int8_t MAX_FPS = 60;
constexpr int FPS_INDICATOR_X = 10;
constexpr int FPS_INDICATOR_Y = 10;
inline u_int8_t ACTION_KEY_DELAY = 4; // in frames

/*
Define all math Constants for the raycaster
*/

constexpr float MY_PI = 3.14159265358979323846f;
constexpr float
Deg2Rad(float deg)
{
    return deg * (MY_PI / 180.0f);
}
constexpr float
Rad2Deg(float rad)
{
    return rad * (180.0f / MY_PI);
}
constexpr Vector2
ROTATE_MAT_2D(float angle, Vector2 vec)
{
    return { (cos(angle) * vec.x) - (sin(angle) * vec.y),
             (sin(angle) * vec.x) + (cos(angle) * vec.y) };
}

/*
    Define all constant for the raycaster
*/

constexpr Color FLOOR_COLOR = GRAY;
constexpr Color CEILING_COLOR = SKYBLUE;
constexpr Color WALL1_COLOR = RED;
constexpr Color WALL2_COLOR = GREEN;
constexpr Color WALL3_COLOR = BLUE;
constexpr Color WALL4_COLOR = YELLOW;
constexpr Color WALL5_COLOR = MAGENTA;
constexpr Color WALL6_COLOR = SKYBLUE;
constexpr Color WALL7_COLOR = ORANGE;
constexpr Color WALL8_COLOR = PURPLE;

constexpr const char* MAPS[] = { "./maps/1.ray", "./maps/2.ray", "./maps/3.ray",
                                 "./maps/4.ray", "./maps/5.ray", "./maps/6.ray",
                                 "./maps/7.ray", "./maps/8.ray", "./maps/9.ray" };
constexpr const int MAP_CONT = sizeof(MAPS) / sizeof(MAPS[0]);

constexpr const char* WALL_TEXTURES[] = {
    "./assets/textures/wall1.png", "./assets/textures/wall2.png", "./assets/textures/wall3.png",
    "./assets/textures/wall4.png", "./assets/textures/wall5.png", "./assets/textures/wall6.png",
    "./assets/textures/wall7.png", "./assets/textures/wall8.png"
};

constexpr int SPRITE_WALL_NUM = sizeof(WALL_TEXTURES) / sizeof(WALL_TEXTURES[0]);

constexpr const char* SPRITE_OBSTACLES[] = { "./assets/textures/obstacle1.png",
                                             "./assets/textures/obstacle2.png" };

constexpr int SPRITE_OBSTACLES_NUM = sizeof(SPRITE_OBSTACLES) / sizeof(SPRITE_OBSTACLES[0]);

constexpr const char* SPRITE_ENEMY[] = { "./assets/textures/enemie1.png" };

constexpr int SPRITE_ENEMY_NUM = sizeof(SPRITE_ENEMY) / sizeof(SPRITE_ENEMY[0]);

inline float VISION_SCALE = 0.5f;

constexpr const char* MUSIC = "./assets/sounds/music.wav";

/*
    Define all value for the map
*/

enum class MapTile
{
    Empty = 0,
    Wall = 1,
    Wall2 = 2,
    Wall3 = 3,
    Wall4 = 4,
    Wall5 = 5,
    Wall6 = 6,
    Wall7 = 7,
    Wall8 = 8,
    Player_North = 9,
    Player_South = 10,
    Player_West = 11,
    Player_East = 12,
    Ignore = 13,
    Error = 14
};

enum class WallSide
{
    horizontal = 0,
    vertical = 1,
    none = 2
};
/*
    Define all player constants for the raycaster
*/
constexpr int PLAYER_FOV = 69;
constexpr int PLAYER_STEP = 10;
constexpr int PLAYER_SIZE_ON_MINI_MAP = 8;
constexpr int PLAYER_HITBOX_SIZE = 10;
constexpr int LIFE_POINTS = 100;

/*
    Define all enemie constants for the raycaster
*/
constexpr float ENEMIE_STEP = 0.1f;

/*
    Define constant about mini-map
*/

constexpr int MINI_MAP_TILE_SIZE = 64;

/*
    Define sprite types
*/

enum class SpriteType
{
    Enemy,
    Item,
    Obstacle1,
    Obstacle2,
};

/*
    Define all structs for the raycaster
*/

typedef struct sprite
{
    Vector2 position;
    SpriteType type;
    bool visible;
} sprite_t;

typedef struct map
{
    int width;
    int height;
    std::vector<std::vector<MapTile>> data;
    std::string name;
    std::vector<sprite_t*> sprites;
} map_t;
