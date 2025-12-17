#include "pch.h"
#include "ImageRenderer.h"

void ImageRenderer::Update(float _deltaTime) {
	destinationRect.w = transform->size.x * transform->scale.x;
	destinationRect.h = transform->size.y * transform->scale.y;
	destinationRect.x = transform->position.x;
	destinationRect.y = transform->position.y;
	//Vector2 offset = transform->scale * Vector2(-transform->size.x, -transform->size.y) / 2.0f;
	//destinationRect.x = transform->position.x + offset.x;
	//destinationRect.y = transform->position.y + offset.y;
}

void ImageRenderer::Render() {
	renderManager->GetTexture(resourcePath);

	sourceRect = { sourceOffset.x, sourceOffset.y, sourceSize.x, sourceSize.y };
	destinationRect = { transform->position.x, transform->position.y, destinationRect.w, destinationRect.h };

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