#include "player.hpp"

#include "map_reader.hpp"

namespace {
MapTile
get_cell(const map_t& map, int x, int y)
{
    if (y < 0 || y >= map.height * MINI_MAP_TILE_SIZE || x < 0 ||
        x >= map.width * MINI_MAP_TILE_SIZE) {
        return MapTile::Error;
    }
    return map.data[y / MINI_MAP_TILE_SIZE][x / MINI_MAP_TILE_SIZE];
}

bool
canMoveAt(const int x, const int y, const map_t& map)
{
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

} // namespace

Player::Player(map_t& map, std::array<float, SCREEN_WIDTH>* zBuffer)
{
    load_map(map, zBuffer);
}

Player::~Player()
{
    for (auto ray : rays) {
        delete ray;
    }
    rays.clear();
}

void
Player::move()
{
    // sin are inverted due to coordinate system

    int buffer_x = static_cast<int>(player_dir.x * player_speed);
    int buffer_y = static_cast<int>(-player_dir.y * player_speed);

    for (int j = -PLAYER_HITBOX_SIZE; j <= PLAYER_HITBOX_SIZE; j++) {
        for (int i = -PLAYER_HITBOX_SIZE; i <= PLAYER_HITBOX_SIZE; i++) {
            if (!canMoveAt(static_cast<int>(player_pos.x + buffer_x) + i,
                           static_cast<int>(player_pos.y + buffer_y) + j,
                           *map)) {
                return;
            }
        }
    }
    player_pos.x += buffer_x;
    player_pos.y += buffer_y;
    this->castRays();
}

void
Player::rotate(bool right)
{
    player_dir = ROTATE_MAT_2D(right ? -PLAYER_ROT_STEP : PLAYER_ROT_STEP, player_dir);

    float tan_buff = tan(Deg2Rad(player_fov / 2));
    player_plane = { player_dir.y * tan_buff, -player_dir.x * tan_buff };
    this->castRays();
}

void
Player::draw() const
{
    DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_SIZE_ON_MINI_MAP, WHITE);

    for (auto ray : this->rays) {
        ray->draw();
    }
}

void
Player::castRays()
{
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        float camera_x = 2 * i / static_cast<float>(SCREEN_WIDTH) - 1;
        Vector2 ray_dir = { player_dir.x + player_plane.x * camera_x,
                            player_dir.y + player_plane.y * camera_x };

        this->rays[i]->cast(*this, *map, ray_dir);
    }
}

void
Player::draw_vision(std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                    TextureManager* texture_manager) const
{
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        this->rays[i]->draw_line(i, screenPixels, texture_manager);
    }
}

bool
Player::load_map(map_t& map, std::array<float, SCREEN_WIDTH>* zBuffer)
{
    int x, y;
    MapTile dir;
    if (!map_reader::find_player(map, x, y, dir)) {
        return false;
    }

    this->map = &map;

    player_pos.x = (static_cast<float>(x) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);
    player_pos.y = (static_cast<float>(y) * MINI_MAP_TILE_SIZE) + (MINI_MAP_TILE_SIZE / 2);

    switch (dir) {
        case MapTile::Player_North:
            player_dir = { 0, 1 };
            break;
        case MapTile::Player_South:
            player_dir = { 0, -1 };
            break;
        case MapTile::Player_West:
            player_dir = { -1, 0 };
            break;
        case MapTile::Player_East:
            player_dir = { 1, 0 };
            break;
        default:
            throw std::runtime_error("Invalid player direction in map");
    }
    float tan_buff = tan(Deg2Rad(player_fov / 2));
    player_plane = { player_dir.y * tan_buff, player_dir.x * tan_buff };

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        rays.push_back(new MyRay(zBuffer));
    }
    this->castRays();
    return true;
}