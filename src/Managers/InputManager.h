#pragma once

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

	bool GetArrowInput(Sint32 arrowKey);
	bool GetGamepadButton(int buttonID);
	float GetGamepadAxisX();
	float GetGamepadAxisY();

	void LeftClickProcessed() { leftClick = false; }
	void EventProcessed(Sint32 _input) { keyReference[_input] = EMPTY; }
private:
	InputManager() : mouseX(0), mouseY(0), leftClick(false) {}
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	float mouseX = 0;
	float mouseY = 0;
	bool leftClick;
	std::unordered_map<Sint32, KeyState> keyReference;
};