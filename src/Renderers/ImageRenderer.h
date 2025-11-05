#pragma once
#include "Components/Transform.h"

class ImageRenderer : public Renderer {
public:
	ImageRenderer(Transform* _transform, std::string _resourcePath, Vector2 _sourceOffset, Vector2 _sourceSize)
		: Renderer(_transform, _resourcePath),
		resourcePath(_resourcePath),
		sourceOffset(_sourceOffset),
		sourceSize(_sourceSize) {}

	virtual void LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) override {}
	virtual void Update(float dt) override;
	virtual void Render() override;

private:
	SDL_Texture* texture = nullptr;
	std::string resourcePath;
	Vector2 sourceOffset;
	Vector2 sourceSize;
};