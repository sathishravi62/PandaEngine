#ifndef PLAYER_H
#define PLAYER_H

#include <PandaEngine/InputManager.h>
#include <PandaEngine/Camera2D.h>

#include "Human.h"
#include <SDL/SDL.h>
#include <vector>
#include "Gun.h"

class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed,glm::vec2 pos, PandaEngine::InputManager* inputManager,PandaEngine::Camera2D* camera, std::vector<Bullet>* bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string> & levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies) ;

private:
	PandaEngine::InputManager* _inputManager;
	std::vector<Gun*> _guns;
	int _currentGunIndex;

	PandaEngine::Camera2D* _camera;
	std::vector<Bullet>* _bullets;
};

#endif // !PLAYER_H



