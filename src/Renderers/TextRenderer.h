#pragma once

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
		destinationRect.x = transform->position.x;
		destinationRect.y = transform->position.y;

		if(autoSize) {
			destinationRect.w = sourceRect.w * transform->scale.x;
			destinationRect.h = sourceRect.h * transform->scale.y;
		}
		else {
			destinationRect.w = transform->GetSize().x;
			destinationRect.h = transform->GetSize().y;
		}
	}
	virtual void Render() override {
		SDL_RenderTextureRotated(RenderManager::GetInstance()->GetRenderer(), textTexture, &sourceRect, &destinationRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}

	void SetText(std::string _text) {
		if(textTexture != nullptr) {
			SDL_DestroyTexture(textTexture);
		}

		SDL_Surface* surf = TTF_RenderText_Solid(
			RenderManager::GetInstance()->GetFont(resourcePath), _text.c_str(), _text.length(), color
		);
		assert(surf);

		textTexture = SDL_CreateTextureFromSurface(RenderManager::GetInstance()->GetRenderer(), surf);
		assert(textTexture);

		sourceRect = { 0.f , 0.f , (float)surf->w , (float)surf->h };
		text = _text;
	}

	void SetColor(SDL_Color _color) override {
		Renderer::SetColor(_color);
		SetText(text);
	}

	std::string GetText() const { return text; }

protected:
	std::string text;
	SDL_Texture* textTexture;
	bool autoSize = true;
};
