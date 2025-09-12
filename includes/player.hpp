#pragma once

#include "include.hpp"
#include "ray.hpp"
#include "texture.hpp"

class Enemie;

class Player
{
  public:
    Player(map_t& map, std::array<float, SCREEN_WIDTH>* zBuffer);
    ~Player();

    bool load_map(map_t& map, std::array<float, SCREEN_WIDTH>* zBuffer);

    float get_x() const { return player_pos.x; }
    float get_y() const { return player_pos.y; }
    std::array<float, SCREEN_WIDTH>* get_buffer() const { return zBuffer; }
    Vector2 get_dir() const { return player_dir; }
    Vector2 get_plane() const { return player_plane; }
    int get_life() const { return life; }

    void move(bool forward);
    void rotate(bool right);

    void take_damage(int damage) { life -= damage; }
    void heal(int heal) { life += heal; }
    void upgrade_damage(int amount) { damage += amount; }

    bool can_attack(const Enemie* enemy) const;
    void attack(Enemie* enemy);
    bool is_attacking() const;
    float get_attack_animation(Enemie* enemy);

    void castRays();

    void draw() const;
    void render_vision(std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                       TextureManager* texture_manager) const;

    void reset();

  private:
    Vector2 player_pos;
    float player_speed = PLAYER_STEP;
    float player_fov = PLAYER_FOV;
    Vector2 player_dir;
    Vector2 player_plane;
    map_t* map;
    std::vector<MyRay*> rays;
    std::array<float, SCREEN_WIDTH>* zBuffer;
    int life = PLAYER_LIFE;
    int damage = PLAYER_DAMAGE;
    int texture_attack = 0;
    int attack_tick = 0;
    bool attacking = false;
};
