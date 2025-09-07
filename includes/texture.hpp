#pragma once

#include "include.hpp"

class TextureManager
{
  public:
    TextureManager();
    ~TextureManager();

    Color* get_texture(int index) { return texture[index]; }
    int get_texture_width(int index) { return texture_width[index]; }
    int get_texture_height(int index) { return texture_height[index]; }

    void load_textures();
    void unload_textures();

  private:
    std::array<Color*, TEXTURE_NUM> texture;

    std::array<int, TEXTURE_NUM> texture_width;
    std::array<int, TEXTURE_NUM> texture_height;
};