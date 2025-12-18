#include "pch.h"
#include "Button.h"

void Button::OnHoverEnter() {
	transform->scale *= 1.1;
	isHovered = true;
}

void Button::OnHoverExit() {
	transform->scale /= 1.1;
	isHovered = false;
}

void Button::OnClicked() {
	onClick();
}