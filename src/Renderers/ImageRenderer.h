#pragma once
#include "Components/Transform.h"
#include "Managers/RenderManager.h"
#include "Math/Vector2.h"
#include "Renderer.h"
#include <cassert>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <string>

class ImageRenderer : public Renderer {
public:
	ImageRenderer(Transform* _transform, std::string _resourcePath, Vector2 _sourceOffset, Vector2 _sourceSize)
		: Renderer(_transform, _resourcePath),
		resourcePath(_resourcePath),
		sourceOffset(_sourceOffset),
		sourceSize(_sourceSize) {}

	virtual void LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) override {}

	virtual void Update(float dt) override {
		Vector2 offset = transform->scales * Vector2(-transform->size.x, -transform->size.y) / 2.0f;
		destinationRect.x = transform->position.x + offset.x;
		destinationRect.y = transform->position.y + offset.y;
		destinationRect.w = transform->size.x * transform->scales.x;
		destinationRect.h = transform->size.y * transform->scales.y;
	}

	virtual void Render() override {
		renderManager->GetTexture(resourcePath);
		sourceRect = SDL_FRect{ sourceOffset.x, sourceOffset.y, sourceSize.x, sourceSize.y };
		destinationRect = SDL_FRect{ transform->position.x, transform->position.y, destinationRect.w, destinationRect.h };
		SDL_RenderTextureRotated(renderManager->GetRenderer(), renderManager->GetTexture(resourcePath),
			&sourceRect, &destinationRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}

private:
	SDL_Texture* texture = nullptr;
	std::string resourcePath;
	Vector2 sourceOffset;
	Vector2 sourceSize;
};