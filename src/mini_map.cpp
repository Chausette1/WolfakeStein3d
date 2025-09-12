#include "mini_map.hpp"

namespace {

void
draw_rectangle(int x, int y, Color color)
{
    DrawRectangle(x, y, MINI_MAP_TILE_SIZE, MINI_MAP_TILE_SIZE, color);
}

void
draw_enemies_on_map(map_t& map, float player_x, float player_y)
{
    for (const auto& sprite : map.sprites) {
        if (sprite->type != SpriteType::Enemy) {
            continue;
        }
        float enemy_x = sprite->position.x * MINI_MAP_TILE_SIZE;
        float enemy_y = sprite->position.y * MINI_MAP_TILE_SIZE;

        Vector2 buffer_coord = { enemy_x - player_x + (SCREEN_WIDTH / 2),
                                 enemy_y - player_y + (SCREEN_HEIGHT / 2) };
        if (buffer_coord.x >= 0 && buffer_coord.x < SCREEN_WIDTH && buffer_coord.y >= 0 &&
            buffer_coord.y < SCREEN_HEIGHT) {
            DrawRectangle(buffer_coord.x - 5, buffer_coord.y - 5, 10, 10, RED);
        }
    }
}

} // namespace

MiniMap::MiniMap(Player* player, map_t& map)
{
    if (player == nullptr) {
        throw std::runtime_error("Player is null");
    }
    this->player = player;
    this->map = &map;
}

void
MiniMap::draw()
{
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
                if (map->data[tile_y][tile_x] == MapTile::Wall ||
                    map->data[tile_y][tile_x] == MapTile::Wall2 ||
                    map->data[tile_y][tile_x] == MapTile::Wall3 ||
                    map->data[tile_y][tile_x] == MapTile::Wall4 ||
                    map->data[tile_y][tile_x] == MapTile::Wall5 ||
                    map->data[tile_y][tile_x] == MapTile::Wall6 ||
                    map->data[tile_y][tile_x] == MapTile::Wall7 ||
                    map->data[tile_y][tile_x] == MapTile::Wall8) {
                    draw_rectangle(x_win, y_win, WALL_COLOR);
                }
            }
            x += MINI_MAP_TILE_SIZE;
            x_win += MINI_MAP_TILE_SIZE;
        }
        y += MINI_MAP_TILE_SIZE;
        y_win += MINI_MAP_TILE_SIZE;
    }

    player->draw();
    draw_enemies_on_map(*map, player->get_x(), player->get_y());
}

bool
MiniMap::isInMap(int x, int y)
{
    return ((x >= 0 && x < map->width) && (y >= 0 && y < map->height));
}

void
MiniMap::change_map(map_t& map)
{
    this->map = &map;
    if (!this->player->load_map(map, this->player->get_buffer())) {
        throw std::runtime_error("Failed to load player map");
    }
}