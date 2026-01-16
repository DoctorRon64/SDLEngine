#pragma once
#include "../audio/AtomicWrapper.h"
#include "../audio/AudioStream.h"

class AudioManager {
public:
	static AudioManager* GetInstance() {
		static AudioManager instance;
		return &instance;
	}

	bool Init() {
		try {
			if(!SDL_Init(SDL_INIT_AUDIO)) {
				throw SDL_GetError();
			}
			audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
			if(audioDevice == 0) {
				throw SDL_GetError();
			}
			return true;
		}
		catch(const std::exception& e) {
			std::cerr << "AudioManager Init Error: " << e.what() << std::endl;
			return false;
		}
	};

	//void HaltAudio() {
	//	shouldHaltAudio = true;

	//	int size = threadsDone.size();
	//	for(int i = 0; i < size; ) {
	//		if(threadsDone.at(i).value) {
	//			i++;
	//		}
	//	}

	//	// FOR EACH SCENE CHANGE
	//	// BUT WE DONT WANT THAT BECAUSE WE CAN JUST SAY
	//	// FOR WHICH SCENE WE WNAT
	//	//shouldHaltAudio = false;
	//	//threadsDone.clear();
	//}

	void StopAllAudio() {
		StopAllSoundEffects();
		StopMusic();
	}

	bool LoadSoundData(const std::string& filePath) {
		if(soundsData.find(filePath) != soundsData.end()) {
			return false;
		}

		SoundData* soundData = new SoundData();

		try {
			if(!SDL_LoadWAV(filePath.c_str(), &soundData->spec, &soundData->wavData, &soundData->wavDataLength)) {
				throw SDL_GetError();
			}

			soundsData[filePath] = soundData;
			return true;
		}
		catch(const std::exception& e) {
			delete soundData;
			soundData = nullptr;

			std::cerr << "LoadSoundData Error: " << e.what() << std::endl;
			return false;
		}
	};

	void PlaySound(const std::string& filePath) {
		if(soundsData.find(filePath) == soundsData.end()) return;

		auto soundThread = std::make_unique<SoundThread>();

		soundThread->thread = std::thread([this, filePath, st = soundThread.get()]() {
			AudioStream stream(soundsData[filePath]->spec, audioDevice);
			stream.CheckPlayBack(soundsData[filePath], st->done);
			st->done = true;
		});

		soundThreads.push_back(std::move(soundThread));
	}

	void PlaySoundLooping(const std::string& filePath) {
		if(soundsData.find(filePath) == soundsData.end()) return;

		// Stop previous music ONLY if changing tracks
		StopMusic();

		musicThreadDone.value = false;

		musicThread = std::thread([this, filePath]() {
			AudioStream stream(soundsData[filePath]->spec, audioDevice);
			stream.CheckPlayBackLooping(soundsData[filePath], musicThreadDone.value);
		});
	}

	void StopAllSoundEffects() {
		for(auto& st : soundThreads) {
			st->done = true;
			if(st->thread.joinable())
				st->thread.join();
		}
		soundThreads.clear();
	}

	void StopMusic() {
		if(musicThread.joinable()) {
			musicThreadDone.value = true;
			musicThread.join();
		}
	}

	void Mute() {
		if(muted) {
			return;
		}

		SDL_PauseAudioDevice(audioDevice);
		muted = true;
	};

	void Unmute() {
		if(!muted) {
			return;
		}
		SDL_ResumeAudioDevice(audioDevice);
		muted = false;
	}

	SoundData* GetSoundData(const std::string& filePath) {
		if(soundsData.find(filePath) != soundsData.end()) {
			return nullptr;
		}

		return soundsData[filePath];
	};

	struct SoundThread {
		std::thread thread;
		std::atomic<bool> done{ false };
	};

	std::vector<std::unique_ptr<SoundThread>> soundThreads;

private:
	AudioManager() = default;
	AudioManager(AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	~AudioManager() {
		// Stop all sound threads
		for(auto& st : soundThreads) {
			st->done = true;
			if(st->thread.joinable())
				st->thread.join();
		}

		// Stop music thread
		if(musicThread.joinable()) {
			musicThreadDone.value = true;
			musicThread.join();
		}

		// Free audio data
		for(auto& [_, data] : soundsData) {
			SDL_free(data->wavData);
			delete data;
		}

		soundsData.clear();

		SDL_CloseAudioDevice(audioDevice);
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}

	void PlaySoundCallback(const std::string& filePath, int threadIndex, bool looping) {
		AudioStream stream = AudioStream(soundsData[filePath]->spec, audioDevice);
		if(looping) {
			stream.CheckPlayBackLooping(soundsData[filePath], threadsDone[threadIndex].value);
		}
		else {
			stream.CheckPlayBack(soundsData[filePath], threadsDone[threadIndex].value);
		}
		threadsDone[threadIndex] = AtomicWrapper<bool>(std::atomic<bool>(true));
	}

	bool muted = false;
	SDL_AudioDeviceID audioDevice = 0;
	std::map<std::string, SoundData*> soundsData;

	std::vector<AtomicWrapper<bool>> threadsDone;
	std::thread musicThread;
	AtomicWrapper<bool> musicThreadDone;
};
