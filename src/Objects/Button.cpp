#include "pch.h"
#include "Button.h"

void Button::OnHoverEnter() {
	transform->scale = (Vector2(2.f, 1.f) *= 1.1);
	isHovered = true;
}

void Button::OnHoverExit() {
	transform->scale = Vector2(2.f, 1.f);
	isHovered = false;
}

void Button::OnClicked() {
	onClick();
}