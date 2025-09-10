#pragma once

#include "include.hpp"
#include "player.hpp"

class Enemie
{
  public:
    Enemie(Vector2 pos, int texture_id, map_t& map);
    ~Enemie();

    void move_toward_player(Player* player, map_t& map);

  private:
    void update_texture_in_map();

    map_t* map;
    float speed = ENEMIE_STEP;
    Vector2 position;
    int textureID;
};
