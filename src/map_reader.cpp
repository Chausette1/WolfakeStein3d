#include "map_reader.hpp"

namespace {
MapTile
get_tile_value(char c)
{
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
        case '5':
            return MapTile::Wall5;
        case '6':
            return MapTile::Wall6;
        case '7':
            return MapTile::Wall7;
        case '8':
            return MapTile::Wall8;
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
} // namespace

bool
map_reader::load_map(map_t& map, const std::string filename)
{
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
    std::vector<sprite_t*> sprites;
    bool map_loaded = false;

    while (std::getline(file, line)) { // read each line
        if (!map_loaded) {
            if (line == "END_MAP") {
                map_loaded = true;
                continue;
            }
            std::vector<MapTile> row;
            for (char c : line) { // get the tile value from each character
                width++;

                MapTile buffer = static_cast<MapTile>(get_tile_value(c));
                if (buffer == MapTile::Ignore) {
                    width--;
                    continue;
                }
                if (buffer == MapTile::Error) {
                    std::cerr << "Error: Invalid character '" << c << "' in map file " << filename
                              << std::endl;
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
            height = map_data.size();
        } else {
            std::string buffer;
            Vector2 sprite_pos;
            SpriteType type;
            for (char c : line) {
                if (c == ' ') {
                    if ((buffer[0] == 'O' && buffer.size() > 1) || buffer[0] == 'I' ||
                        buffer[0] == 'E') {
                        if (buffer[0] == 'O') {
                            if (buffer[1] == '1') {
                                type = SpriteType::Obstacle1;
                            } else if (buffer[1] == '2') {
                                type = SpriteType::Obstacle2;
                            }
                        } else if (buffer[0] == 'I') {
                            type = SpriteType::Item;
                        } else if (buffer[0] == 'E') {
                            type = SpriteType::Enemy;
                        }
                    } else {
                        if (buffer == "") {
                            continue;
                        }
                        int buffer_coord = std::stoi(buffer);
                        if (sprite_pos.x == 0) {
                            sprite_pos.x = buffer_coord;
                        } else if (sprite_pos.y == 0) {
                            sprite_pos.y = buffer_coord;
                        }
                    }
                    buffer = "";
                    continue;
                } else {
                    buffer += c;
                }
            }
            sprite_t* sprite = new sprite_t{ sprite_pos, type, true };
            sprites.push_back(sprite);
            sprite_pos.x = 0;
            sprite_pos.y = 0;
        }
    }
    map = { max_width, height, map_data, filename, sprites };

    file.close(); // close the file

    return true;
}

bool
map_reader::find_player(map_t& map, int& x, int& y, MapTile& dir)
{
    for (int j = 0; j < map.height; j++) {
        for (int i = 0; i < map.width; i++) {
            if (map.data[j][i] == MapTile::Player_North ||
                map.data[j][i] == MapTile::Player_South || map.data[j][i] == MapTile::Player_West ||
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
