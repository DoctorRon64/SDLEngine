#pragma once
#include "Objects/Object.h"

class Engine {
public:
	Engine();
	~Engine();
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	bool IsRunning() const { return isRunning; }
private:
	const int windowSizeX = 1200;
	const int windowSizeY = 1200;
	const std::string windowTitle = "SDL_Engine";

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Object*> gameObjects;
};
