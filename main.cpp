#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"
#include "./includes/texture.hpp"

void
update(Player* player);
void
draw(MiniMap* mini_map,
     Player* player,
     std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
     Texture2D& screenTex,
     TextureManager* texture_manager);
int
load_map(std::string path, map_t& map);

static bool mini_map_enabled = false;
static int frame_count = 0;

static bool lock_tab = false;
static bool lock_up = false;
static bool lock_down = false;

static bool load_new_map = false;
static int map_index = 0;

int
main(void)
{
    map_t map;
    load_map(MAPS[map_index], map);

    Player* player = new Player(map);
    MiniMap* mini_map = new MiniMap(player, map);
    TextureManager* textureManager = new TextureManager();

    SetTraceLogLevel(LOG_NONE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

    SetTargetFPS(MAX_FPS);

    Image frameBuffer = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    Texture2D screenTex = LoadTextureFromImage(frameBuffer);
    UnloadImage(frameBuffer);
    std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT> screenPixels;

    while (!WindowShouldClose()) {
        if (load_new_map) {
            load_map(MAPS[map_index], map);
            mini_map->change_map(map);
            load_new_map = false;
        }

        if (frame_count % ACTION_KEY_DELAY == 0) {
            update(player);
        }
        draw(mini_map, player, screenPixels, screenTex, textureManager);

        frame_count++;
    }

    CloseWindow();

    delete mini_map;
    delete player;

    return 0;
}

void
update(Player* player)
{

    if (IsKeyUp(KEY_TAB) && lock_tab) {
        lock_tab = false;
    }
    if (IsKeyUp(KEY_UP) && lock_up) {
        lock_up = false;
    }
    if (IsKeyUp(KEY_DOWN) && lock_down) {
        lock_down = false;
    }

    if (IsKeyDown(KEY_A)) {
        player->rotate(false);
    } else if (IsKeyDown(KEY_D)) {
        player->rotate(true);
    } else if (IsKeyDown(KEY_W)) {
        player->move();
    } else if (IsKeyDown(KEY_UP) && !lock_up) {
        load_new_map = true;
        map_index = (map_index + 1) % MAP_CONT;
        lock_up = true;
    } else if (IsKeyDown(KEY_DOWN) && !lock_down) {
        load_new_map = true;
        map_index = (map_index - 1 + MAP_CONT) % MAP_CONT;
        lock_down = true;
    }

    if (IsKeyDown(KEY_TAB) && !lock_tab) {
        mini_map_enabled = !mini_map_enabled;
        lock_tab = true;
    }
}

void
draw(MiniMap* mini_map,
     Player* player,
     std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
     Texture2D& screenTex,
     TextureManager* texture_manager)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (mini_map_enabled) {
        mini_map->draw();
    } else {
        player->draw_vision(screenPixels, texture_manager);
        UpdateTexture(screenTex, screenPixels.data());
        DrawTexture(screenTex, 0, 0, WHITE);
    }

    DrawRectangle(FPS_INDICATOR_X - 2, FPS_INDICATOR_Y - 2, 80, 22, BLACK);
    DrawFPS(FPS_INDICATOR_X, FPS_INDICATOR_Y);
    EndDrawing();
}

int
load_map(std::string path, map_t& map)
{
    if (!map_reader::load_map(map, path)) {
        std::cerr << "Failed to load map: " << path << std::endl;
        return 1;
    }
    return 0;
}
