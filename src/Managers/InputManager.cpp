#include "InputManager.h"
#include <cstdint>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>
#include <unordered_map>

bool InputManager::Listen() {
	for(std::unordered_map<int32_t, KeyState>::iterator it = keyReference.begin(); it != keyReference.end(); it++) {
		if(it->second == DOWN) {
			it->second = HOLD;
		}
		else if(it->second == UP) {
			it->second = RELEASED;
		}
	}

	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			return true;
		}
		else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				leftClick = true;
			}
		}
		else if(event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				leftClick = false;
			}
		}
		else if(event.type == SDL_EVENT_KEY_DOWN) {
			if(keyReference[event.key.key] != HOLD) {
				keyReference[event.key.key] = DOWN;
			}
		}
		else if(event.type == SDL_EVENT_KEY_UP) {
			keyReference[event.key.key] = UP;
		}
	}
	return false;
}

bool InputManager::GetEvent(int32_t _input, KeyState _inputValue) {
	if(keyReference.find(_input) != keyReference.end()) {
		return keyReference[_input] == _inputValue;
	}
	return false;
}