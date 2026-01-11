#pragma once

class EnemyFactory;

class XMLReader :
	public FileManager {
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

	Wave FetchWave(int level, int waveNum) {
		std::string rawText = ReadRawText(levelPaths[level]);
		rapidxml::xml_document<> doc;
		doc.parse<0>(&rawText[0]);

		rapidxml::xml_node<>* pRoot = doc.first_node();
		rapidxml::xml_node<>* pNode;
		for(pNode = pRoot->first_node("wave"); pNode; pNode = pNode->next_sibling()) {
			if(waveNum == 0) break;
			waveNum--;
		}

		SpawnInstruction instr;
		instr.enemyId = std::stoi(pNode->first_node("spawned_enemy_id")->value());
		instr.amount = std::stoi(pNode->first_node("amount")->value());
		instr.delayBetweenSpawns = std::stof(pNode->first_node("delay_between_spawns")->value());

		Wave wave;
		BuildWaveFromInstruction(wave, instr);

		return wave;
	}

	void BuildWaveFromInstruction(Wave& wave, const SpawnInstruction& instr) {
		for(int i = 0; i < instr.amount; ++i) {
			wave.AddSpawn(
				i * instr.delayBetweenSpawns,
				EnemyFactory::Instance().spawnFunctions[instr.enemyId]
			);
		}
	}
};
