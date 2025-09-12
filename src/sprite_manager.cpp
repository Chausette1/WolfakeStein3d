#include "sprite_manager.hpp"

namespace {
void
sort_sprites(std::vector<int>& order, std::vector<float>& dist, std::size_t count)
{
    std::vector<std::pair<float, int>> sprites(count);
    for (std::size_t i = 0; i < count; i++) {
        sprites[i].first = dist[i];
        sprites[i].second = order[i];
    }

    std::sort(sprites.begin(), sprites.end());

    std::reverse(sprites.begin(), sprites.end());
    for (std::size_t i = 0; i < count; i++) {
        order[i] = sprites[i].second;
        dist[i] = sprites[i].first;
    }
}

}

SpriteManager::SpriteManager(map_t* map, std::array<float, SCREEN_WIDTH>* zBuffer)
{
    this->map = map;
    this->zBuffer = zBuffer;
}

SpriteManager::~SpriteManager()
{
    this->map = nullptr;
    this->zBuffer = nullptr;
}

void
SpriteManager::render_sprites(Player* player,
                              std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                              TextureManager* textureManager,
                              Texture2D& screenTex)
{
    Vector2 player_pos_normed = { player->get_x() / MINI_MAP_TILE_SIZE,
                                  player->get_y() / MINI_MAP_TILE_SIZE };

    std::size_t sprite_count = this->map->sprites.size();
    if (sprite_count == 0) {
        return;
    }

    std::vector<int> sprite_order(sprite_count);
    std::vector<float> sprite_distance(sprite_count);

    for (std::size_t i = 0; i < sprite_count; i++) {
        sprite_t* sprite = this->map->sprites[i];
        if (!sprite->visible) {
            continue;
        }

        sprite_order[i] = i;
        sprite_distance[i] =
          ((player_pos_normed.x - sprite->position.x) * (player_pos_normed.x - sprite->position.x) +
           (((player_pos_normed.y - sprite->position.y) *
             (player_pos_normed.y - sprite->position.y))));
    }

    sort_sprites(sprite_order, sprite_distance, sprite_count);

    for (std::size_t i = 0; i < sprite_count; i++) {
        Vector2 sprite_pos = {
            this->map->sprites[sprite_order[i]]->position.x - player_pos_normed.x,
            -(this->map->sprites[sprite_order[i]]->position.y - player_pos_normed.y)
        };

        Vector2 plane = player->get_plane();
        Vector2 dir = player->get_dir();

        float invDet = 1.0f / (plane.x * dir.y - dir.x * plane.y);

        Vector2 transform = { invDet * (dir.y * sprite_pos.x - dir.x * sprite_pos.y),
                              invDet * (-plane.y * sprite_pos.x + plane.x * sprite_pos.y) };

        int spriteScreenX = static_cast<int>((SCREEN_WIDTH / 2) * (1 + transform.x / transform.y));
        int spriteHeight = std::abs(static_cast<int>(SCREEN_HEIGHT / (transform.y)));

        int drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEndY >= SCREEN_HEIGHT)
            drawEndY = SCREEN_HEIGHT - 1;

        int spriteWidth = std::abs(static_cast<int>(SCREEN_HEIGHT / (transform.y)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= SCREEN_WIDTH)
            drawEndX = SCREEN_WIDTH - 1;

        SpriteType type = this->map->sprites[sprite_order[i]]->type;
        Color* spriteTexture;
        int tex_width;
        int tex_height;
        int textureID = this->map->sprites[sprite_order[i]]->texture_id;
        switch (type) {
            case SpriteType::Obstacle1:
                spriteTexture = textureManager->get_obstacle_textures(0);
                tex_width = textureManager->get_obstacle_texture_width(0);
                tex_height = textureManager->get_obstacle_texture_height(0);

                break;
            case SpriteType::Obstacle2:
                spriteTexture = textureManager->get_obstacle_textures(1);
                tex_width = textureManager->get_obstacle_texture_width(1);
                tex_height = textureManager->get_obstacle_texture_height(1);
                break;
            case SpriteType::Enemy:
                spriteTexture = textureManager->get_enemy_textures(textureID);
                tex_width = textureManager->get_enemy_texture_width(textureID);
                tex_height = textureManager->get_enemy_texture_height(textureID);
                break;
            default:
                throw std::runtime_error("Unknown sprite type");
        }

        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            if (!(transform.y > 0 && stripe > 0 && stripe < SCREEN_WIDTH &&
                  transform.y < (*this->zBuffer)[stripe])) {
                continue;
            }
            int texX =
              int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * tex_width / spriteWidth) /
              256;
            for (int y = drawStartY; y < drawEndY; y++) {
                int d = (y) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128;
                int texY = ((d * tex_height) / spriteHeight) / 256;

                Color x_y_color = spriteTexture[texY * tex_width + texX];
                if (x_y_color.r == 255 && x_y_color.g == 0 && x_y_color.b == 255)
                    continue;

                screenPixels[y * SCREEN_WIDTH + stripe] = x_y_color;
            }
        }
        UpdateTexture(screenTex, screenPixels.data());
    }
}
