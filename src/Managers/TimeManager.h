#pragma once
#define timeManager TimeManager::GetInstance()

class TimeManager {
public:
	static TimeManager* GetInstance() {
		static TimeManager instance;
		return &instance;
	}
	float GetDeltaTime() { return deltaTime; }
	float GetElapsedTime() { return elapsedTime; }
	bool ShouldUpdateGame() { return deltaTime >= frameTime; }
	void ResetDeltaTime() {
		deltaTime -= static_cast<float>(std::floor(deltaTime / frameTime)) * frameTime;
	}
	void Update() {
		elapsedTime = static_cast<double>(SDL_GetTicks()) / 1000.0;
		deltaTime += elapsedTime - previousElapsedTime;
		previousElapsedTime = elapsedTime;
	}
private:
	TimeManager() {
		deltaTime = 0.0f;
		elapsedTime = 0.0f;
		previousElapsedTime = static_cast<double>(SDL_GetTicks()) / 1000.0;
		frameTime = 1.0f / static_cast<float>(fps);
	}
	~TimeManager() = default;
	TimeManager(TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;

	//Time Controle
	float deltaTime;
	float elapsedTime;
	float previousElapsedTime;

	//FPS Controle
	const int fps = 60;
	float frameTime;
};
