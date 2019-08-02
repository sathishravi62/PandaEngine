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

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	PandaEngine::SpriteBatch _spriteBatch;

	glm::ivec2 _startPlayerPos;
	std::vector<glm::ivec2> _zombiesStartPos;
	
};

#endif // !LEVEL_H



