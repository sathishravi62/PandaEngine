#include "Level.h"

#include <PandaEngine/Error.h>
#include <PandaEngine/ResourceManager.h>

#include <fstream>
#include <iostream>

Level::Level(const std::string& fileName)
{
	

	std::ifstream file;
	file.open(fileName);

	// error check
	if (file.fail()) 
	{
		PandaEngine::fatalError("failed to open " + fileName);
	}
	// throw away the first string in tmp
	std::string temp;

	file >> temp >> _numHumans;
	
	std::getline(file, temp); // Throw away the rest of the first line

	 // Read level data
	while (std::getline(file, temp))
	{
		_levelData.push_back(temp);
	}
	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	PandaEngine::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	// Render all the tile
	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			// grab the tile
			char tile = _levelData[y][x];
			// process the tile
			
			// get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y*TILE_WIDTH,  TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
			case 'B':
			case 'R':
				_spriteBatch.draw(destRect, uvRect, 
					PandaEngine::ResourceManager::getTexture("texture/redbrick.png", GL_TRUE).ID,0.0f,
					whiteColor);
				break;

			case 'G':
				_spriteBatch.draw(destRect, uvRect,
					PandaEngine::ResourceManager::getTexture("texture/Glass.png", GL_TRUE).ID, 0.0f,
					whiteColor);
				break;
			case 'L':
				_spriteBatch.draw(destRect, uvRect,
					PandaEngine::ResourceManager::getTexture("texture/lightbrick.png", GL_TRUE).ID, 0.0f,
					whiteColor);
				break;
			case '@':
				_levelData[y][x] = '.'; // So we dont collied with a @
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;
			case 'Z':
				_levelData[y][x] = '.'; // So we dont collied with a Z
				_zombiesStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;

			}
		}
	}
	_spriteBatch.end();
}


Level::~Level()
{
}

void Level::draw()
{
	_spriteBatch.renderbatch();
}
