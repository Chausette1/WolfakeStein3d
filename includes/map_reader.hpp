#pragma once

#include "include.hpp"

class map_reader {
  public:
    map_reader() = delete; // see on stack overflow to make my class static

    static bool load_map(map_t &map, const std::string filename);

    static bool find_player(map_t &map, int &x, int &y, MapTile &dir);
};
