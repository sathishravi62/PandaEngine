#ifndef PLAYER_H
#define PLAYER_H

#include <PandaEngine/InputManager.h>
#include "Human.h"
#include <SDL/SDL.h>
class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed,glm::vec2 pos, PandaEngine::InputManager* inputManager);

	void update();

private:
	PandaEngine::InputManager* _inputManager;
};

#endif // !PLAYER_H



