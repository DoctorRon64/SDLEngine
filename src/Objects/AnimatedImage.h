#pragma once
#include "../renderers/AnimatedImageRenderer.h"
#include "Object.h"

class AnimatedImage : public Object {
private:
	int numberOfFrames;
	int currentFrame;
	bool looping;
	float frameTime;
public:
	AnimatedImage(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize,
		int _numberOfFrames, int _numberOfRows, float _frameWidth, float _frameHeight, int _frameTime, bool _looping)
		: Object(), numberOfFrames(_numberOfFrames), currentFrame(0), looping(_looping), frameTime(_frameTime) {
		renderer = new AnimatedImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize, _numberOfFrames, _numberOfRows, _frameWidth, _frameHeight, _frameTime, _looping);
		transform->SetSize(_sourceSize);
		renderer->SetDestinationRect({
			static_cast<float>(transform->position.x),
			static_cast<float>(transform->position.y),
			static_cast<float>(_sourceSize.x * transform->scale.x),
			static_cast<float>(_sourceSize.y * transform->scale.y)
		});
		TimeManager::GetInstance()->SubscribeEvent(
			TimeManager::GetInstance()->GetTimeFrame() * frameTime, [this]() { NextFrame(); }
		);
	}

	void NextFrame() {
		currentFrame++;
		if (currentFrame >= numberOfFrames && !looping) {
			Destroy();
			return;
		}
		currentFrame %= numberOfFrames;
		dynamic_cast<AnimatedImageRenderer*>(renderer)->NextFrame();
		TimeManager::GetInstance()->SubscribeEvent(
			TimeManager::GetInstance()->GetTimeFrame() * frameTime, [this]() { NextFrame(); }
		);
	}
};
