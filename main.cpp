#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"

void update(Player *player);
void draw(MiniMap *mini_map);

int main(void) {

  map_t map;
  if (!map_reader::load_map(map, DEFAULT_MAP)) {
    std::cerr << "Failed to load map: " << DEFAULT_MAP << std::endl;
    return 1;
  }

  Player *player = new Player(map);
  MiniMap *mini_map = new MiniMap(player, map);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

  SetTargetFPS(MAX_FPS);

  int frame_count = 0;
  while (!WindowShouldClose()) {
    if (frame_count % 6 == 0) {
      update(player);
    }
    draw(mini_map);

    frame_count++;
  }

  CloseWindow();

  return 0;
}

void update(Player *player) {
  if (IsKeyDown(KEY_A)) {
    player->rotate(false);
  } else if (IsKeyDown(KEY_D)) {
    player->rotate(true);
  } else if (IsKeyDown(KEY_W)) {
    player->move();
  }
}

void draw(MiniMap *mini_map) {
  BeginDrawing();

  ClearBackground(BLACK);

  mini_map->draw();

  DrawFPS(FPS_INDICATOR_X, FPS_INDICATOR_Y);
  EndDrawing();
}
