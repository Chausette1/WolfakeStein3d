#pragma once

#include "include.hpp"
#include "player.hpp"

class MiniMap {
public:
  MiniMap(Player *player, map_t &map);
  ~MiniMap();

  void draw();

private:
  Player *player;
  map_t *map;
  bool isInMap(int x, int y);
};
