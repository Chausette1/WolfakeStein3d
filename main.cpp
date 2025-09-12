#include "./includes/enemie.hpp"
#include "./includes/include.hpp"
#include "./includes/map_reader.hpp"
#include "./includes/mini_map.hpp"
#include "./includes/player.hpp"
#include "./includes/sprite_manager.hpp"
#include "./includes/texture.hpp"

void
update(Player* player, std::vector<Enemie*>& enemies, map_t& map, MiniMap* mini_map);

void
render(Player* player,
       std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
       Texture2D& screenTex,
       TextureManager* texture_manager);

void
draw(MiniMap* mini_map,
     Texture2D& screenTex,
     Player* player,
     TextureManager* texture_manager,
     std::vector<Enemie*> enemies);

int
load_map(std::string path, map_t& map);

Vector2
get_random_empty_position(map_t& map);

void
draw_health_bar(Player* player);

void
draw_sword(TextureManager* texture_manager, float rotation);

void
draw_wave();

void
reset_game(Player* player, std::vector<Enemie*>* enemies, map_t* map, MiniMap* mini_map);

static bool mini_map_enabled = false;

static bool lock_tab = false;

static int map_index = 0;

int wave_count = 0;
bool wave_in_progress = false;

int
main(void)
{
    SetTraceLogLevel(LOG_NONE);

    std::random_device rd;
    unsigned int seed = rd();

    SetRandomSeed(seed);
    SetTargetFPS(MAX_FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

    map_t map;
    load_map(MAPS[map_index], map);

    std::array<float, SCREEN_WIDTH>* zBuffer = new std::array<float, SCREEN_WIDTH>();

    Player* player = new Player(map, zBuffer);

    MiniMap* mini_map = new MiniMap(player, map);
    TextureManager* textureManager = new TextureManager();
    SpriteManager* spriteManager = new SpriteManager(&map, zBuffer);
    std::vector<Enemie*> enemies;

    auto current_time = std::chrono::high_resolution_clock::now();
    auto old_time = current_time;

    Image frameBuffer = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    Texture2D screenTex = LoadTextureFromImage(frameBuffer);
    UnloadImage(frameBuffer);
    std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT> screenPixels;

    InitAudioDevice();
    SetMasterVolume(0.65f);

    Sound sound = LoadSound(MUSIC);
    PlaySound(sound);

    while (!WindowShouldClose()) {
        if (IsSoundPlaying(sound) == false) {
            PlaySound(sound);
        }

        current_time = std::chrono::high_resolution_clock::now();

        auto elapsed =
          std::chrono::duration_cast<std::chrono::milliseconds>(current_time - old_time).count();
        if (elapsed > 66) { // ~15 actions per second
            old_time = current_time;
            if (!wave_in_progress) {
                wave_count++;
                if (wave_count % 3 == 0) {
                    map_index = (map_index + 1) % (sizeof(MAPS) / sizeof(MAPS[0]));
                    load_map(MAPS[map_index], map);
                    mini_map->change_map(map);
                }
                ENEMIE_LIFE += 5;
                ENEMIE_DAMAGE += 4;
                wave_in_progress = true;
                ENEMIE_NUMBER = 1 + wave_count * 2;
                for (int i = 0; i < ENEMIE_NUMBER; i++) {
                    Vector2 pos = get_random_empty_position(map);
                    Vector2 player_pos = { player->get_x() / MINI_MAP_TILE_SIZE,
                                           player->get_y() / MINI_MAP_TILE_SIZE };
                    enemies.push_back(new Enemie(pos, 0, map, i, player_pos));
                }
            }
            update(player, enemies, map, mini_map);
            render(player, screenPixels, screenTex, textureManager);
            spriteManager->render_sprites(player, screenPixels, textureManager, screenTex);
        }
        draw(mini_map, screenTex, player, textureManager, enemies);
    }

    StopSound(sound);

    UnloadTexture(screenTex);
    UnloadSound(sound);
    CloseWindow();

    delete mini_map;
    delete player;
    delete textureManager;
    delete spriteManager;
    delete zBuffer;
    for (auto& enemie : enemies) {
        delete enemie;
    }
    enemies.clear();

    return 0;
}

void
update(Player* player, std::vector<Enemie*>& enemies, map_t& map, MiniMap* mini_map)
{
    if (player->get_life() <= 0) {
        reset_game(player, &enemies, &map, mini_map);
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemie* enemie = *it;
        if (enemie->get_life() <= 0) {
            delete enemie;
            it = enemies.erase(it);
            continue;
        }
        if (enemie->is_attacking()) {
            enemie->update_attack_animation(player);
        }
        enemie->move_toward_player(player, map);
        if (enemie->can_attack(player)) {
            enemie->attack();
        }
        ++it;
    }
    if (enemies.empty()) {
        wave_in_progress = false;
    }

    if (IsKeyUp(KEY_TAB) && lock_tab) {
        lock_tab = false;
    }

    if (IsKeyDown(KEY_A)) {
        player->rotate(false);
    } else if (IsKeyDown(KEY_D)) {
        player->rotate(true);
    } else if (IsKeyDown(KEY_W)) {
        player->move(true);
    } else if (IsKeyDown(KEY_S)) {
        player->move(false);
    } else if (IsKeyDown(KEY_SPACE)) {
        for (auto& enemie : enemies) {
            if (player->can_attack(enemie)) {
                player->attack(enemie);
            }
        }
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
    player->render_vision(screenPixels, texture_manager);
    UpdateTexture(screenTex, screenPixels.data());
}

void
draw(MiniMap* mini_map,
     Texture2D& screenTex,
     Player* player,
     TextureManager* texture_manager,
     std::vector<Enemie*> enemies)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (mini_map_enabled) {
        mini_map->draw();
    } else {
        DrawTexture(screenTex, 0, 0, WHITE);

        float rotation = 0.0f;

        for (auto& enemie : enemies) {
            if (enemie->is_cibled()) {
                rotation = player->get_attack_animation(enemie);
                break;
            }
        }

        draw_sword(texture_manager, rotation);
    }

    draw_wave();
    draw_health_bar(player);

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

void
draw_health_bar(Player* player)
{
    int bar_height = 20;
    int x = (SCREEN_WIDTH - HEALTH_BAR_WIDTH) / 2;
    int y = 10;

    DrawRectangle(x - 2, y - 2, HEALTH_BAR_WIDTH + 4, bar_height + 4, BLACK);

    float health_percentage = static_cast<float>(player->get_life()) / PLAYER_LIFE;
    int health_bar_width = static_cast<int>(HEALTH_BAR_WIDTH * health_percentage);

    Color health_color;
    if (health_percentage > 0.5f) {
        health_color = GREEN;
    } else if (health_percentage > 0.2f) {
        health_color = YELLOW;
    } else {
        health_color = RED;
    }

    DrawRectangle(x, y, health_bar_width, bar_height, health_color);
    DrawRectangleLines(x, y, HEALTH_BAR_WIDTH, bar_height, WHITE);
}

void
draw_sword(TextureManager* texture_manager, float rotation)
{
    int x = (SCREEN_WIDTH) * (3.0f / 4.0f);
    int y = SCREEN_HEIGHT;

    Texture2D sword_texture = texture_manager->get_sword_texture();

    Rectangle source = { 0.0f,
                         0.0f,
                         -static_cast<float>(sword_texture.width),
                         static_cast<float>(sword_texture.height) };

    Rectangle dest = { static_cast<float>(x),
                       static_cast<float>(y),
                       static_cast<float>(sword_texture.width) * 4.0f,
                       static_cast<float>(sword_texture.height) * 4.0f };

    Vector2 origin = { dest.width, dest.height };

    Color tint = WHITE;
    DrawTexturePro(sword_texture, source, dest, origin, -rotation, tint);
}

void
draw_wave()
{
    std::string wave_text = "Wave " + std::to_string(wave_count);
    int font_size = 50;
    int text_width = MeasureText(wave_text.c_str(), font_size);
    // at the right up corner
    int x = (SCREEN_WIDTH - (text_width * 1.3f));
    int y = font_size / 2;

    DrawText(wave_text.c_str(), x, y, font_size, BLACK);
}

void
reset_game(Player* player, std::vector<Enemie*>* enemies, map_t* map, MiniMap* mini_map)
{
    player->reset();
    for (auto& enemie : *enemies) {
        delete enemie;
    }
    enemies->clear();
    map_index = 0;
    wave_count = 0;
    wave_in_progress = false;
    ENEMIE_LIFE = 5;
    ENEMIE_DAMAGE = 4;
    ENEMIE_NUMBER = 0;
    load_map(MAPS[map_index], *map);
    mini_map->change_map(*map);
    mini_map_enabled = false;
    lock_tab = false;
}
