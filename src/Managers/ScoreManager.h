#pragma once
#include <utils/config.h>

struct HighScore {
	const char* name;
	int score;

	bool operator> (HighScore other) {
		return score > other.score || score == other.score && std::strcmp(name, other.name) > 0;
	}
};

class ScoreManager {
private:
	ScoreManager() = default;
	~ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	int score = 0;
	std::vector<HighScore> highScores;

public:
	static ScoreManager* GetInstance() {
		static ScoreManager instance;
		return &instance;
	}

	void Init() {
		highScores = Load();
	}

	void AddScore(int value) { score += value; }

	int GetScore() const { return score; }

	const std::vector<HighScore> GetScores() const { return highScores; }

	const std::string GetScoreAsText() const {
		int scoreDigits = (score > 0) ? std::floor(std::log10(score)) : 1;
		int zeroCount = SCORE_TEXT_DIGITS - scoreDigits;
		std::string result = "";
		for(int i = 0; i < zeroCount; ++i) result += "0";
		result += std::to_string(score);
		return result;
	}

	const std::string MakeScoreAsText(int score) {
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
		HighScore entry{ name.c_str(), score };

		highScores.push_back(entry);
		std::sort(
			highScores.begin(), highScores.end(),
			[](HighScore l, HighScore r) { return l > r; }
		);
		while(highScores.size() > MAX_STORED_SCORES) highScores.pop_back();

		FileManager::Instance().WriteBinary("ranking.bin", entry);
	}

	std::vector<HighScore> Load() {
		return FileManager::Instance().ReadBinary<HighScore>("ranking.bin");
	}
};
