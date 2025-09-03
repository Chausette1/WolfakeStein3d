#include "player.hpp"

#include "map_reader.hpp"

namespace {
MapTile get_cell(const map_t &map, int x, int y) {
  if (y < 0 || y >= map.height * MINI_MAP_TILE_SIZE || x < 0 ||
      x >= map.width * MINI_MAP_TILE_SIZE) {
    return MapTile::Error;
  }
  return map.data[y / MINI_MAP_TILE_SIZE][x / MINI_MAP_TILE_SIZE];
}

bool canMoveAt(const int x, const int y, const map_t &map) {
  MapTile tile = get_cell(map, x, y);
  switch (tile) {
    case MapTile::Wall:
      return false;
    case MapTile::Wall2:
      return false;
    case MapTile::Wall3:
      return false;
    case MapTile::Wall4:
      return false;
    case MapTile::Empty:
      return true;
    default:
      return false;
  }
}

}  // namespace

Player::Player(map_t &map) {
  int x, y;
  MapTile dir;

  if (!map_reader::find_player(map, x, y, dir)) {
    std::cerr << "Error: Player not found in map" << std::endl;
    throw std::runtime_error("Player not found in map");
  }

  this->map = &map;

  player_x =
      (static_cast<float>(x) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);
  player_y =
      (static_cast<float>(y) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);

  switch (dir) {
    case MapTile::Player_North:
      player_dir = Deg2Rad(90.0f);
      break;
    case MapTile::Player_South:
      player_dir = Deg2Rad(270.0f);
      break;
    case MapTile::Player_West:
      player_dir = Deg2Rad(180.0f);
      break;
    case MapTile::Player_East:
      player_dir = Deg2Rad(0.0f);
      break;
    default:
      throw std::runtime_error("Invalid player direction in map");
  }
}

Player::~Player() {
  this->map = nullptr;
  delete this;
}

void Player::move() {
  // sin are inverted due to coordinate system

  int buffer_x = static_cast<int>(cos(player_dir) * player_speed);
  int buffer_y = static_cast<int>(-sin(player_dir) * player_speed);

  if (canMoveAt(static_cast<int>(player_x + buffer_x),
                static_cast<int>(player_y + buffer_y), *map)) {
    player_x += buffer_x;
    player_y += buffer_y;
  }
}

void Player::rotate(bool right) {
  if (right) {
    player_dir -= PLAYER_ROT_STEP;
  } else {
    player_dir += PLAYER_ROT_STEP;
  }
  player_dir = fmod((player_dir + (2 * PI)), (2 * PI));
}

void Player::draw() const {
  DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_SIZE_ON_MINI_MAP,
             WHITE);
  DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
           SCREEN_WIDTH / 2 + cos(player_dir) * 30,
           SCREEN_HEIGHT / 2 - sin(player_dir) * 30, WHITE);
}
