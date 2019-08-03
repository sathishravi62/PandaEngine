#include "Gun.h"
#include <random>
#include <ctime>
#include <GLM/gtx/rotate_vector.hpp>



Gun::Gun(std::string name, int fireRate, int bulletPerShot, float spread, float bulletSpeed, float bulletDamage)
	:_name(name),
	_fireRate(fireRate),
	_bulletPerShot(bulletPerShot),
	_spread(spread),
	_bulletSpeed(bulletSpeed),
	_bulletDamage(bulletDamage),
	_frameCounter(0)
{
	// Empty
}



Gun::~Gun()
{
}

void Gun::update(bool isMouseDown,const glm::vec2& position, glm::vec2& direction, std::vector<Bullet>& bullets)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction,position, bullets);
		_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine(time(nullptr));

	std::uniform_real_distribution<float>randRotate(-_spread, _spread);


	for (int i = 0; i < _bulletPerShot; i++)
	{
		bullets.emplace_back(position, glm::rotate(direction,randRotate(randomEngine)), 
			                 _bulletSpeed, _bulletDamage); 
	}
}
