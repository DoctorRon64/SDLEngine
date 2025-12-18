#pragma once
#include "../renderers/AnimatedImageRenderer.h"
#include "Object.h"

class AnimatedImage : public Object {
public:
	AnimatedImage(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize,
		int _numberOfFrames, int _numberOfRows, float _frameWidth, float _frameHeight, bool _looping)
		: Object() {
		//renderManager->LoadTexture(_texturePath); TODO LATER Would be nice if all Images load there textures here instead of defining it at Start

		SDL_Texture* tex = renderManager->GetTexture(_texturePath);
		float textureWidth = 0;
		float textureHeight = 0;
		SDL_GetTextureSize(tex, &textureWidth, &textureHeight);
		textureSize = _sourceSize.x > 0 ? _sourceSize : Vector2(textureWidth, textureHeight);

		renderer = new AnimatedImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize, _numberOfFrames, _numberOfRows, _frameWidth, _frameHeight, _looping);
		//transform->size = _sourceSize;
	}
};
