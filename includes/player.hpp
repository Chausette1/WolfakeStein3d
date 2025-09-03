#pragma once

#include "include.hpp"

class Player {
 public:
  Player(map_t &map);
  ~Player();

  int get_x() const { return static_cast<int>(player_x); }
  int get_y() const { return static_cast<int>(player_y); }

  void move();
  void rotate(bool right);

  void draw() const;

 private:
  float player_x;
  float player_y;
  float player_speed = PLAYER_STEP;
  float player_fov = PLAYER_FOV;
  float player_dir;
  map_t *map;
};
