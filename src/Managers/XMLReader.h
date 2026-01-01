#pragma once
#include "FileManager.h"
#include "EnemyFactory.h"
class XMLReader :
    public FileManager
{
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
		for (pNode = pRoot->first_node("wave"); pNode; pNode = pNode->next_sibling()) {
			if (waveNum == 0) break;
			waveNum--;
		}

		Wave wave;
		int enemyId = std::stoi(pNode->first_node("spawned_enemy_id")->value());
		int enemyAmount = std::stoi(pNode->first_node("amount")->value());
		while (enemyAmount) {
			enemyAmount--;
			wave.AddSpawn(0.f, EnemyFactory::Instance().spawnFunctions[enemyId]);
		}

		return wave;
	}
};

