#pragma once

#include "include.hpp"

class TextureManager
{
  public:
    TextureManager();
    ~TextureManager();

    std::vector<u_int32_t> get_texture(int index) { return texture[index]; }

    void load_textures();
    void unload_textures();

    // Texture2D get_wall1_v_texture() const;
    // Texture2D get_wall1_h_texture() const;
    // Texture2D get_wall2_v_texture() const;
    // Texture2D get_wall2_h_texture() const;
    // Texture2D get_wall3_v_texture() const;
    // Texture2D get_wall3_h_texture() const;
    // Texture2D get_wall4_v_texture() const;
    // Texture2D get_wall4_h_texture() const;

  private:
    // Texture2D wall1_v_texture;
    // Texture2D wall1_h_texture;
    // Texture2D wall2_v_texture;
    // Texture2D wall2_h_texture;
    // Texture2D wall3_v_texture;
    // Texture2D wall3_h_texture;
    // Texture2D wall4_v_texture;
    // Texture2D wall4_h_texture;
    const int texWidth = TEXTURE_WIDTH;
    const int texHeight = TEXTURE_HEIGHT;

    std::array<std::vector<u_int32_t>, 4> texture;
};