#include "Bullet.h"
#include <GL/glew.h>


Bullet::Bullet( glm::vec2 position, glm::vec2 direction, float speed, float damage)
   :_position(position),
	_direction(direction),
	_speed(speed),
	_damage(damage)

{

}


Bullet::~Bullet()
{
}

bool Bullet::update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;
	return colliedWithWorld(levelData);
}
void Bullet::draw(PandaEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 desRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 UvRect(0.0f, 0.0f, 1.0f, 1.0f);
	PandaEngine::Color color;
	color.r = 75;
	color.g = 75;
	color.b = 75;
	color.a = 255;
	spriteBatch.draw(desRect, UvRect, PandaEngine::ResourceManager::getTexture("texture/circle.png", GL_TRUE).ID, 0.0f, color);
}

bool Bullet::colliedWithAgent(Agent * agent)
{
	// calculating the minmum distance 
	const float MIN_DISTANCE = AGENT_RADIUS +  BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0)
	{

		return true;
	}
	else
	{
		return false;
	}
}

bool Bullet::colliedWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	// if we are outside of the world, just return
	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
	{
		return true;
	}

	return(levelData[gridPosition.x][gridPosition.y] != '.');

}
