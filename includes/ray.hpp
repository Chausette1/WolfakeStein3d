#pragma once

#include "include.hpp"
class Player;
class TextureManager;

class MyRay
{
  private:
    float distance;
    WallSide wall_side;
    MapTile wall_type;
    bool is_cast;
    Vector2 ray_dir;
    double wall_x;
    int tex_num;
    int tex_x;

  public:
    MyRay();
    void cast(const Player& player, const map_t& map, Vector2 ray_dir = { 0, 0 });
    void draw();
    void draw_line(int line_x,
                   std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                   TextureManager* texture_manager);
};