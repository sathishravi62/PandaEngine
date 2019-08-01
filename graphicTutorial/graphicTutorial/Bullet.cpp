#include "Bullet.h"

#include<PandaEngine/Texture.h>
#include<PandaEngine/ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime): _lifeTime(lifeTime),
_position(pos),
_direction(dir),
_speed(speed)
{
}


Bullet::~Bullet()
{
}



void Bullet::draw(PandaEngine::SpriteBatch & spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static PandaEngine::Texture texture = PandaEngine::ResourceManager::getTexture("texture/boy.png", GL_TRUE);

	PandaEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30.0f, 30.0f);

	spriteBatch.draw(posAndSize, uv, texture.ID, 0.0f, color);
}

bool Bullet::update()
{
	_position += _direction * _speed;
	_lifeTime--;

	if (_lifeTime == 0)
	{
		return true;
	}
	return false;
}
