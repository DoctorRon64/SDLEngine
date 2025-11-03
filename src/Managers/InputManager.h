#pragma once
#include <cstdint>
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
	bool GetEvent(int32_t _input, KeyState _inputValue);
private:
	InputManager() : mouseX(0), mouseY(0), leftClick(false) {}
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	float mouseX;
	float mouseY;
	bool leftClick;
	std::unordered_map<int32_t, KeyState> keyReference;
};