#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"

void update(Player *player);
void draw(MiniMap *mini_map, Player *player);

static bool mini_map_enabled = false;
int frame_count = 0;
int last_time = 0;

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

    while (!WindowShouldClose()) {
        if (frame_count % ACTION_KEY_DELAY == 0) {
            update(player);
        }
        draw(mini_map, player);

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
        } else if (IsKeyDown(KEY_TAB) && last_time + 4 * ACTION_KEY_DELAY < frame_count) {
            last_time = frame_count;
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

void draw(MiniMap *mini_map, Player *player) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (mini_map_enabled) {
        mini_map->draw();
    } else {
        player->draw_vision();
    }

    DrawFPS(FPS_INDICATOR_X, FPS_INDICATOR_Y);
    EndDrawing();
}
