#pragma once
#include <Objects/Object.h>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Engine {
public:
	Engine() {
		isRunning = false;
		window = nullptr;
		renderer = nullptr;
	}
	void Init();
	void HandleEvents();
	void Update();
	void Render();

	bool IsRunning() const { return isRunning; }

private:
	const int windowSizeX = 800;
	const int windowSizeY = 800;
	std::string windowTitle = "SDL Engine";

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Object*> gameObjects;
};
