#ifndef BULLET_H
#define BULLET_H

#include <GLM/glm.hpp>
#include <PandaEngine/SpriteBatch.h>

class Bullet
{
public:

	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);

	~Bullet();

	void draw(PandaEngine::SpriteBatch& spriteBatch);

	bool update();

private:

	int _lifeTime;
	float _speed;
	glm::vec2 _direction,_position;
};

#endif // !BULLET_H



