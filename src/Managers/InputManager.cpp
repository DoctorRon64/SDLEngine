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
			if(event.button.button == SDL_BUTTON_LEFT) leftClick = true;
		}
		else if(event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
			if(event.button.button == SDL_BUTTON_LEFT) leftClick = false;
		}
		else if(event.type == SDL_EVENT_KEY_DOWN) {
			if(keyReference[event.key.key] != HOLD) 
				keyReference[event.key.key] = DOWN;
		}
		else if(event.type == SDL_EVENT_KEY_UP) {
			keyReference[event.key.key] = UP;
		}
	}

	return false;
}

bool InputManager::GetArrowInput(Sint32 arrowKey) {
	return GetEvent(arrowKey, HOLD) || GetEvent(arrowKey, DOWN);
}

bool InputManager::GetGamepadButton(int buttonID) {
	if(SDL_IsGamepad(0)) {
		SDL_Gamepad* controller = SDL_OpenGamepad(0);
		if(controller) {
			return SDL_GetGamepadButton(controller, static_cast<SDL_GamepadButton>(buttonID)) != 0;
		}
	}
	return false;
}

float InputManager::GetGamepadAxisX() {
	if(SDL_IsGamepad(0)) {
		SDL_Gamepad* controller = SDL_OpenGamepad(0);
		if(controller) {
			Sint16 val = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_LEFTX);
			return val / 32767.0f;
		}
	}
	return 0.f;
}

float InputManager::GetGamepadAxisY() {
	if(SDL_IsGamepad(0)) {
		SDL_Gamepad* controller = SDL_OpenGamepad(0);
		if(controller) {
			Sint16 val = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_LEFTY);
			return val / 32767.0f;
		}
	}
	return 0.f;
}

bool InputManager::GetEvent(Sint32 _input, KeyState _inputValue) {
	return keyReference[_input] == _inputValue;
}