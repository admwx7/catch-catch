#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "GameState.h"

struct Texture {
  SDL_Texture* sdlTexture = nullptr;
  std::string filePath = "";
};

class TextureManager {
 public:
  enum TextureName {
    MENU_BACKGROUND,
    MENU_BUTTON_BACKGROUND,
  };

 private:
  GameState* state = nullptr;
  // lookup map for textures
  std::unordered_map<TextureName, Texture> textureCache = {
      {MENU_BACKGROUND, Texture{nullptr, "menu-background.png"}},
      {MENU_BUTTON_BACKGROUND, Texture{nullptr, "menu-button-texture.png"}},
  };
  // std::vector<TokenRenderInfo> renderTokenCache = {};

  SDL_Texture* loadTexture(TextureName textureName);

 public:
  TextureManager(GameState* state);
  ~TextureManager();
  SDL_Texture* getTexture(TextureName name);
};