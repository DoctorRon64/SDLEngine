#pragma once
#include "../Object.h"
#include <Objects/Decorations/Decoration1.h>
#include <Objects/Decorations/Decoration2.h>
#include <Objects/Decorations/Decoration3.h>

#define DECORATION_COUNT 3

class BackgroundDecorator :
	public Object {
	enum class DecorationPlace {
		TOP,
		BOTTOM
	};

	using DecorationFunction = std::function<void(DecorationPlace)>;

private:
	const DecorationFunction spawnFunctions[DECORATION_COUNT] = {
		[this](DecorationPlace place) { this->SpawnDecoration<Decoration1>(place); },
		[this](DecorationPlace place) { this->SpawnDecoration<Decoration2>(place); },
		[this](DecorationPlace place) { this->SpawnDecoration<Decoration3>(place); }
	};

public:
	BackgroundDecorator() {
		transform = new Transform();
		rbComp = new RigidBody(transform);
		TimeManager::GetInstance()->SubscribeEvent(1.0f, [this]() { TopSpawnEvent(); });
		TimeManager::GetInstance()->SubscribeEvent(1.0f, [this]() { BottomSpawnEvent(); });
	}
	~BackgroundDecorator() {
		delete transform;
		transform = nullptr;
		delete renderer;
		renderer = nullptr;
		delete rbComp;
		rbComp = nullptr;
	}
	virtual void Update() {}
	//virtual void Render() { renderer->Render(); }

	void TopSpawnEvent() {
		int randomSpawn = std::rand() % DECORATION_COUNT;
		spawnFunctions[randomSpawn](DecorationPlace::TOP);

		float randomTime = (float)(std::rand() % (2 * (DECORATION_MAX_TIME - DECORATION_MIN_TIME)) + DECORATION_MIN_TIME) / 2.0f;
		TimeManager::GetInstance()->SubscribeEvent(randomTime, [this]() { TopSpawnEvent(); });
	}

	void BottomSpawnEvent() {
		int randomSpawn = std::rand() % DECORATION_COUNT;
		spawnFunctions[randomSpawn](DecorationPlace::BOTTOM);

		float randomTime = (float)(std::rand() % (2 * (DECORATION_MAX_TIME - DECORATION_MIN_TIME)) + DECORATION_MIN_TIME) / 2.0f;
		TimeManager::GetInstance()->SubscribeEvent(randomTime, [this]() { BottomSpawnEvent(); });
	}

	template <class T>
	void SpawnDecoration(DecorationPlace place) {
		Decoration* decoration;
		assert(decoration = dynamic_cast<Decoration*>(new T()));
		switch(place) {
			case DecorationPlace::TOP:
			decoration->GetTransform()->position = { (float)RenderManager::GetInstance()->WINDOW_WIDTH, 0 };
			decoration->GetTransform()->rotation = 180.0f;
			break;
			case DecorationPlace::BOTTOM:
			decoration->GetTransform()->position = { (float)RenderManager::GetInstance()->WINDOW_WIDTH,
				(float)RenderManager::GetInstance()->WINDOW_HEIGHT - decoration->GetTransform()->GetSize().y };
			break;
		}
		decoration->GetRigidBody()->SetVelocity({ -BACKGROUND_SPEED, 0 });
		SpawnManager::Instance().SpawnObject(decoration);
	}
};
