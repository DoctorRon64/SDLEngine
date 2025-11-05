#include "pch.h"
#include "ImageRenderer.h"

void ImageRenderer::Update(float dt) {
	Vector2 offset = transform->scales * Vector2(-transform->size.x, -transform->size.y) / 2.0f;
	destinationRect.x = transform->position.x + offset.x;
	destinationRect.y = transform->position.y + offset.y;
	destinationRect.w = transform->size.x * transform->scales.x;
	destinationRect.h = transform->size.y * transform->scales.y;
}

void ImageRenderer::Render() {
	renderManager->GetTexture(resourcePath);
	sourceRect = SDL_FRect{ sourceOffset.x, sourceOffset.y, sourceSize.x, sourceSize.y };
	destinationRect = SDL_FRect{ transform->position.x, transform->position.y, destinationRect.w, destinationRect.h };
	SDL_RenderTextureRotated(renderManager->GetRenderer(), renderManager->GetTexture(resourcePath),
		&sourceRect, &destinationRect, transform->rotation, NULL, SDL_FLIP_NONE);
}