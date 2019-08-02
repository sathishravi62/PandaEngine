#include "Agent.h"
#include <PandaEngine/ResourceManager.h>

Agent::Agent()
{
}


Agent::~Agent()
{
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
