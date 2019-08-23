#include "Agent.h"
#include <PandaEngine/ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	// check the four corner
	// First corner
	checkTilePosition(collideTilePos, _position.x, _position.y, levelData);

	//second corner
	checkTilePosition(collideTilePos, _position.x + AGENT_WIDTH, _position.y, levelData);

	//third corner
	checkTilePosition(collideTilePos, _position.x, _position.y + AGENT_WIDTH, levelData);

	//four corner
	checkTilePosition(collideTilePos, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH, levelData);

	if (collideTilePos.size() == 0)
	{
		return false;
	}
	// Do the Collision
	for (int i = 0; i < collideTilePos.size(); i++)
	{
		collideWithTile(collideTilePos[i]);
	}

	return true;
}

bool Agent::collidewithAgent(Agent * agent)
{
	// calculating the minmum distance 
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);  
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		
		agent->_position -= collisionDepthVec / 2.0f;
		
		return true;
	}
	else
	{
		return false;
	}
}

bool Agent::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}
	return false;
}

void Agent::draw(PandaEngine::SpriteBatch & _spriteBatch)
{
	static int textureID = PandaEngine::ResourceManager::getTexture("texture/circle.png", GL_TRUE).ID;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;  
	
	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f,_color);
}

void Agent::checkTilePosition(std::vector<glm::vec2>& collideTilePos, float x, float y, const std::vector<std::string>& levelData)
{
	// check the four corner
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH));

	// if we are outside of the world, just return
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return; 
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePos.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH/2.0f));
	}
}

// AABB collison
void Agent::collideWithTile(glm::vec2 tilePos)
{
	
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS); 

	glm::vec2 distVec = centerPlayerPos - tilePos;
	
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	// if this is true, we are colliding
	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth,0.0f) < std::max(yDepth,0.0f))
		{
			if (distVec.x < 0)
			{
				_position.x -= xDepth;
			}
			else
			{
				_position.x += xDepth;
			}
		}
		else
		{
			if (distVec.y < 0)
			{
				_position.y -= yDepth;
			} 
			else
			{
				_position.y += yDepth;
			}
		}
	}
}
