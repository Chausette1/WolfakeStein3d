
#include "texture.hpp"

TextureManager::TextureManager()
{
    load_textures();
}

TextureManager::~TextureManager()
{
    unload_textures();
}

void
TextureManager::load_textures()
{
    for (int i = 0; i < SPRITE_WALL_NUM; i++) {
        Image wall = LoadImage(WALL_TEXTURES[i]);

        if (!IsImageValid(wall)) {
            std::cerr << "Failed to load wall texture" << std::endl;
            exit(EXIT_FAILURE);
        }
        wall_texture[i] = LoadImageColors(wall);
        wall_texture_width[i] = wall.width;
        wall_texture_height[i] = wall.height;
        UnloadImage(wall);
    }

    for (int i = 0; i < SPRITE_OBSTACLES_NUM; i++) {
        Image obstacle = LoadImage(SPRITE_OBSTACLES[i]);

        if (!IsImageValid(obstacle)) {
            std::cerr << "Failed to load obstacle texture" << std::endl;
            exit(EXIT_FAILURE);
        }
        obstacle_texture[i] = LoadImageColors(obstacle);
        obstacle_texture_width[i] = obstacle.width;
        obstacle_texture_height[i] = obstacle.height;
        UnloadImage(obstacle);

        for (int i = 0; i < SPRITE_ENEMY_NUM; i++) {
            Image enemy = LoadImage(SPRITE_ENEMY[i]);

            if (!IsImageValid(enemy)) {
                std::cerr << "Failed to load enemy texture" << std::endl;
                exit(EXIT_FAILURE);
            }
            enemies_texture[i] = LoadImageColors(enemy);
            enemies_texture_width[i] = enemy.width;
            enemies_texture_height[i] = enemy.height;
            UnloadImage(enemy);
        }
    }

    Image sword_texture = LoadImage(SWORD_SPRITE);
    if (!IsImageValid(sword_texture)) {
        std::cerr << "Failed to load sword texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->sword_texture = LoadTextureFromImage(sword_texture);
    UnloadImage(sword_texture);
}

void
TextureManager::unload_textures()
{
    for (auto& tex : wall_texture) {
        UnloadImageColors(tex);
    }
    for (auto& tex : obstacle_texture) {
        UnloadImageColors(tex);
    }
    for (auto& tex : enemies_texture) {
        UnloadImageColors(tex);
    }
    UnloadTexture(sword_texture);
}