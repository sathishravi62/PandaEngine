#ifndef GUN_H
#define GUN_H

#include <string>
#include <GLM/glm.hpp>
#include <vector>

#include "Bullet.h"
class Gun
{
public:
	Gun(std::string name,int fireRate, int bulletPerShot,float spread,float bulletSpeed, float bulletDamage);
	~Gun();

	void update(bool isMouseDown,const glm::vec2& position, glm::vec2& direction, std::vector<Bullet>& bullets);

private:

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet> & bullets);

	std::string _name;

	int _fireRate; // Fire Rate in terms of frames

	int _bulletPerShot; // how many bullets are fired at at time

	float _spread; // Accuracy

	float _bulletSpeed; // bullet speed;

	float _bulletDamage; // bullet damage;

	int _frameCounter;
};


#endif // !GUN_H


