#include "pch.h"
#include "Wave.h"

void Wave::AddSpawn(float delay, std::function<void()> factory) {
	spawns.push_back({ delay, factory });
}

void Wave::Start() {
	spawnsSpawned = 0;

	if(OnWaveStarted) {
		OnWaveStarted();
	}

	for(const EnemySpawn& e : spawns) {
		TimeManager::GetInstance()->SubscribeEvent(
			e.delay,
			[this, e]() {
			e.create();
			spawnsSpawned++;

			if(IsFinishedSpawning() && OnWaveFinishedSpawning)
				OnWaveFinishedSpawning();
		}
		);
	}
}

bool Wave::IsFinishedSpawning() const {
	return spawnsSpawned >= spawns.size();
}