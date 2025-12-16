#include "../include/SceneManager.h"

ButtonEntity* SceneManager::createMenuButton(
    const std::string& text, int index, int totalButtons,
    ButtonEntity::ButtonState initialState) {
  float buttonHeight = 32.0f;
  float buttonWidth = 128.0f;
  float buttonGap = 48.0f;

  float totalHeight = totalButtons * (buttonHeight + buttonGap) - buttonGap;
  float startY = (state->windowDimensions.height - totalHeight) / 2.0f;
  float buttonY = startY + index * (buttonHeight + buttonGap);

  SDL_FRect* buttonPosition =
      new SDL_FRect{state->windowDimensions.width / 2.0f - buttonWidth / 2.0f,
                    buttonY, buttonWidth, buttonHeight};

  return new ButtonEntity(
      initialState,
      {
          {ButtonEntity::ButtonState::IDLE,
           new SDL_FRect{0.0f, 0.0f, 128.0f, 32.0f}},
          {ButtonEntity::ButtonState::SELECTED,
           new SDL_FRect{0.0f, 32.0f, 128.0f, 32.0f}},
      },
      textureManager->getTexture(TextureManager::MENU_BUTTON_BACKGROUND),
      buttonPosition, text, {16.0f, 8.0f});
}

SceneManager::SceneManager(GameState* state, TextureManager* textureManager)
    : state(state), textureManager(textureManager) {
  scenes[Scene::MAIN_MENU] = {
      SceneComponent::MAIN_MENU_BACKGROUND,
      SceneComponent::MAIN_MENU_BUTTONS,
  };
  gameEntities[SceneComponent::MAIN_MENU_BACKGROUND] = {new Entity(
      textureManager->getTexture(TextureManager::MENU_BACKGROUND), NULL, NULL)};
  ;
  gameEntities[SceneComponent::MAIN_MENU_BUTTONS] = {
      createMenuButton("New Game", 0, 3, ButtonEntity::ButtonState::SELECTED),
      createMenuButton("Settings", 1, 3),
      createMenuButton("Quit", 2, 3),
  };
}
SceneManager::~SceneManager() {
  for (auto& [state, entities] : gameEntities) {
    for (Entity* entity : entities) {
      delete entity;
    }
  }
}
void SceneManager::changeScene(Scene newScene) { currentScene = newScene; }
SceneManager::Scene SceneManager::getCurrentScene() const {
  return currentScene;
}
std::vector<Entity*> SceneManager::getEntitiesForCurrentScene() const {
  std::vector<Entity*> entities = {};
  for (auto& component : scenes.at(currentScene)) {
    entities.insert(entities.end(), gameEntities.at(component).begin(),
                    gameEntities.at(component).end());
  }
  return entities;
}
std::vector<Entity*> SceneManager::getEntitiesForSceneComponent(
    SceneComponent component) {
  return gameEntities.at(component);
}