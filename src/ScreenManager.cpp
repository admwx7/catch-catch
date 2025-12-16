#include "../include/ScreenManager.h"

ScreenManager::ScreenManager(GameState* state, GameManager* gameManager)
    : state(state), gameManager(gameManager) {
  char* font_path = NULL;
  SDL_asprintf(&font_path, "%s../assets/%s", SDL_GetBasePath(), "cinzel.ttf");
  font = TTF_OpenFont(font_path, 42);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
}
ScreenManager::~ScreenManager() {
  if (font) {
    TTF_CloseFont(font);
  }
}

SDL_AppResult ScreenManager::renderFrame() {
  SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(state->renderer);

  const SceneManager::Scene scene = gameManager->getCurrentScene();
  switch (scene) {
    case SceneManager::Scene::MAIN_MENU: {
      renderMainMenuScreen();
      break;
    }
    default:
      break;
  }

  SDL_RenderPresent(state->renderer);
  return SDL_APP_CONTINUE;
}

void ScreenManager::renderMainMenuScreen() {
  if (!state->renderer || !font) {
    return;
  }
  for (auto* entity : gameManager->getEntitiesForCurrentScene()) {
    if (ButtonEntity* d_ptr = dynamic_cast<ButtonEntity*>(entity)) {
      d_ptr->render(state->renderer, font);
    } else {
      entity->render(state->renderer);
    }
  }
}

// void renderText(SDL_Renderer* renderer, TTF_Font* font,
//                 const std::string& text) {
//   SDL_Color color = {0, 0, 0};
//   SDL_Surface* surface =
//       TTF_RenderText_Blended(font, text.c_str(), text.size(), color);
//   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//   SDL_DestroySurface(surface);
//   SDL_FRect dstRect{80, 260, 480, 120};
//   SDL_RenderTexture(renderer, texture, NULL, &dstRect);
//   SDL_DestroyTexture(texture);
// }