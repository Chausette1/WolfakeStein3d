#pragma once

#include "include.hpp"
#include "ray.hpp"
#include "texture.hpp"

class Player
{
  public:
    Player(map_t& map);
    ~Player();

    bool load_map(map_t& map);

    float get_x() const { return player_pos.x; }
    float get_y() const { return player_pos.y; }

    void move();
    void rotate(bool right);

    void castRays(); // usable when one ray works

    void draw() const;
    void draw_vision(std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                     TextureManager* texture_manager) const;

  private:
    Vector2 player_pos;
    float player_speed = PLAYER_STEP;
    float player_fov = PLAYER_FOV;
    Vector2 player_dir;
    Vector2 player_plane;
    map_t* map;
    std::vector<MyRay*> rays;
};
