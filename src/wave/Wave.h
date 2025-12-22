#pragma once
struct EnemySpawn {
	float delay;
	std::function<Object* ()> create;
};

class Wave {
public:
	void AddSpawn(float delay, std::function<Object* ()> factory) {
		spawns.push_back({ delay, factory });
	}

	void Start() {
		timer = 0.f;
		index = 0;
		active = true;
	}

	void Update() {
		if(!active || index >= spawns.size()) return;

		timer += timeManager->GetDeltaTime();

		if(timer >= spawns[index].delay) {
			//spawnerManager.SpawnObject(spawns[index].create());

			timer = 0.f;
			index++;
		}
	}

	bool IsFinishedSpawning() const {
		return index >= spawns.size();
	}

	void Stop() { active = false; }

private:
	std::vector<EnemySpawn> spawns;
	size_t index = 0;
	float timer = 0.f;
	bool active = false;
};
