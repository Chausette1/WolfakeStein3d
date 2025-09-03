#include "map_reader.hpp"

namespace {
u_int8_t get_tile_value(char c) {
  // get the good tile value
  switch (c) {
  case '0':
    return MAP_TILE_EMPTY;
  case '1':
    return MAP_TILE_WALL;
  case '2':
    return MAP_TILE_WALL2;
  case '3':
    return MAP_TILE_WALL3;
  case '4':
    return MAP_TILE_WALL4;
  case 'N':
    return PLAYER_ORIENTATION_NORTH;
  case 'S':
    return PLAYER_ORIENTATION_SOUTH;
  case 'W':
    return PLAYER_ORIENTATION_WEST;
  case 'E':
    return PLAYER_ORIENTATION_EAST;
  case ' ':
    return MAP_IGNOR;
  default:
    return MAP_ERROR;
  }
}
} // namespace

bool map_reader::load_map(map_t &map, const std::string filename) {

  // Load the file
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    file.close();
    return false;
  }

  // declare variables
  std::string line;
  std::vector<std::vector<u_int8_t>> map_data;
  int width = 0;
  int max_width = 0;
  int height = 0;

  while (std::getline(file, line)) { // read each line
    std::vector<u_int8_t> row;
    for (char c : line) { // get the tile value from each character
      width++;

      u_int8_t buffer = get_tile_value(c);
      if (buffer == MAP_IGNOR) {
        width--;
        continue;
      }
      if (buffer == MAP_ERROR) {
        std::cerr << "Error: Invalid character '" << c << "' in map file "
                  << filename << std::endl;
        file.close();
        return false;
      }
      row.push_back(buffer);
    }

    if (width > max_width) { // calc max width
      max_width = width;
    }

    width = 0;
    map_data.push_back(row);
  }

  // create the map
  width = max_width;
  height = map_data.size();

  map = {width, height, map_data, filename};

  file.close(); // close the file

  return true;
}

bool map_reader::find_player(map_t &map, int &x, int &y, u_int8_t &dir) {
  for (int j = 0; j < map.height; j++) {
    for (int i = 0; i < map.width; i++) {
      if (map.data[j][i] == PLAYER_ORIENTATION_NORTH ||
          map.data[j][i] == PLAYER_ORIENTATION_SOUTH ||
          map.data[j][i] == PLAYER_ORIENTATION_WEST ||
          map.data[j][i] == PLAYER_ORIENTATION_EAST) {
        x = i;
        y = j;
        dir = map.data[j][i];
        map.data[j][i] = 0;
        return true;
      }
    }
  }
  return false;
}
