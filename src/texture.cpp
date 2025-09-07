
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
    // wall1_v_texture = LoadTexture("./assets/wall1_v.png");
    // wall1_h_texture = LoadTexture("./assets/wall1_h.png");
    // wall2_v_texture = LoadTexture("./assets/wall2_v.png");
    // wall2_h_texture = LoadTexture("./assets/wall2_h.png");
    // wall3_v_texture = LoadTexture("./assets/wall3_v.png");
    // wall3_h_texture = LoadTexture("./assets/wall3_h.png");
    // wall4_v_texture = LoadTexture("./assets/wall4_v.png");
    // wall4_h_texture = LoadTexture("./assets/wall4_h.png");
    for (int i = 0; i < 4; i++) {
        texture[i].resize(texWidth * texHeight);
    }

    for (int x = 0; x < texWidth; x++) {
        for (int y = 0; y < texHeight; y++) {

            int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
            int xycolor = y * 128 / texHeight + x * 128 / texWidth;

            texture[0][texWidth * y + x] = 65536 * 255 * (x != y && x != texWidth - y);

            texture[1][texWidth * y + x] =
              xycolor + 256 * xycolor + 65536 * xycolor; // sloped greyscale
            texture[2][texWidth * y + x] =
              65536 * 255 * (x % 16 && y % 16); // sloped yellow gradient
            texture[3][texWidth * y + x] =
              xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
        }
    }
}

void
TextureManager::unload_textures()
{
    // UnloadTexture(wall1_v_texture);
    // UnloadTexture(wall1_h_texture);
    // UnloadTexture(wall2_v_texture);
    // UnloadTexture(wall2_h_texture);
    // UnloadTexture(wall3_v_texture);
    // UnloadTexture(wall3_h_texture);
    // UnloadTexture(wall4_v_texture);
    // UnloadTexture(wall4_h_texture);
}