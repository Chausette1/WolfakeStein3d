#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"

void update(Player *player);
void draw(MiniMap *mini_map);

static bool mini_map_enabled = true;

int main(void) {
    map_t map;
    if (!map_reader::load_map(map, DEFAULT_MAP)) {
        std::cerr << "Failed to load map: " << DEFAULT_MAP << std::endl;
        return 1;
    }

    Player *player = new Player(map);
    MiniMap *mini_map = new MiniMap(player, map);

    SetTraceLogLevel(LOG_NONE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

    SetTargetFPS(MAX_FPS);

    int frame_count = 0;
    while (!WindowShouldClose()) {
        if (frame_count % ACTION_KEY_DELAY == 0) {
            update(player);
        }
        draw(mini_map);

        frame_count++;
    }

    CloseWindow();

    return 0;
}

void update(Player *player) {
    int queue = GetKeyPressed();

    if (queue == 0) { // nothing in queue we look if key are pressed
        if (IsKeyDown(KEY_A)) {
            player->rotate(false);
        } else if (IsKeyDown(KEY_D)) {
            player->rotate(true);
        } else if (IsKeyDown(KEY_W)) {
            player->move();
        } else if (IsKeyDown(KEY_TAB)) {
            mini_map_enabled = !mini_map_enabled;
        }
    } else {
        if (queue == KEY_A) {
            player->rotate(false);
        } else if (queue == KEY_D) {
            player->rotate(true);
        } else if (queue == KEY_W) {
            player->move();
        } else if (queue == KEY_TAB) {
            mini_map_enabled = !mini_map_enabled;
        }
    }
}

void draw(MiniMap *mini_map) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (mini_map_enabled) {
        mini_map->draw();
    }

    DrawFPS(FPS_INDICATOR_X, FPS_INDICATOR_Y);
    EndDrawing();
}
