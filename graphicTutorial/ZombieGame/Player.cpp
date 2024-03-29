#include "Player.h"



Player::Player() :_currentGunIndex(-1)
{

}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, PandaEngine::InputManager* inputManager,PandaEngine::Camera2D* camera, std::vector<Bullet>* bullets)
{

	_speed = speed;
	_position = pos;
	_inputManager = inputManager;
	_camera = camera;
	_bullets = bullets;

	_color.r = 0;
	_color.g = 0;
	_color.b = 128;
	_color.a = 255;

	_health = 150;
}

void Player::addGun(Gun * gun)
{
	// add the gun to the inventory 
	_guns.push_back(gun);

	// if no gun equipped, equip gun
	if (_currentGunIndex == -1)
	{
		_currentGunIndex = 0;
	}
}

void Player::update(const std::vector<std::string> & levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies, float deltaTime)
{
	if (_inputManager->isKeyDown(SDLK_a))
	{
		_position.x -= _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_d))
	{
		_position.x += _speed * deltaTime;
	}
	if (_inputManager->isKeyDown(SDLK_w))
	{
		_position.y += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_s))
	{
		_position.y -= _speed * deltaTime;
    }

	if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}
	else if(_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}
	else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2)
	{
		_currentGunIndex = 2;
	}

	if (_currentGunIndex != -1)
	{
		// getting the mouse position from the inputmanager
		glm::vec2 mouseCoords = _inputManager->getMouseCoord();

		//converting the mouse positon from screen space to world space 
		mouseCoords = _camera->convertScreenToWorld(mouseCoords);

		//calculating the centerposition of the player
		glm::vec2 centerPostion = _position + glm::vec2(AGENT_RADIUS);

		//calucting the direction where the bullet need to go
		glm::vec2  direction = glm::normalize(mouseCoords - centerPostion);


		_guns[_currentGunIndex]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
			centerPostion, direction, *_bullets,deltaTime);
	}

	collideWithLevel(levelData);
}
