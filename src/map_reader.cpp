#include "map_reader.hpp"

namespace {
MapTile get_tile_value(char c) {
  // get the good tile value
  switch (c) {
    case '0':
      return MapTile::Empty;
    case '1':
      return MapTile::Wall;
    case '2':
      return MapTile::Wall2;
    case '3':
      return MapTile::Wall3;
    case '4':
      return MapTile::Wall4;
    case 'N':
      return MapTile::Player_North;
    case 'S':
      return MapTile::Player_South;
    case 'W':
      return MapTile::Player_West;
    case 'E':
      return MapTile::Player_East;
    case ' ':
      return MapTile::Ignore;
    default:
      return MapTile::Error;
  }
}
}  // namespace

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
  std::vector<std::vector<MapTile>> map_data;
  int width = 0;
  int max_width = 0;
  int height = 0;

  while (std::getline(file, line)) {  // read each line
    std::vector<MapTile> row;
    for (char c : line) {  // get the tile value from each character
      width++;

      MapTile buffer = static_cast<MapTile>(get_tile_value(c));
      if (buffer == MapTile::Ignore) {
        width--;
        continue;
      }
      if (buffer == MapTile::Error) {
        std::cerr << "Error: Invalid character '" << c << "' in map file "
                  << filename << std::endl;
        file.close();
        return false;
      }
      row.push_back(buffer);
    }

    if (width > max_width) {  // calc max width
      max_width = width;
    }

    width = 0;
    map_data.push_back(row);
  }

  // create the map
  width = max_width;
  height = map_data.size();

  map = {width, height, map_data, filename};

  file.close();  // close the file

  return true;
}

bool map_reader::find_player(map_t &map, int &x, int &y, MapTile &dir) {
  for (int j = 0; j < map.height; j++) {
    for (int i = 0; i < map.width; i++) {
      if (map.data[j][i] == MapTile::Player_North ||
          map.data[j][i] == MapTile::Player_South ||
          map.data[j][i] == MapTile::Player_West ||
          map.data[j][i] == MapTile::Player_East) {
        x = i;
        y = j;
        dir = map.data[j][i];
        map.data[j][i] = MapTile::Empty;
        return true;
      }
    }
  }
  return false;
}
