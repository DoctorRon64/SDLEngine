#pragma once
#include "../audio/AtomicWrapper.h"
#include "../audio/AudioStream.h"

//Para controlar cuando hay que terminar los threads
static std::atomic<bool> shouldHaltAudio = false;
static std::vector<AtomicWrapper<bool>> threadsDone;

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
		if(soundsData.find(filePath) == soundsData.end()) {
			return;
		}

		threadsDone.push_back(std::atomic<bool>(false));
		std::thread thread(&AudioManager::PlaySoundCallback, this, filePath, (threadsDone.size() - 1), false);
		thread.detach();
	};

	void PlaySoundLooping(const std::string& filePath) {
		if(soundsData.find(filePath) == soundsData.end()) {
			return;
		}

		threadsDone.push_back(std::atomic<bool>(false));
		std::thread thread(&AudioManager::PlaySoundCallback, this, filePath, (threadsDone.size() - 1), true);
		thread.detach();
	};

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
			stream.CheckPlayBackLooping(soundsData[filePath], shouldHaltAudio);
		}
		else {
			stream.CheckPlayBack(soundsData[filePath], shouldHaltAudio);
		}
		threadsDone[threadIndex] = AtomicWrapper<bool>(std::atomic<bool>(true));
	}

	bool muted = false;
	SDL_AudioDeviceID audioDevice = 0;
	std::map<std::string, SoundData*> soundsData;
};
