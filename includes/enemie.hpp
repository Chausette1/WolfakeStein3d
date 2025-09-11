#pragma once

#include "include.hpp"
#include "player.hpp"

class Enemie
{
  public:
    Enemie(Vector2 pos, int texture_id, map_t& map, int id, Vector2 player_pos);
    ~Enemie();

    void move_toward_player(Player* player, map_t& map);

    void take_damage(int damage);

  private:
    void update_texture_in_map();

    map_t* map;
    float speed = ENEMIE_STEP;
    Vector2 position;
    int textureID;
    int enemie_life = ENEMIE_LIFE;
    int enemie_damage = ENEMIE_DAMAGE;
    int id;
    std::vector<Vector2> path_to_player;
    float last_distance_to_player = 0;
};
