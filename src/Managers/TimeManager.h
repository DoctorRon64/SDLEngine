#pragma once

class TimeManager {
	struct TimedEvent {
		float time;
		std::function<void()> event;
		TimedEvent(float _time, std::function<void()> _event) : time(_time), event(_event) {}

		bool operator< (const TimedEvent& other) {
			return this->time < other.time;
		}

		friend bool operator> (const TimedEvent l, const TimedEvent& r) {
			return l.time > r.time;
		}
	};

	using TimedEventQueue = std::priority_queue<TimedEvent, std::vector<TimedEvent>, std::greater<TimedEvent>>;
private:
	TimedEventQueue timedEvents = TimedEventQueue();

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
		//std::cout << "Delta Time: " << deltaTime << std::endl;

		elapsedTime = SDL_GetTicks() / 1000.0;
		deltaTime = deltaTime + static_cast<float>(elapsedTime) - previousElapsedTime;
		previousElapsedTime = elapsedTime;

		while(timedEvents.size() > 0 && timedEvents.top().time <= elapsedTime) {
			TimedEvent timedEvent = timedEvents.top();
			timedEvent.event();
			timedEvents.pop();
		}
	}

	void SubscribeEvent(float timeToExecution, std::function<void()> event) {
		timedEvents.push(TimedEvent(
			timeToExecution + (float)elapsedTime, event
		));
	}
};
