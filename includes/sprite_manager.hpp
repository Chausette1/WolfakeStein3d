#pragma once

#include "include.hpp"
#include "player.hpp"
#include "texture.hpp"

class SpriteManager
{
  public:
    SpriteManager(map_t* map, std::array<float, SCREEN_WIDTH>* zBuffer);
    ~SpriteManager();

    void render_sprites(Player* player,
                        std::array<Color, SCREEN_WIDTH * SCREEN_HEIGHT>& screenPixels,
                        TextureManager* textureManager,
                        Texture2D& screenTex);

  private:
    map_t* map;
    std::array<float, SCREEN_WIDTH>* zBuffer;
};