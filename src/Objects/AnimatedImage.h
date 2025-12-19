#pragma once
#include "../renderers/AnimatedImageRenderer.h"
#include "Object.h"

class AnimatedImage : public Object {
public:
	AnimatedImage(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize,
		int _numberOfFrames, int _numberOfRows, float _frameWidth, float _frameHeight, bool _looping)
		: Object() {
		renderer = new AnimatedImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize, _numberOfFrames, _numberOfRows, _frameWidth, _frameHeight, _looping);
		transform->SetSize(_sourceSize);
		renderer->SetDestinationRect({
			static_cast<float>(transform->position.x),
			static_cast<float>(transform->position.y),
			static_cast<float>(_sourceSize.x * transform->scale.x),
			static_cast<float>(_sourceSize.y * transform->scale.y)
		});
	}
};
