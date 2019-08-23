#ifndef BULLET_H
#define BULLET_H

#include <GLM/glm.hpp>
#include <PandaEngine/SpriteBatch.h>
#include <vector>
#include <PandaEngine/ResourceManager.h>
#include "Agent.h"
#include "Human.h"
#include "Zombie.h"
#include "Level.h"

class Human;
class Zombie;

const int BULLET_RADIUS = 5;

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, float damage);
	~Bullet();

	//if update return true we are deleting the bullet
	bool update(const std::vector<std::string>& levelData,float deltaTime);

	void draw(PandaEngine::SpriteBatch& spriteBatch);

	bool colliedWithAgent(Agent* agent);

	// getter
	float getDamage() const { return _damage; }

private:

	bool colliedWithWorld(const std::vector<std::string>& levelData);

	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};


#endif // !BULLET_H


