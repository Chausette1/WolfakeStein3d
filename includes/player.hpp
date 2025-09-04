#pragma once

#include "include.hpp"
#include "ray.hpp"

class Player {
  public:
    Player(map_t &map);
    ~Player();

    int get_x() const { return static_cast<int>(player_pos.x); }
    int get_y() const { return static_cast<int>(player_pos.y); }

    void move();
    void rotate(bool right);

    void castRays(); // usable when one ray works

    void draw() const;

  private:
    Vector2 player_pos;
    float player_speed = PLAYER_STEP;
    float player_fov = PLAYER_FOV;
    Vector2 player_dir;
    Vector2 player_plane;
    map_t *map;
    std::vector<MyRay *> rays;
};
