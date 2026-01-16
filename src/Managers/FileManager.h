#pragma once

class FileManager {
protected:
	FileManager() = default;
	~FileManager() = default;
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

public:
	static FileManager& Instance() {
		static FileManager instance;
		return instance;
	}

	template<typename T>
	bool WriteBinary(const char* path, const T& data, bool append = true) {
		SDL_IOStream* file = SDL_IOFromFile(path, append ? "ab" : "wb");
		if(!file) {
			SDL_Log("Writing failed: %s", SDL_GetError());
			return false;
		}

		int written = SDL_WriteIO(file, &data, sizeof(T));
		if(written != sizeof(T)) {
			SDL_Log("Failed to write full data: %d/%zu bytes", written, sizeof(T));
			SDL_CloseIO(file);
			return false;
		}

		SDL_CloseIO(file);
		return true;
	}

	template<typename T>
	std::vector<T> ReadBinary(const char* path) {
		std::vector<T> result = {};
		SDL_IOStream* file = SDL_IOFromFile(path, "rb");
		if(!file) {
			SDL_Log("Failed to open file: %s", SDL_GetError());
			return result;
		}

		T temp{};
		while(SDL_ReadIO(file, &temp, sizeof(T)) == sizeof(T)) {
			result.push_back(temp);
		}

		SDL_CloseIO(file);
		return result;
	}

	std::string ReadRawText(const char* path) {
		std::string result;
		char* Content{
			static_cast<char*>(
			SDL_LoadFile(path, nullptr)
		)};

		assert(Content);

		result = Content;

		SDL_free(Content);

		return result;
	}
};
