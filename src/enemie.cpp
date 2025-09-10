#include "enemie.hpp"

Enemie::Enemie(Vector2 pos, int texture_id, map_t& map)
  : map(&map)
  , speed(ENEMIE_STEP)
  , position(pos)
  , textureID(texture_id) {};

Enemie::~Enemie()
{
    this->map = nullptr;
}

void
Enemie::update_texture_in_map()
{
    int map_x = static_cast<int>(this->position.x);
    int map_y = static_cast<int>(this->position.y);

    if (map_x >= 0 && map_x < this->map->width && map_y >= 0
        && map_y < this->map->height) {
        
    }
}