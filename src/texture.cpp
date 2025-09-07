
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
    Image wall[] = { LoadImage("./assets/textures/wall1.png"),
                     LoadImage("./assets/textures/wall2.png"),
                     LoadImage("./assets/textures/wall3.png"),
                     LoadImage("./assets/textures/wall4.png") };

    for (int i = 0; i < TEXTURE_NUM; i++) {
        if (wall[i].data == nullptr) {
            std::cerr << "Failed to load texture colors" << std::endl;
            exit(EXIT_FAILURE);
        }
        texture[i] = LoadImageColors(wall[i]);
        texture_width[i] = wall[i].width;
        texture_height[i] = wall[i].height;
        UnloadImage(wall[i]);
    }
}

void
TextureManager::unload_textures()
{
    for (auto& tex : texture) {
        UnloadImageColors(tex);
    }
}