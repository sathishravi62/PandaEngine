#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <PandaEngine/SpriteBatch.h>
#include <GLM/glm.hpp>

const int TILE_WIDTH = 64;

class Level
{
public:
	// Load the level
	Level(const std::string& fileName);
	~Level();

	void draw();

	//Getter
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }

	int getNumberHuman() const { return _numHumans; }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPos() const { return _zombiesStartPos; }
	const std::vector<std::string>&  getLevelData() const { return _levelData; }

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	PandaEngine::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombiesStartPos;
	
};

#endif // !LEVEL_H



