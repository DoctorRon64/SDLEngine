#pragma once
#include <objects/PowerUps/PowerUpFactory.h>
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
		bossActive = false;
		if(waves.empty()) return;

		if(OnWaveStarted) {
			OnWaveStarted(currentWaveIndex);
		}

		waves[currentWaveIndex].Start();
	}

	void StartNextWave() {
		if(currentWaveIndex + 1 >= waves.size())
			return;

		currentWaveIndex++;
		aliveEnemies = 0;

		if(OnWaveStarted)
			OnWaveStarted(currentWaveIndex);

		waves[currentWaveIndex].Start();
	}

	void RestartWave() {
		if(currentWaveIndex >= waves.size()) return;

		aliveEnemies = 0;
		bossActive = false;
		waves[currentWaveIndex].Start();
	}

	void CheckWaveCleared() {
		if(currentWaveIndex >= waves.size()) return;

		if(waves[currentWaveIndex].IsFinishedSpawning() && aliveEnemies == 0) {
			if(!bossActive) {
				SpawnPowerUp();
			}

			if(currentWaveIndex + 1 < waves.size()) {
				StartNextWave();
			}
			else {
				//if(waves[currentWaveIndex].OnWaveCleared)
				//	waves[currentWaveIndex].OnWaveCleared();

				// ALL WAVES DONE → Finish Stage
				if(OnWaveCleared)
					OnWaveCleared(currentWaveIndex);
			}
		}
	}

	bool AreAllWavesFinished() const {
		if(waves.empty()) return true;

		bool isLastWave = (currentWaveIndex == waves.size() - 1);
		bool lastWaveDoneSpawning = waves[currentWaveIndex].IsFinishedSpawning();
		bool noEnemiesAlive = (aliveEnemies == 0);

		return isLastWave && lastWaveDoneSpawning && noEnemiesAlive;
	}

	void Clear() {
		waves.clear();
		currentWaveIndex = 0;
		aliveEnemies = 0;
		bossActive = false;
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

	void SetBossActive(bool active) { bossActive = active; }
	bool IsBossActive() const { return bossActive; }

	std::function<void(int waveIndex)> OnWaveStarted;
	std::function<void(int waveIndex)> OnWaveCleared;

private:
	void SpawnPowerUp() {
		int minId = 1;
		int maxId = (int)PowerupId::TWIN_TURRETS;
		PowerupId id = (PowerupId)Randomness::Range(minId, maxId);
		PowerUp* pu = PowerUpFactory().Create(id);

		pu->GetTransform()->position = Vector2(RenderManager::GetInstance()->WINDOW_WIDTH / 2.f, RenderManager::GetInstance()->WINDOW_HEIGHT / 2.f);
		SpawnManager::Instance().SpawnObject(pu);
	}

	std::vector<Wave> waves;
	size_t currentWaveIndex = 0;
	std::vector<bool> currentWaveSpawns = std::vector<bool>();
	int aliveEnemies = 0;
	bool bossActive = false;
};
