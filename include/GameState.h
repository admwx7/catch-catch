#pragma once
#include <SDL3/SDL.h>

struct WindowDimensions {
  int width = 640;
  int height = 360;
};

class GameState {
 public:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  WindowDimensions windowDimensions;

  ~GameState() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }
};