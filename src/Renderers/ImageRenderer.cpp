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

	SDL_Texture* texture = RenderManager::GetInstance()->GetTexture(resourcePath);
	if(!texture) return;

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);

	SDL_RenderTextureRotated(
		RenderManager::GetInstance()->GetRenderer(),
		texture,
		&sourceRect,
		&destinationRect,
		transform->rotation,
		nullptr,
		SDL_FLIP_NONE
	);

	SDL_SetTextureColorMod(texture, 0xff, 0xff, 0xff);
	SDL_SetTextureAlphaMod(texture, 0xff);
}
