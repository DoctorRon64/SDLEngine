#pragma once
#include "Components/Transform.h"

class Renderer {
protected:
	Transform* transform = nullptr;
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_FRect sourceRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	SDL_FRect destinationRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::string texturePath = "";

public:
	Renderer() = default;
	Renderer(Transform* _transform, std::string _texturePath) : transform(_transform), texturePath(_texturePath) {}

	virtual void LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;

	virtual void SetDestinationRect(const SDL_FRect _destRect) { destinationRect = _destRect; }
	virtual void SetColor(SDL_Color _color) { color = _color; }
	SDL_Color GetColor() const { return color; }
};