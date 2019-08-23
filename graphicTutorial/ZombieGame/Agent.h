#ifndef AGENT_H
#define AGENT_H

#include <GLM/glm.hpp>
#include <PandaEngine/SpriteBatch.h>


const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = (float)AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
public:

	Agent();
	
	virtual ~Agent();

	virtual void update(const std::vector<std::string> & levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies, float deltaTime) = 0;

	bool collideWithLevel(const std::vector<std::string> & levelData);

	bool collidewithAgent(Agent* agent);

	// return true if we died
	bool applyDamage(float damage);

	void draw(PandaEngine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return _position; }

protected:

	void checkTilePosition(std::vector<glm::vec2>& collideTilePos, float x, float y, const std::vector<std::string>& levelData);

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 _position;
	float _speed;
	float _health;
	PandaEngine::ColorRGBA8 _color;
};

#endif // !AGENT_H




