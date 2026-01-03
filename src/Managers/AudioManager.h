#pragma once
#include "../audio/AtomicWrapper.h"
#include "../audio/AudioStream.h"

//Para controlar cuando hay que terminar los threads
static std::atomic<bool> shouldHaltAudio = false;
static std::atomic<bool> soundEffectsHalt = false;
static std::vector<AtomicWrapper<bool>> threadsDone;
static std::vector<AtomicWrapper<bool>> activeLoops;

#define audioManager AudioManager::GetInstance()
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

	void HaltAudio() {
		shouldHaltAudio = true;

		int size = threadsDone.size();
		for(int i = 0; i < size; ) {
			if(threadsDone.at(i).value) {
				i++;
			}
		}

		// FOR EACH SCENE CHANGE
		// BUT WE DONT WANT THAT BECAUSE WE CAN JUST SAY
		// FOR WHICH SCENE WE WNAT
		//shouldHaltAudio = false;
		//threadsDone.clear();
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

		threadsDone.push_back(AtomicWrapper<bool>(false));
		int index = threadsDone.size() - 1;

		std::thread([this, filePath, index]() {
			AudioStream stream(soundsData[filePath]->spec, audioDevice);
			stream.CheckPlayBack(soundsData[filePath], threadsDone[index].value);
			threadsDone[index].value = true;
		}).detach();
	}

	void PlaySoundLooping(const std::string& filePath) {
		if(soundsData.find(filePath) == soundsData.end()) return;

		// Stop previous music if any
		if(musicThread.joinable()) {
			musicThreadDone.value = true;
			musicThread.join();
		}

		// Reset flag for new music
		musicThreadDone.value = false;

		// Start new music thread
		musicThread = std::thread([this, filePath]() {
			AudioStream stream(soundsData[filePath]->spec, audioDevice);
			stream.CheckPlayBackLooping(soundsData[filePath], musicThreadDone.value);
			musicThreadDone.value = true; // done
		});
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

private:
	AudioManager() = default;
	AudioManager(AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	~AudioManager() {
		for(std::map<std::string, SoundData*>::iterator it = soundsData.begin(); it != soundsData.end(); ++it) {
			SDL_free(it->second->wavData);
			delete it->second;
			it->second = nullptr;
		}

		soundsData.clear();
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
