#pragma once

#include "include.hpp"

class TextureManager
{
  public:
    TextureManager();
    ~TextureManager();

    Color* get_wall_textures(int index) { return wall_texture[index]; }
    int get_wall_texture_width(int index) { return wall_texture_width[index]; }
    int get_wall_texture_height(int index) { return wall_texture_height[index]; }

    Color* get_obstacle_textures(int index) { return obstacle_texture[index]; }
    int get_obstacle_texture_width(int index) { return obstacle_texture_width[index]; }
    int get_obstacle_texture_height(int index) { return obstacle_texture_height[index]; }

    Color* get_enemy_textures(int index) { return enemies_texture[index]; }
    int get_enemy_texture_width(int index) { return enemies_texture_width[index]; }
    int get_enemy_texture_height(int index) { return enemies_texture_height[index]; }

    void load_textures();
    void unload_textures();

  private:
    std::array<Color*, SPRITE_WALL_NUM> wall_texture;

    std::array<int, SPRITE_WALL_NUM> wall_texture_width;
    std::array<int, SPRITE_WALL_NUM> wall_texture_height;

    std::array<Color*, SPRITE_OBSTACLES_NUM> obstacle_texture;

    std::array<int, SPRITE_OBSTACLES_NUM> obstacle_texture_width;
    std::array<int, SPRITE_OBSTACLES_NUM> obstacle_texture_height;

    std::array<Color*, SPRITE_ENEMY_NUM> enemies_texture;

    std::array<int, SPRITE_ENEMY_NUM> enemies_texture_width;
    std::array<int, SPRITE_ENEMY_NUM> enemies_texture_height;
};