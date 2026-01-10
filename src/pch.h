#pragma once

// Standard Library Includes
#include <algorithm>
#include <atomic>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

//SDL3 Includes
#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

//Rapidxml
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

//Utils
#include "Utils/assets.h"
#include "Utils/config.h"

//Math
#include "math/Random.h"
#include "math/Vector2.h"

#include "managers/RenderManager.h"

#include "managers/TimeManager.h"

#include "renderers/ImageRenderer.h"

#include "managers/AudioManager.h"
#include "managers/InputManager.h"

#include "managers/CollisionManager.h"
#include "managers/EnemyFactory.h"
#include "managers/FileManager.h"
#include "managers/SceneManager.h"
#include "managers/ScoreManager.h"
#include "managers/SpawnManager.h"
#include "managers/WaveManager.h"
