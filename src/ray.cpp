#include "ray.hpp"

#include "player.hpp"
#include "texture.hpp"

MyRay::MyRay(std::array<float, SCREEN_WIDTH>* zBuffer)
{
    distance = 0.0f;
    wall_side = WallSide::none;
    wall_type = MapTile::Empty;
    is_cast = false;
    this->zBuffer = zBuffer;
}

void
MyRay::cast(const Player& player, const map_t& map, Vector2 ray_dir)
{
    this->zBuffer = zBuffer;
    is_cast = false;

    this->ray_dir = ray_dir;

    Vector2 pos = { (player.get_x() / static_cast<float>(MINI_MAP_TILE_SIZE)),
                    (player.get_y() / static_cast<float>(MINI_MAP_TILE_SIZE)) };

    Vector2 map_coord = { static_cast<float>(static_cast<int>(player.get_x() / MINI_MAP_TILE_SIZE)),
                          static_cast<float>(
                            static_cast<int>(player.get_y() / MINI_MAP_TILE_SIZE)) };

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
        distance = (sideDist.x - deltaDist.x) / MINI_MAP_TILE_SIZE;
        wall_x = pos.y - distance * ray_dir.y;
    } else {
        distance = (sideDist.y - deltaDist.y) / MINI_MAP_TILE_SIZE;
        wall_x = pos.x + distance * ray_dir.x;
    }

    wall_x -= floor((wall_x));

    switch (wall_type) {
        case MapTile::Wall:
            tex_num = 0;
            break;
        case MapTile::Wall2:
            tex_num = 1;
            break;
        case MapTile::Wall3:
            tex_num = 2;
            break;
        case MapTile::Wall4:
            tex_num = 3;
            break;
        case MapTile::Wall5:
            tex_num = 4;
            break;
        case MapTile::Wall6:
            tex_num = 5;
            break;
        case MapTile::Wall7:
            tex_num = 6;
            break;
        case MapTile::Wall8:
            tex_num = 7;
            break;
        default:
            throw std::runtime_error("Invalid wall type in ray casting");
    }
}

void
MyRay::draw()
{
    if (!is_cast) {
        return;
    }

    DrawLine(SCREEN_WIDTH / 2,
             SCREEN_HEIGHT / 2,
             SCREEN_WIDTH / 2 + ray_dir.x * distance * MINI_MAP_TILE_SIZE,
             SCREEN_HEIGHT / 2 - ray_dir.y * distance * MINI_MAP_TILE_SIZE,
             MAGENTA);
}

void
MyRay::draw_line(int line_x,
                 std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                 TextureManager* texture_manager)
{
    if (!is_cast) {
        throw std::runtime_error("Ray not casted before drawing");
    }

    (*zBuffer)[line_x] = distance;

    int texture_width = texture_manager->get_wall_texture_width(tex_num);

    tex_x = static_cast<int>(wall_x * texture_width);

    if ((wall_side == WallSide::vertical && ray_dir.x > 0) ||
        (wall_side == WallSide::horizontal && ray_dir.y < 0)) {
        tex_x = texture_width - tex_x - 1;
    }

    float line_height = SCREEN_HEIGHT / distance;

    int drawStart = -line_height * VISION_SCALE + SCREEN_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = line_height * VISION_SCALE + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT)
        drawEnd = SCREEN_HEIGHT - 1;

    double step = 1.0 * texture_width / line_height;

    double texPos = (drawStart - SCREEN_HEIGHT / 2 + line_height * VISION_SCALE) * step;

    Color* texture = texture_manager->get_wall_textures(tex_num);

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y < drawStart) {
            screenPixels[y * SCREEN_WIDTH + line_x] = CEILING_COLOR;
        } else if (y >= drawStart && y <= drawEnd) {

            int tex_y = static_cast<int>(texPos) & (texture_width - 1);
            texPos += step;

            Color color = texture[texture_width * tex_y + tex_x];

            if (wall_side == WallSide::horizontal) {
                color.r = (color.r >> 1) & 127;
                color.g = (color.g >> 1) & 127;
                color.b = (color.b >> 1) & 127;
            }
            screenPixels[y * SCREEN_WIDTH + line_x] = color;

        } else {
            screenPixels[y * SCREEN_WIDTH + line_x] = FLOOR_COLOR;
        }
    }
}
