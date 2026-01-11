#pragma once
#include "../components/Collidable.h"
#include "Objects/Image.h"

class Actor : public Image, public Collidable {
protected:
	int maxHealth;
	int health;

	virtual	void MoveTowards(Transform* t, Vector2 target, float speed, float dt) {
		Vector2 dir = target - t->position;
		dir.Normalize();
		t->position += dir * speed * dt;
	}

	virtual void Orbit(Transform* t, Vector2 center, float radius, float& angle, float angularSpeed, float dt) {
		angle += angularSpeed * dt;
		t->position = {
			center.x + cos(angle) * radius,
			center.y + sin(angle) * radius
		};
	}

	void InitHp(int _hp) {
		health = _hp;
		maxHealth = _hp;
	}

	virtual void OnDeath() {
		if(OnDeathEvent) {
			OnDeathEvent();
		}

		Destroy();
	}
public:
	Actor(
		std::string _texturePath,
		Vector2 _sourceOffset = Vector2(0, 0),
		Vector2 _sourceSize = Vector2(400.f, 400.f),
		int _maxHealth = 100,
		int _health = 0
	)
		: Image(_texturePath, _sourceOffset, _sourceSize),
		maxHealth(_maxHealth),
		health(_health), Collidable(rbComp) {}

	virtual ~Actor() = default;

	std::function<void(int current, int max)> OnHealthChanged;
	std::function<void()> OnDeathEvent;
	virtual void TakeDamage(int amount) {
		if(health <= 0) return; // already dead

		health -= amount;
		OnHealthChangedEvent();

		if(health <= 0) {
			OnDeath();
		}
	}

	void Heal(int amount) {
		health += amount;
		OnHealthChangedEvent();
	}
	void HealToMax() {
		health = maxHealth;
		OnHealthChangedEvent();
	}

	void OnHealthChangedEvent() {
		if(OnHealthChanged) OnHealthChanged(health, maxHealth);
	}
};