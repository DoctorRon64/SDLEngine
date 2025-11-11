#pragma once

// Standard Library Includes
#include <cassert>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

//SDL3 Includes
#include <SDL3/SDL.h>
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

#include "Math/Vector2.h"

#include "Renderers/ImageRenderer.h"
#include "Renderers/Renderer.h"

#include "Managers/InputManager.h"
#include "Managers/RenderManager.h"
#include "Managers/TimeManager.h"