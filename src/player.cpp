#include "player.hpp"
#include "map_reader.hpp"

Player::Player(map_t &map) {
  int x, y;
  u_int8_t dir;

  if (!map_reader::find_player(map, x, y, dir)) {
    std::cerr << "Error: Player not found in map" << std::endl;
    throw std::runtime_error("Player not found in map");
  }

  player_x =
      (static_cast<float>(x) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);
  player_y =
      (static_cast<float>(y) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);

  switch (dir) {
  case PLAYER_ORIENTATION_NORTH:
    player_dir = DEG2RAD(270.0f);
    break;
  case PLAYER_ORIENTATION_SOUTH:
    player_dir = DEG2RAD(90.0f);
    break;
  case PLAYER_ORIENTATION_WEST:
    player_dir = DEG2RAD(180.0f);
    break;
  case PLAYER_ORIENTATION_EAST:
    player_dir = DEG2RAD(0.0f);
    break;
  }
}

void Player::move() {
  player_x -= cos(player_dir) * player_speed; // inverse due to coordinate
                                              // system
  player_y += sin(player_dir) * player_speed;
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
           SCREEN_WIDTH / 2 - cos(player_dir) * 30,
           SCREEN_HEIGHT / 2 + sin(player_dir) * 30, WHITE);
}
