#pragma once

#include "renderers/TextRenderer.h"

class TextObject : public Object {
public:
	TextObject(std::string _text) : Object() {
		renderer = new TextRenderer(transform, _text);
		renderer->SetColor({ 0xff, 0xff, 0xff, 0xFF });
	}

	void SetText(std::string _text) {
		dynamic_cast<TextRenderer*>(renderer)->SetText(_text);
	}
};