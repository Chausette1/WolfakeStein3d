#include "./includes/enemie.hpp"
#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"
#include "./includes/sprite_manager.hpp"
#include "./includes/texture.hpp"

void
update(Player* player);

void
render(Player* player,
       std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
       Texture2D& screenTex,
       TextureManager* texture_manager);

void
draw(MiniMap* mini_map, Texture2D& screenTex);

int
load_map(std::string path, map_t& map);

Vector2
get_random_empty_position(map_t& map);

static bool mini_map_enabled = false;
static int frame_count = 0;

static bool lock_tab = false;
static bool lock_up = false;
static bool lock_down = false;

static bool load_new_map = false;
static int map_index = 0;

int wave_count = 0;
bool wave_in_progress = false;

int
main(void)
{
    map_t map;
    load_map(MAPS[map_index], map);

    std::array<float, SCREEN_WIDTH>* zBuffer = new std::array<float, SCREEN_WIDTH>();

    Player* player = new Player(map, zBuffer);

    MiniMap* mini_map = new MiniMap(player, map);
    TextureManager* textureManager = new TextureManager();
    SpriteManager* spriteManager = new SpriteManager(&map, zBuffer);
    std::vector<Enemie*> enemies;

    SetTraceLogLevel(LOG_NONE);

    std::random_device rd;
    unsigned int seed = rd();

    SetRandomSeed(seed);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

    SetTargetFPS(MAX_FPS);

    Image frameBuffer = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    Texture2D screenTex = LoadTextureFromImage(frameBuffer);
    UnloadImage(frameBuffer);
    std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT> screenPixels;

    InitAudioDevice();
    SetMasterVolume(65.0f / 100.0f);

    Sound sound = LoadSound(MUSIC);
    PlaySound(sound);

    while (!WindowShouldClose()) {
        if (IsSoundPlaying(sound) == false) {
            PlaySound(sound);
        }
        // if (load_new_map) {
        //     load_map(MAPS[map_index], map);
        //     mini_map->change_map(map);
        //     load_new_map = false;
        // }

        if (frame_count % ACTION_KEY_DELAY == 0) {
            if (!wave_in_progress) {
                ENEMIE_LIFE += 5;
                ENEMIE_DAMAGE += 2;
                wave_in_progress = true;
                wave_count++;
                ENEMIE_NUMBER = 5 + wave_count * 2;
                for (int i = 0; i < ENEMIE_NUMBER; i++) {
                    Vector2 pos = get_random_empty_position(map);
                    Vector2 player_pos = { player->get_x() / MINI_MAP_TILE_SIZE,
                                           player->get_y() / MINI_MAP_TILE_SIZE };
                    enemies.push_back(new Enemie(pos, 0, map, i, player_pos));
                }
            } else {
                for (auto& enemie : enemies) {
                    enemie->move_toward_player(player, map);
                }
            }
            update(player);
            render(player, screenPixels, screenTex, textureManager);
            spriteManager->render_sprites(player, screenPixels, textureManager, screenTex);
        }
        draw(mini_map, screenTex);

        frame_count++;
    }

    StopSound(sound);

    UnloadTexture(screenTex);
    UnloadSound(sound);
    CloseWindow();

    delete mini_map;
    delete player;
    delete textureManager;

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
        player->move(true);
    } else if (IsKeyDown(KEY_S)) {
        player->move(false);
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
render(Player* player,
       std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
       Texture2D& screenTex,
       TextureManager* texture_manager)
{
    player->draw_vision(screenPixels, texture_manager);
    UpdateTexture(screenTex, screenPixels.data());
}

void
draw(MiniMap* mini_map, Texture2D& screenTex)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (mini_map_enabled) {
        mini_map->draw();
    } else {
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

Vector2
get_random_empty_position(map_t& map)
{
    Vector2 pos;
    do {
        pos.x = GetRandomValue(0, map.width - 1);
        pos.y = GetRandomValue(0, map.height - 1);
    } while (map.data[pos.y][pos.x] != MapTile::Empty);
    return pos;
}