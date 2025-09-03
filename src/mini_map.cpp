#include "mini_map.hpp"

namespace {

void draw_rectangle(int x, int y, Color color) {
  DrawRectangle(x, y, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE, color);
  DrawRectangleLines(x, y, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE, WHITE);
}
} // namespace

MiniMap::MiniMap(Player *player, map_t &map) {
  if (player == nullptr) {
    throw std::runtime_error("Player is null");
  }
  this->player = player;
  this->map = &map;
}

MiniMap::~MiniMap() {
  this->player = nullptr;
  this->map = nullptr;
  delete this;
}

void MiniMap::draw() {

  int x_win = 0, y_win = 0; // cursor in windows to draw

  int x = player->get_x() - (SCREEN_WIDTH / 2); // minimap x/y
  int y = player->get_y() - (SCREEN_HEIGHT / 2);

  const int x_max = x + SCREEN_WIDTH; // max value of printing
  const int y_max = y + SCREEN_HEIGHT;

  while (y < y_max) {
    x_win = 0;
    x = player->get_x() - (SCREEN_WIDTH / 2);

    int offset_y = y % MINI_MAP_TILE_SIZE;
    while (offset_y > 0 || offset_y < 0) {
      y--;
      y_win--;
      offset_y = y % MINI_MAP_TILE_SIZE;
    }
    int tile_y = y / MINI_MAP_TILE_SIZE;

    while (x < x_max) {

      int offset_x = x % MINI_MAP_TILE_SIZE;
      while (offset_x > 0 || offset_x < 0) {
        x--;
        x_win--;
        offset_x = x % MINI_MAP_TILE_SIZE;
      }
      int tile_x = x / MINI_MAP_TILE_SIZE;

      if (isInMap(tile_x, tile_y)) {
        // print x/y
        switch (map->data[tile_y][tile_x]) {
        case MAP_TILE_EMPTY:
          draw_rectangle(x_win, y_win, BLACK);
          break;
        case MAP_TILE_WALL:
          draw_rectangle(x_win, y_win, RED);
          break;
        case MAP_TILE_WALL2:
          draw_rectangle(x_win, y_win, GREEN);
          break;
        case MAP_TILE_WALL3:
          draw_rectangle(x_win, y_win, BLUE);
          break;
        case MAP_TILE_WALL4:
          draw_rectangle(x_win, y_win, YELLOW);
          break;
        default:
          draw_rectangle(x_win, y_win, WHITE);
          break;
        }
      }
      x += MINI_MAP_TILE_SIZE;
      x_win += MINI_MAP_TILE_SIZE;
    }
    y += MINI_MAP_TILE_SIZE;
    y_win += MINI_MAP_TILE_SIZE;
  }

  player->draw();
}

bool MiniMap::isInMap(int x, int y) {
  return ((x >= 0 && x < map->width) && (y >= 0 && y < map->height));
}
