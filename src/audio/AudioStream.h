#pragma once

struct SoundData {
	SDL_AudioSpec spec;
	Uint8* wavData;
	Uint32 wavDataLength;
};

enum StreamState {
	READY,
	PLAYING,
	STOPPED,
};

class AudioStream {
private:
	SDL_AudioStream* stream;
	StreamState state;

	void StopStream() {
		SDL_ClearAudioStream(stream);
		SDL_UnbindAudioStream(stream);
		SDL_DestroyAudioStream(stream);

		state = STOPPED;
	}
public:
	AudioStream(SDL_AudioSpec _spec, SDL_AudioDeviceID _deviceId) {
		stream = SDL_CreateAudioStream(&_spec, NULL);
		SDL_BindAudioStream(_deviceId, stream);
		state = READY;
	};

	~AudioStream() {}

	void CheckPlayBack(SoundData* _data, std::atomic<bool>& _haltRequest) {
		while(state != STOPPED) {
			if((state != READY && SDL_GetAudioStreamQueued(stream) == 0) || _haltRequest) {
				StopStream();
			}

			if(state == READY) {
				Uint32 bytesQueded = SDL_GetAudioStreamQueued(stream);
				int bytesRemaining = static_cast<int>(_data->wavDataLength) - bytesQueded;

				std::vector<Uint8> wavDataRemainginVec = std::vector<Uint8>(bytesRemaining, '\0');
				Uint8* wavDataRemaining = &wavDataRemainginVec[0];

				SDL_memcpy(wavDataRemaining, (const Uint32*)(&_data->wavData[bytesQueded]), bytesRemaining);
				SDL_PutAudioStreamData(stream, wavDataRemaining, bytesRemaining);
				SDL_FlushAudioStream(stream);

				state = PLAYING;
			}
		}
	}

	void CheckPlayBackLooping(SoundData* _data, std::atomic<bool>& _haltRequest) {
		while(state != STOPPED) {
			if(_haltRequest) {
				StopStream();
			}

			if(state == READY) {
				Uint32 bytesQueded = SDL_GetAudioStreamQueued(stream);
				int bytesRemaining = static_cast<int>(_data->wavDataLength) - bytesQueded;

				std::vector<Uint8> wavDataRemainginVec = std::vector<Uint8>(bytesRemaining, '\0');
				Uint8* wavDataRemaining = &wavDataRemainginVec[0];

				SDL_memcpy(wavDataRemaining, (const Uint32*)&_data->wavData[bytesQueded], bytesRemaining);
				SDL_PutAudioStreamData(stream, wavDataRemaining, bytesRemaining);
				SDL_FlushAudioStream(stream);

				state = PLAYING;
			}

			if(state == PLAYING && SDL_GetAudioStreamQueued(stream) == 0) {
				SDL_ClearAudioStream(stream);
				state = READY;
			}
		}
	};
};