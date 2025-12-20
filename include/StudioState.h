#pragma once

#include <memory>
#include <random>
#include <unordered_map>
#include <vector>

#include "CardManager.h"
#include "GameState.h"

#define STARTING_FUNDS 1000
#define WINNING_FUNDS 1000000
#define WINNING_GAMES 10
#define LOSING_DAYS 1000
#define LOSING_FUNDS 0
#define EVENT_RNG_MIN_INTERVAL 5
#define EVENT_RNG_MAX_INTERVAL 10
#define EVENT_TIMED_INTERVAL 10

class StudioState {
  int day = 0;
  int funds = STARTING_FUNDS;
  std::vector<GameState> games = {};
  std::vector<CardEntity*> studioModifiers = {};
  std::unordered_map<CardManager::DeckType, int> scheduledEvents = {
      {CardManager::DeckType::EVENTS_RNG,
       getInterval(CardManager::DeckType::EVENTS_RNG)},
      {CardManager::DeckType::EVENTS_TIMED,
       getInterval(CardManager::DeckType::EVENTS_TIMED)}};

  int getInterval(CardManager::DeckType type) {
    switch (type) {
      case CardManager::DeckType::EVENTS_RNG:
        return (rand() %
                (EVENT_RNG_MAX_INTERVAL - EVENT_RNG_MIN_INTERVAL + 1)) +
               EVENT_RNG_MIN_INTERVAL;
      case CardManager::DeckType::EVENTS_TIMED:
        return EVENT_TIMED_INTERVAL;
      default:
        return 0;
    }
  }

 public:
  enum ModifierType {
    GAME_MODIFIER,
    STUDIO_MODIFIER,
  };
  enum Outcome { ONGOING, WIN, LOSE };
  StudioState() {
    games.push_back(GameState());
    scheduleEvent(
        CardManager::DeckType::EVENTS_RNG,
        (rand() % (EVENT_RNG_MAX_INTERVAL - EVENT_RNG_MIN_INTERVAL + 1)) +
            EVENT_RNG_MIN_INTERVAL);
    scheduleEvent(CardManager::DeckType::EVENTS_TIMED, EVENT_TIMED_INTERVAL);
  }
  ~StudioState() {
    // FIXME: adding this causes malloc errors on exit for some reason...
    // for (auto modifier : studioModifiers) {
    //   delete modifier;
    // }
    studioModifiers.clear();
  }
  void addCard(CardEntity* card, ModifierType modifierType = GAME_MODIFIER) {
    switch (modifierType) {
      case GAME_MODIFIER:
        currentGame().addCard(card);
        break;
      case STUDIO_MODIFIER:
        studioModifiers.push_back(new CardEntity(*card));
        currentGame().applyModifier(card);
        break;
    }
  }
  GameState& currentGame() { return games.back(); }
  void newGame() {
    games.push_back(GameState());
    for (const auto& modifier : studioModifiers) {
      currentGame().applyModifier(modifier);
    }
  }
  void incrementDay() { day++; }
  Outcome checkOutcome() const {
    if (funds >= WINNING_FUNDS && games.size() >= WINNING_GAMES) {
      return Outcome::WIN;
    }
    if (funds <= LOSING_FUNDS || day >= LOSING_DAYS) {
      return Outcome::LOSE;
    }
    return Outcome::ONGOING;
  }
  void scheduleEvent(CardManager::DeckType type, int daysFromNow) {
    scheduledEvents[type] = day + daysFromNow;
  }
  CardManager::DeckType getNextEvent() {
    for (auto [type, scheduledDay] : scheduledEvents) {
      if (scheduledDay <= day) {
        scheduledDay = day + getInterval(type);
        return type;
      }
    }
    auto complete = currentGame().gameComplete();
    return complete ? CardManager::DeckType::RUN_UNLOCKS
                    : CardManager::DeckType::PLAYER_ACTIONS;
  }
};