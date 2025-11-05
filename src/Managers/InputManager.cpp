#include "pch.h"
#include "InputManager.h"

bool InputManager::Listen() {
	for(std::unordered_map<Sint32, KeyState>::iterator it = keyReference.begin(); it != keyReference.end(); it++) {
		if(it->second == DOWN) {
			it->second = HOLD;
		}
		else if(it->second == UP) {
			it->second = RELEASED;
		}
	}

	SDL_Event event;
	SDL_GetMouseState(&mouseX, &mouseY);

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			return true;
		}
		else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				std::cout << "Left Clicked" << std::endl;
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
				SDL_Log("KeyDown: %d", event.key.key);
				keyReference[event.key.key] = DOWN;
			}
		}
		else if(event.type == SDL_EVENT_KEY_UP) {
			keyReference[event.key.key] = UP;
		}
	}

	return false;
}

bool InputManager::GetEvent(Sint32 _input, KeyState _inputValue) {
	return keyReference[_input] == _inputValue;
}