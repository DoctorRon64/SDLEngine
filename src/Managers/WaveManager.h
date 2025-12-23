#pragma once
#include <wave/Wave.h>

#define waveManager WaveManager::GetInstance()

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
		currentWave = 0;
		waves[currentWave].Start();
	}

	void Update() {
		if(currentWave >= waves.size()) return;

		waves[currentWave].Update();
	}

	void StartNextWave() {
		currentWave++;
		assert(currentWave < waves.size());
		waves[currentWave].Start();
	}

	bool IsCurrentWaveFinishedSpawning() { return waves[currentWave].IsFinishedSpawning(); }
	bool AreAllWavesFinishedSpawning() { return currentWave >= waves.size() && IsCurrentWaveFinishedSpawning(); }

private:
	std::vector<Wave> waves;
	size_t currentWave = 0;
};
