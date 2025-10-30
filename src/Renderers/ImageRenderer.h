#pragma once
#include "Renderer.h"

class ImageRenderer : public Renderer {
public:
	virtual void LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) override;
	virtual void Update() override;
	virtual void Render(SDL_Renderer* _renderer) override;
};