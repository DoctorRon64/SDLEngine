#pragma once
#include <SDL3/SDL.h>
#include <string>

class Renderer {
protected:
	SDL_Texture* texture;
	SDL_FRect sourceRect;
	SDL_FRect destinationRect;

public:
	virtual void LoadTexture(const std::string texturePath, SDL_Renderer* renderer) = 0;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void SetDestinationRect(const SDL_FRect destRect) {
		destinationRect = destRect;
	}
};