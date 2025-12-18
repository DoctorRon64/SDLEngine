#pragma once
class AnimatedImageRenderer : public ImageRenderer {
private:
	int numberOfFrames;
	int numberOfRows;
	int currentFrame;
	float frameWidth;
	float frameHeight;

	bool looping;
	float currentFrameTime;
public:
	AnimatedImageRenderer(Transform* _transform, std::string _resourcePath, Vector2 _sourceOffset, Vector2 _sourceSize, int _numberOfFrames, int _numberOfRows, float _frameWidth, float _frameHeight, bool _looping)
		: ImageRenderer(_transform, _resourcePath, _sourceOffset, _sourceSize), numberOfFrames(_numberOfFrames), numberOfRows(_numberOfRows), currentFrame(0), frameWidth(_frameWidth), frameHeight(_frameHeight), looping(_looping), currentFrameTime(0.0f) {
		sourceRect = SDL_FRect{ _sourceOffset.x, _sourceOffset.y, _frameWidth, _frameHeight };
	}

	virtual void Update(float _deltaTime) override {
		ImageRenderer::Update(_deltaTime);

		currentFrameTime += _deltaTime;

		if(currentFrameTime >= timeManager->GetTimeFrame()) {
			currentFrame++;
			if(looping) {
				currentFrame = 0;
			}
			else {
				currentFrame = numberOfFrames - 1;
			}
		}

		int currentRow = currentFrame / numberOfRows;
		int currentColumn = currentFrame % numberOfRows;

		sourceRect.x = currentRow * frameWidth;
		sourceRect.y = currentColumn * frameHeight;
	}

	virtual void Render() override {
		ImageRenderer::Render();
	}
};
