#pragma once
#include <Utils/enemyId.h>

class EnemyFactory;

class XMLReader : public FileManager {
private:
	XMLReader() : FileManager() {}
	~XMLReader() = default;
	XMLReader(const XMLReader&) = delete;
	XMLReader& operator=(const XMLReader&) = delete;

public:
	static XMLReader& Instance() {
		static XMLReader instance;
		return instance;
	}

	std::vector<Wave> FetchWavesFromFile(unsigned int level) {
		std::vector<Wave> waves;
		std::string rawText = ReadRawText(levelPaths[level]);

		rapidxml::xml_document<> doc;
		doc.parse<0>(&rawText[0]);

		auto* root = doc.first_node("level");
		if(!root) return waves;

		for(auto* waveNode = root->first_node("wave");
			waveNode;
			waveNode = waveNode->next_sibling("wave")) {
			float delay = std::stof(
				waveNode->first_node("delay_between_spawns")->value()
			);

			Wave wave;
			float currentTime = 0.0f;

			for(auto* enemyNode = waveNode->first_node("enemy");
				enemyNode;
				enemyNode = enemyNode->next_sibling("enemy")) {
				std::string typeStr = enemyNode->first_attribute("type")->value();
				int amount = std::stoi(enemyNode->first_attribute("amount")->value());

				EnemyId enemyId = EnemyIdFromString(typeStr);
				size_t index = static_cast<size_t>(enemyId);

				for(int i = 0; i < amount; ++i) {
					wave.AddSpawn(currentTime, EnemyFactory::Instance().GetSpawnFunctions()[static_cast<size_t>(enemyId)]);
					currentTime += delay;
				}
			}

			waves.push_back(std::move(wave));
		}

		return waves;
	}

private:
	void BuildWave(Wave& wave, EnemyId enemyId, int amount, float delay) {
		size_t index = static_cast<size_t>(enemyId);

		for(int i = 0; i < amount; ++i) {
			wave.AddSpawn(
				i * delay,
				EnemyFactory::Instance().GetSpawnFunctions()[index]
			);
		}
	}
};
