#pragma once
struct EnemySpawn {
	float delay;
	std::function<void()> create;
};

class Wave {
public:
	void AddSpawn(float delay, std::function<void()> factory) {
		spawns.push_back({ delay, factory });
	}

	void Start() {
		timer = 0.f;
		active = true;

		spawnsSpawned = 0;

		for (EnemySpawn eSpawn : spawns) 
			timeManager->SubscribeEvent(std::make_pair(
				eSpawn.delay, 
				[this, eSpawn]() { eSpawn.create(); spawnsSpawned++; }
			));
	}

	bool IsFinishedSpawning() const {
		return spawnsSpawned >= spawns.size();
	}

	void Stop() { active = false; }

private:
	std::vector<EnemySpawn> spawns;
	size_t spawnsSpawned;
	float timer = 0.f;
	bool active = false;
};
