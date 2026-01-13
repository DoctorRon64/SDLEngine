#pragma once
#include <string>
constexpr unsigned int WIDTH = 1360;
constexpr unsigned int HEIGHT = 768;
const std::string TITLE = "SDL_Engine";

constexpr unsigned int PLAYER_HEALTH = 100;
constexpr unsigned int PLAYER_LIVES = 3;
constexpr float BASE_PLAYER_SPEED = 1.0f;

constexpr unsigned int SCORE_TEXT_DIGITS = 6;
constexpr unsigned int MAX_STORED_SCORES = 10;

constexpr unsigned int SCORE_POWERUP_VALUE = 1000u;
constexpr float ENGINE_POWERUP_SCALE_VALUE = 1.3f;

constexpr unsigned int BULLETS_PER_SECOND = 5;

constexpr float BACKGROUND_SPEED = 200.0f;

constexpr unsigned int DECORATION_MIN_TIME = 1;
constexpr unsigned int DECORATION_MAX_TIME = 3;

constexpr unsigned int LEVEL_COUNT = 1;

constexpr const char* levelPaths[LEVEL_COUNT] = { "res/level_1.xml" };

constexpr unsigned int ENEMY_ID_COUNT = 6;
constexpr size_t ENEMY_COUNT = 6;
