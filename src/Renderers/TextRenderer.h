#pragma once

#define FONT_PATH "res/fonts/Fredoka.ttf"

class TextRenderer : public Renderer {
public:
	TextRenderer(Transform* _transform, std::string _text) : Renderer(_transform, FONT_PATH) {
		SetText(_text);
	}

	~TextRenderer() {
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}

	virtual void Update(float _deltaTime) override {
		Vector2 offset = (Vector2(-transform->size.x, -transform->size.y) / 2.0f) * transform->scale;

		destinationRect.x = transform->position.x + offset.x;
		destinationRect.y = transform->position.y + offset.y;

		if(autoSize) {
			destinationRect.w = sourceRect.w * transform->scale.x;
			destinationRect.h = sourceRect.h * transform->scale.y;
		}
		else {
			destinationRect.w = transform->size.x * transform->scale.x;
			destinationRect.h = transform->size.y * transform->scale.y;
		}
	}
	virtual void Render() override {
		SDL_RenderTextureRotated(renderManager->GetRenderer(), textTexture, &sourceRect, &destinationRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}
	virtual void LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) override {};

	void SetText(std::string _text) {
		if(textTexture != nullptr) {
			SDL_DestroyTexture(textTexture);
		}

		SDL_Surface* surf = TTF_RenderText_Solid(
			renderManager->GetFont(resourcePath), _text.c_str(), _text.length(), color
		);
		assert(surf);

		textTexture = SDL_CreateTextureFromSurface(renderManager->GetRenderer(), surf);
		assert(textTexture);

		sourceRect = { 0.f , 0.f , (float)surf->w , (float)surf->h };
		text = _text;
	}

	void SetColor(SDL_Color _color) override {
		Renderer::SetColor(_color);
		SetText(text);
	}

protected:
	std::string text;
	SDL_Texture* textTexture;
	bool autoSize = true;
};
