#pragma once
#include <cctype>
#include <utils/config.h>

struct HighScore {
	char name[MAX_USER_LENGTH];
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
		std::sort(
			highScores.begin(), highScores.end(),
			[](HighScore l, HighScore r) { return l > r; }
		);
		while(highScores.size() > MAX_STORED_SCORES) highScores.pop_back();
	}

	void AddScore(int value) { score += value; }

	int GetScore() const { return score; }

	const std::vector<HighScore> GetScores() const { return highScores; }

	const std::string GetScoreAsText() const {
		int scoreDigits = (score > 0) ? std::floor(std::log10(score)) + (score % 10 == 0) : 1;
		int zeroCount = SCORE_TEXT_DIGITS - scoreDigits;
		std::string result = "";
		for(int i = 0; i < zeroCount; ++i) result += "0";
		result += std::to_string(score);
		return result;
	}

	const std::string MakeScoreAsText(int score) const {
		int scoreDigits = (score > 0) ? std::floor(std::log10(score)) + (score % 10 == 0) : 1;
		int zeroCount = SCORE_TEXT_DIGITS - scoreDigits;
		std::string result = "";
		for(int i = 0; i < zeroCount; ++i) result += "0";
		result += std::to_string(score);
		return result;
	}

	bool IsHighScore() const {
		int bestScore = GetBestScore();
		return score > 0 && score > bestScore;
	}

	int GetBestScore() const {
		int bestScore = 0;
		for(const HighScore& entry : highScores) {
			bestScore = std::max(bestScore, entry.score);
		}
		return bestScore;
	}

	const std::string GetBestScoreAsText() const {
		return MakeScoreAsText(GetBestScore());
	}

	void Save(const std::string& name) {
		std::string sanitized = SanitizeName(name);
		HighScore entry{ {}, score };
		for(int i = 0; i < MAX_USER_LENGTH; ++i) {
			entry.name[i] = (i < sanitized.size()) ? sanitized[i] : '\0';
		}

		highScores.push_back(entry);
		std::sort(
			highScores.begin(), highScores.end(),
			[](HighScore l, HighScore r) { return l > r; }
		);
		while(highScores.size() > MAX_STORED_SCORES) highScores.pop_back();

		FileManager::Instance().WriteBinary("ranking.bin", highScores[0], false);
		for(int i = 1; i < highScores.size(); ++i) FileManager::Instance().WriteBinary("ranking.bin", highScores[i]);
	}

	std::vector<HighScore> Load() {
		return FileManager::Instance().ReadBinary<HighScore>("ranking.bin");
	}

private:
	std::string SanitizeName(const std::string& name) const {
		size_t start = 0;
		while(start < name.size() && std::isspace((unsigned char)name[start])) {
			++start;
		}
		size_t end = name.size();
		while(end > start && std::isspace((unsigned char)name[end - 1])) {
			--end;
		}
		std::string trimmed = name.substr(start, end - start);
		if(trimmed.empty()) {
			return "ANON";
		}
		if(trimmed.size() > MAX_USER_LENGTH) {
			return trimmed.substr(0, MAX_USER_LENGTH);
		}
		return trimmed;
	}
};
