#pragma once

struct EnemySpawn {
	float delay;
	std::function<void()> create;
};

struct SpawnInstruction {
	int enemyId;
	int amount;
	float delayBetweenSpawns;
};

class Wave {
public:
	std::function<void()> OnWaveStarted;
	std::function<void()> OnWaveFinishedSpawning;
	std::function<void()> OnWaveCleared;

	void AddSpawn(float delay, std::function<void()> factory);
	void Start();
	bool IsFinishedSpawning() const;

private:
	std::vector<EnemySpawn> spawns;
	size_t spawnsSpawned = 0;
};
