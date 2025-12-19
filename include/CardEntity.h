#pragma once
#include "Sprite.h"

class CardEntity : public Sprite<CardEntity::CardState> {
 private:
 public:
  enum class CardState { IDLE, SELECT };
  // CardEntity(std::vector<SDL_FRect> idleAnimations,
  //            std::vector<SDL_FRect> selectAnimations)
  //     : Sprite<CardEntity::CardState>({{CardState::IDLE, idleAnimations},
  //                                      {CardState::SELECT,
  //                                      selectAnimations}},
  //                                     100) {};
};