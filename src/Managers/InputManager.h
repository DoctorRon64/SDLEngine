#pragma once
#include <SDL3/SDL_stdinc.h>
#include <unordered_map>
#define inputManager InputManager::GetInstance()

enum KeyState { EMPTY, DOWN, UP, HOLD, RELEASED };

class InputManager {
public:
	static InputManager* GetInstance() {
		static InputManager instance;
		return &instance;
	}
	bool Listen();
	float GetMouseX() const { return mouseX; }
	float GetMouseY() const { return mouseY; }
	bool GetLeftClick() const { return leftClick; }
	bool GetEvent(Sint32 _input, KeyState _inputValue);
private:
	InputManager() : mouseX(0), mouseY(0), leftClick(false) {}
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	float mouseX;
	float mouseY;
	bool leftClick;
	std::unordered_map<Sint32, KeyState> keyReference;
};