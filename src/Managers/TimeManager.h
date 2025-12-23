#pragma once
#define timeManager TimeManager::GetInstance()

class TimeManager {
	using TimedEvent = std::pair<float, std::function<void()>>;
private:
	std::vector<TimedEvent> timedEvents = std::vector<TimedEvent>(0);

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
	double elapsedTime;
	float previousElapsedTime;

	//FPS Controle
	const int fps = 60;
	float frameTime;

public:
	static TimeManager* GetInstance() {
		static TimeManager instance;
		return &instance;
	}

	float GetDeltaTime() const { return deltaTime; }
	float GetTimeFrame() const { return frameTime; }
	float GetElapsedTime() const { return static_cast<float>(elapsedTime); }
	bool ShouldUpdateGame() const { return deltaTime >= frameTime; }
	void ResetDeltaTime() {
		deltaTime -= static_cast<float>(std::floor(deltaTime / frameTime)) * frameTime;
	}
	void Update() {
		elapsedTime = SDL_GetTicks() / 1000.0;
		deltaTime = deltaTime + static_cast<float>(elapsedTime) - previousElapsedTime;
		previousElapsedTime = elapsedTime;

		for (int i = timedEvents.size() - 1; i >= 0; --i) {
			timedEvents[i].first -= deltaTime;
			if (timedEvents[i].first <= 0) {
				timedEvents[i].second();
				timedEvents.erase(timedEvents.begin() + i);
			}
		}
	}

	void SubscribeEvent(TimedEvent timedEvent) {
		timedEvents.push_back(timedEvent);
	}
};
