#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"

void update(Player *player);
void draw(MiniMap *mini_map, Player *player);

static bool mini_map_enabled = false;
int frame_count = 0;
bool lock_tab = false;

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

    if (IsKeyUp(KEY_TAB) && lock_tab) {
        lock_tab = false;
    }

    if (IsKeyDown(KEY_A)) {
        player->rotate(false);
    } else if (IsKeyDown(KEY_D)) {
        player->rotate(true);
    } else if (IsKeyDown(KEY_W)) {
        player->move();
    } else if (IsKeyDown(KEY_UP)) {
        ACTION_KEY_DELAY--;
    } else if (IsKeyDown(KEY_DOWN)) {
        ACTION_KEY_DELAY++;
    }

    if (IsKeyDown(KEY_TAB) && !lock_tab) {
        mini_map_enabled = !mini_map_enabled;
        lock_tab = true;
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
