#pragma once
#include <Utils/config.h>

struct HighScore {
	char name[16];
	int score;
};

class ScoreManager {
private:
	ScoreManager() = default;
	~ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	int score = 0;

public:
	static ScoreManager* GetInstance() {
		static ScoreManager instance;
		return &instance;
	}

	void AddScore(int value) {
		score += value;
	}

	int GetScore() const {
		return score;
	}

	const std::string GetScoreAsText() const {
		int scoreDigits = (score > 0) ? std::floor(std::log10(score)) : 1;
		int zeroCount = SCORE_TEXT_DIGITS - scoreDigits;
		std::string result = "";
		for(int i = 0; i < zeroCount; ++i) result += "0";
		result += std::to_string(score);
		return result;
	}

	bool IsHighScore() const {
		//TODO: Check High Score
		return true;
	}

	void Save(const std::string& name) {
		HighScore entry{};
		for(size_t i = 0; i < sizeof(entry.name) - 1 && i < name.size(); i++) {
			entry.name[i] = name[i];
		}
		entry.name[sizeof(entry.name) - 1] = '\0';
		entry.score = score;

		FileManager::Instance().WriteBinary("ranking.bin", entry);
	}

	std::vector<HighScore> Load() {
		return FileManager::Instance().ReadBinary<HighScore>("ranking.bin");
	}
};
