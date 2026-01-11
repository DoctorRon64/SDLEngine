#pragma once
class Turret : public Actor {
public:
	Turret(Vector2 spawnPos) : Actor(TURRET_SPRITE_PATH, spawnPos, Vector2(16, 16)) {}

	void Shoot() {
		Bullet* b = new Bullet(true);
		b->SetLayer(20);
		b->GetTransform()->position = transform->position;
		SpawnManager::Instance().SpawnObject(b);
	}
};
