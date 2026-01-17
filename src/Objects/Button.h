#pragma once
#include "Image.h"
#include "Text.h"
#include "../Renderers/ButtonRenderer.h"

class Button : public Image {
public:
	using OnClick = std::function<void()>;

	Button(OnClick _onClick, Text* _label = new Text(" "))
		: Image(BUTTON_SPRITE_PATH, { 0, 0 }, { 3448.f, 1369.f }), onClick(_onClick), label(_label) {
		renderer = new ButtonRenderer(transform, BUTTON_SPRITE_PATH, { 0, 0 }, { 3448.f, 1369.f });

		transform->scale = Vector2(.1f, .1f);

		collider = new AABB({ 0.f, 0.f }, transform->GetSize());

		Vector2 topLeft = { transform->position.x, transform->position.y };
		collider->SetTopLeft(topLeft);
		collider->SetSize(transform->GetSize());
		GetRigidBody()->AddCollider(collider);
	}

	void Update() override {
		const SDL_FRect labelRect = label->GetRenderer()->GetSourceRect();
		const Vector2 labelSize = {
			labelRect.w * label->GetTransform()->scale.x,
			labelRect.h * label->GetTransform()->scale.y
		};
		label->GetTransform()->position = transform->position + (transform->GetSize() - labelSize) * 0.5f;

		Vector2 mousePos = {
			(float)InputManager::GetInstance()->GetMouseX(),
			(float)InputManager::GetInstance()->GetMouseY()
		};

		bool hovering = collider->CheckOverlappingPoint(mousePos);

		if(hovering && !isHovered) {
			OnHoverEnter();
		}
		else if(!hovering && isHovered) {
			OnHoverExit();
		}

		if(isHovered && InputManager::GetInstance()->GetLeftClick()) {
			OnClicked();
			InputManager::GetInstance()->LeftClickProcessed();
		}

		Object::Update();
	}

private:
	const float hoverScaleFactor = 1.1f;
	bool isHovered = false;
	AABB* collider = nullptr;
	OnClick onClick;
	Text* label;
	Vector2 labelStartScale;

	void OnHoverEnter() {
		transform->scale = transform->scale * hoverScaleFactor;
		label->GetTransform()->scale = label->GetTransform()->scale * hoverScaleFactor;
		//SetScaleCentered(transform->scale * hoverScaleFactor);
		AudioManager::GetInstance()->PlaySound(SFX_UI_HOVER_PATH);

		isHovered = true;
	}

	void OnHoverExit() {
		transform->scale = transform->scale / hoverScaleFactor;
		label->GetTransform()->scale = label->GetTransform()->scale / hoverScaleFactor;
		isHovered = false;
	}

	void OnClicked() {
		AudioManager::GetInstance()->PlaySound(SFX_UI_SELECT_PATH);
		onClick();
	}
};
