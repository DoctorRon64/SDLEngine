#pragma once
#include "Object.h"
#include "renderers/TextRenderer.h"

class Text : public Object {
private:
	SDL_Color colour;
public:
	Text(std::string _text, SDL_Color _colour = {0xff, 0xff, 0xff, 0xff}) : Object(), colour(_colour) {
		renderer = new TextRenderer(transform, _text);
		renderer->SetColor(colour);
	}

	void SetText(std::string _text) {
		dynamic_cast<TextRenderer*>(renderer)->SetText(_text);
	}

	std::string GetText() const { return dynamic_cast<TextRenderer*>(renderer)->GetText(); }

	void SetColor(SDL_Color _colour) {
		colour = _colour;
		renderer->SetColor(colour);
	}

	SDL_Color GetColor() const { return colour; }
};