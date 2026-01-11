#pragma once
#include <wave/Wave.h>

class Wave;

class WaveManager {
public:
	static WaveManager* GetInstance() {
		static WaveManager instance;
		return &instance;
	}

	void AddWave(Wave&& wave) {
		waves.push_back(std::move(wave));
	}

	void Start() {
		currentWaveIndex = 0;
		aliveEnemies = 0;

		if(OnWaveStarted) {
			OnWaveStarted(currentWaveIndex);
		}

		waves[currentWaveIndex].Start();
	}

	void StartNextWave() {
		currentWaveIndex++;
		assert(currentWaveIndex < waves.size());

		aliveEnemies = 0;

		if(OnWaveStarted)
			OnWaveStarted(currentWaveIndex);

		waves[currentWaveIndex].Start();
	}

	void RestartWave() {
		if(currentWaveIndex >= waves.size()) return;

		waves[currentWaveIndex].Start();
	}

	void CheckWaveCleared() {
		if(currentWaveIndex >= waves.size()) return;

		if(waves[currentWaveIndex].IsFinishedSpawning() && aliveEnemies == 0) {
			if(waves[currentWaveIndex].OnWaveCleared)
				waves[currentWaveIndex].OnWaveCleared();

			if(OnWaveCleared)
				OnWaveCleared(currentWaveIndex);
		}
	}

	bool IsCurrentWaveFinishedSpawning() { return waves[currentWaveIndex].IsFinishedSpawning(); }
	bool AreAllWavesFinishedSpawning() { return currentWaveIndex >= waves.size() - 1 && IsCurrentWaveFinishedSpawning(); }

	void RegisterEnemy() {
		aliveEnemies++;
	}

	void UnregisterEnemy() {
		aliveEnemies--;
		CheckWaveCleared();
	}

	std::function<void(int waveIndex)> OnWaveStarted;
	std::function<void(int waveIndex)> OnWaveCleared;

private:
	std::vector<Wave> waves;
	size_t currentWaveIndex = 0;
	std::vector<bool> currentWaveSpawns = std::vector<bool>();
	int aliveEnemies = 0;
};
