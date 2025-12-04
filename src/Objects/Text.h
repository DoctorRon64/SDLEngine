#pragma once
#include "Object.h"
#include "renderers/TextRenderer.h"

class Text : public Object {
public:
	Text(std::string _text) : Object() {
		renderer = new TextRenderer(transform, _text);
		renderer->SetColor({ 0xff, 0xff, 0xff, 0xFF });
	}

	void SetText(std::string _text) {
		dynamic_cast<TextRenderer*>(renderer)->SetText(_text);
	}
};