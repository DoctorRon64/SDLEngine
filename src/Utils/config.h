#pragma once
#include <string>
constexpr unsigned int WIDTH = 1360;
constexpr unsigned int HEIGHT = 768;
const std::string TITLE = "SDL_Engine";

constexpr unsigned int PLAYER_HEALTH = 100;
constexpr unsigned int PLAYER_LIVES = 3;
constexpr float BASE_PLAYER_SPEED = 1.0f;

constexpr unsigned int SCORE_TEXT_DIGITS = 6;

constexpr unsigned int SCORE_POWERUP_VALUE = 1000u;
constexpr float ENGINE_POWERUP_SCALE_VALUE = 1.3f;