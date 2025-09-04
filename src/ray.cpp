#include "ray.hpp"

#include "player.hpp"

MyRay::MyRay() {
    distance = 0.0f;
    wall_side = WallSide::none;
    wall_type = MapTile::Empty;
    is_cast = false;
}

MyRay::~MyRay() { delete this; }

void MyRay::cast(const Player &player, const map_t &map, Vector2 ray_dir) {
    is_cast = false;

    this->ray_dir = ray_dir;

    Vector2 pos = {static_cast<float>(player.get_x() / static_cast<float>(MINI_MAP_TILE_SIZE)),
                   static_cast<float>(player.get_y() / static_cast<float>(MINI_MAP_TILE_SIZE))};

    Vector2 map_coord = {static_cast<float>(static_cast<int>(player.get_x() / MINI_MAP_TILE_SIZE)),
                         static_cast<float>(static_cast<int>(player.get_y() / MINI_MAP_TILE_SIZE))};

    Vector2 sideDist;

    Vector2 deltaDist;

    deltaDist.x = (ray_dir.x == 0) ? 1e30 : std::abs(1 / ray_dir.x) * (MINI_MAP_TILE_SIZE);
    deltaDist.y = (ray_dir.y == 0) ? 1e30 : std::abs(1 / ray_dir.y) * (MINI_MAP_TILE_SIZE);

    Vector2 step;

    if (ray_dir.x < 0) {
        step.x = -1;
        sideDist.x = ((pos.x - map_coord.x) * deltaDist.x);
    } else {
        step.x = 1;
        sideDist.x = ((map_coord.x + 1) - (pos.x)) * deltaDist.x;
    }
    if (ray_dir.y < 0) {
        step.y = 1;
        sideDist.y = ((map_coord.y + 1) - (pos.y)) * deltaDist.y;
    } else {
        step.y = -1;
        sideDist.y = ((pos.y - map_coord.y) * deltaDist.y);
    }

    while (!is_cast) {
        if (sideDist.x < sideDist.y) {
            sideDist.x += deltaDist.x;
            map_coord.x += step.x;
            wall_side = WallSide::vertical;
        } else {
            sideDist.y += deltaDist.y;
            map_coord.y += step.y;
            wall_side = WallSide::horizontal;
        }

        if (map.data[map_coord.y][map_coord.x] != MapTile::Empty) {
            is_cast = true;
            wall_type = map.data[map_coord.y][map_coord.x];
        }
    }

    if (wall_side == WallSide::vertical) {
        distance = (sideDist.x - deltaDist.x);
    } else {
        distance = (sideDist.y - deltaDist.y);
    }
}

void MyRay::draw() {
    if (!is_cast) {
        return;
    }

    DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 + ray_dir.x * distance,
             SCREEN_HEIGHT / 2 - ray_dir.y * distance, MAGENTA);
}

void MyRay::draw_line(int line_x) {
    if (!is_cast) {
        return;
    }
    int line_height = static_cast<int>(SCREEN_HEIGHT / distance);
    int drawStart = -line_height * VISION_SCALE + SCREEN_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = line_height * VISION_SCALE + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT)
        drawEnd = SCREEN_HEIGHT - 1;

    Color color;

    if (wall_type == MapTile::Wall) {
        if (wall_side == WallSide::vertical) {
            color = {126, 0, 0, 255};
        } else if (wall_side == WallSide::horizontal) {
            color = {255, 0, 0, 255};
        }
    } else if (wall_type == MapTile::Wall2) {
        if (wall_side == WallSide::vertical) {
            color = {126, 126, 0, 255};
        } else if (wall_side == WallSide::horizontal) {
            color = {255, 255, 0, 255};
        }
    } else if (wall_type == MapTile::Wall3) {
        if (wall_side == WallSide::vertical) {
            color = {0, 126, 0, 255};
        } else if (wall_side == WallSide::horizontal) {
            color = {0, 255, 0, 255};
        }
    } else if (wall_type == MapTile::Wall4) {
        if (wall_side == WallSide::vertical) {
            color = {126, 0, 126, 255};
        } else if (wall_side == WallSide::horizontal) {
            color = {255, 0, 255, 255};
        }
    }

    DrawLine(line_x, drawStart, line_x, drawEnd, color);
}
