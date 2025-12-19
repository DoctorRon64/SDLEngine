#include "pch.h"
#include "ImageRenderer.h"

void ImageRenderer::Update(float _deltaTime) {
	destinationRect.x = transform->position.x;
	destinationRect.y = transform->position.y;
	destinationRect.w = sourceSize.x * transform->scale.x;
	destinationRect.h = sourceSize.y * transform->scale.y;
}

void ImageRenderer::Render() {
	sourceRect = { sourceOffset.x, sourceOffset.y, sourceSize.x, sourceSize.y };

	SDL_RenderTextureRotated(
		renderManager->GetRenderer(),
		renderManager->GetTexture(resourcePath),
		&sourceRect,
		&destinationRect,
		transform->rotation,
		nullptr,
		SDL_FLIP_NONE
	);
}