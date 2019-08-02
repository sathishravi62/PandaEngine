#ifndef AGENT_H
#define AGENT_H

#include <GLM/glm.hpp>
#include <PandaEngine/SpriteBatch.h>


const float AGENT_WIDTH = 60;
class Agent
{
public:

	Agent();
	
	virtual ~Agent();

	virtual void update() = 0;

	void draw(PandaEngine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return _position; }

protected:

	glm::vec2 _position;
	float _speed;
	PandaEngine::Color _color;
};

#endif // !AGENT_H




