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

		if(waves[currentWave].IsFinishedSpawning() && AreAllEnemiesDead()) {
			currentWave++;

			if(currentWave < waves.size()) {
				waves[currentWave].Start();
			}
			else {
				OnAllWavesCompleted();
			}
		}
	}

private:
	std::vector<Wave> waves;
	size_t currentWave = 0;

	bool AreAllEnemiesDead() {
		// You probably already have:
		// objectManager->Count<Enemy>() == 0
		return true;
	}

	void OnAllWavesCompleted() {
		// spawn powerup / boss
	}
};
