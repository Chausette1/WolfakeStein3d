#pragma once

#include "include.hpp"
class Player;

class MyRay {
  private:
    float distance;
    WallSide wall_side;
    MapTile wall_type;
    bool is_cast;
    Vector2 ray_dir;

  public:
    MyRay();
    ~MyRay();
    void cast(const Player &player, const map_t &map, Vector2 ray_dir = {0, 0});
    void draw();
};