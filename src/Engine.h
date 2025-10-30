#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <Objects/Object.h>

class Engine {
public:
	Engine() = default;
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Terminate();

	bool IsRunning() const { return isRunning; }

private:
	void InitSDL();
	void CreateWindowAndRenderer();

	const double windowSizeX = 800;
	const double windowSizeY = 800;

	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Object*> gameObjects;
};
