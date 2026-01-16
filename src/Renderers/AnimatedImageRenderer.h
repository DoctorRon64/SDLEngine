#pragma once
class AnimatedImageRenderer : public ImageRenderer {
private:
	int numberOfFrames;
	int numberOfRows;
	int currentFrame = 0;
	float frameWidth;
	float frameHeight;
	int frameTime;

	bool looping;
public:
	AnimatedImageRenderer(Transform* _transform, std::string _resourcePath, 
		Vector2 _sourceOffset, Vector2 _sourceSize, 
		int _numberOfFrames, int _numberOfRows, 
		float _frameWidth, float _frameHeight, int _frameTime,
		bool _looping)
		: ImageRenderer(_transform, _resourcePath, _sourceOffset, _sourceSize), 
		numberOfFrames(_numberOfFrames), numberOfRows(_numberOfRows), 
		frameWidth(_frameWidth), frameHeight(_frameHeight), frameTime(_frameTime),
		looping(_looping) {
		sourceRect = SDL_FRect{ _sourceOffset.x, _sourceOffset.y, _frameWidth, _frameHeight };
	}

	virtual void Update(float _deltaTime) override {
		ImageRenderer::Update(_deltaTime);
	}

	virtual void Render() override {
		ImageRenderer::Render();
	}

public:
	void NextFrame() {
		currentFrame = (currentFrame + 1) % numberOfFrames;

		int currentRow = currentFrame % numberOfRows;
		int currentColumn = currentFrame / numberOfRows;

		sourceOffset.x = currentColumn * frameWidth;
		sourceOffset.y = currentRow * frameHeight;
	}
};
