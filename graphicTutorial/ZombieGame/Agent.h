#ifndef AGENT_H
#define AGENT_H

#include <GLM/glm.hpp>
#include <PandaEngine/SpriteBatch.h>


const float AGENT_WIDTH = 60;

class Zombie;
class Human;

class Agent
{
public:

	Agent();
	
	virtual ~Agent();

	virtual void update(const std::vector<std::string> & levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;

	bool collideWithLevel(const std::vector<std::string> & levelData);

	void draw(PandaEngine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return _position; }

protected:

	void checkTilePosition(std::vector<glm::vec2>& collideTilePos, float x, float y, const std::vector<std::string>& levelData);

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 _position;
	float _speed;
	PandaEngine::Color _color;
};

#endif // !AGENT_H




