#include "Human.h"
#include <random>
#include <ctime>
#include <GLM/gtx/rotate_vector.hpp>

Human::Human():_frame(0)
{
}


Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_speed = speed;
	_position = pos;

	_color.r = 200;
	_color.g = 0;
	_color.b = 200;
	_color.a = 255;
	
	_health = 20;
	// Getting the Random direction
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));

	//Making sure Direction is not 0
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

	_direction = glm::normalize(_direction);
	
}

void Human::update(const std::vector<std::string> & levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies, float deltaTime)
{
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float>randRotate(-20.0f, 20.0f);

	_position += _direction * _speed * deltaTime;
	
	// Randomly change direction every 20sec
	if (_frame == 1000)
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frame = 0;
	}
	else
	{
		_frame++;
	}

	if (collideWithLevel(levelData))
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}
