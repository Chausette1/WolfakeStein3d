#pragma once

#include "include.hpp"
#include "player.hpp"

class Enemie
{
  public:
    Enemie(Vector2 pos, int texture_id, map_t& map, int id, Vector2 player_pos);
    ~Enemie();

    float get_x() const { return position.x; }
    float get_y() const { return position.y; }

    void move_toward_player(Player* player, map_t& map);

    bool can_attack(Player* player) const;
    void attack();
    bool is_attacking() const;
    void update_attack_animation(Player* player);

    void take_damage(int damage);
    int get_life() const { return enemie_life; }
    void set_cibled(bool cibled) { this->cibled = cibled; }
    bool is_cibled() const { return cibled; }

    int get_id() const { return id; }

  private:
    void update_texture_in_map();

    map_t* map;
    float speed = ENEMIE_STEP;
    Vector2 position;
    int texture_id;
    int enemie_life = ENEMIE_LIFE;
    int enemie_damage = ENEMIE_DAMAGE;
    int id;
    std::vector<Vector2> path_to_player;
    float last_distance_to_player = 0;
    bool attacking = false;
    int attack_tick = 0;
    bool cibled = false;
};
