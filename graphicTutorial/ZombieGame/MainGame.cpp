#include "MainGame.h"
#include <iostream>
#include "Zombie.h"
#include <random>
#include <ctime>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float PLAYER_SPEED = 5.0f;


MainGame::MainGame():
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_fps(0.0f),
	_player(nullptr),
	_numHumanKilled(0),
	_numZombieKilled(0)	
{
}


MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}

	for (int i = 0; i < _humans.size(); i++)
	{
		delete _humans[i];
	}

	for (int i = 0; i < _zombies.size(); i++)
	{
		delete _zombies[i];
	}
}

void MainGame::run() 
{
	initSystem();
	initLevel();
	gameLoop();
}

void MainGame::initSystem()
{
	PandaEngine::init();

	_windows.create("ZombieGame", _screenWidth, _screenHeight,0);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	initShader();

	_agentSpriteBatch.init();
	_camera.init(_screenWidth, _screenHeight);

	
}

// Initializes the Shader
void MainGame::initShader()
{
	_textureProgram.loadShaderFromFile("Shader/VertexShader.vert", "Shader/FragmentShader.frag");
}

void MainGame::initLevel()
{
	_levels.push_back(new Level("level/level.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager,&_camera,&_bullets);

	_humans.push_back(_player);

	// Creating the random the position for human with in the level size
	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_int_distribution<int>randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randY(2, _levels[_currentLevel]->getHeight() - 2);

	
	// Add all the random humans
	for (int i = 0; i < _levels[_currentLevel]->getNumberHuman(); i++)
	{
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	// Add the Zombies
	const std::vector<glm::vec2>& zombiePosition = _levels[_currentLevel]->getZombieStartPos();
	for (int i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePosition[i]);
	}

	// set up the player gun
	const float BULLET_SPEED = 20.0f;
	_player->addGun(new Gun("Magnum",  10, 1,  0.5f, BULLET_SPEED, 30.0f));
	_player->addGun(new Gun("Shotgun", 30, 12, 0.5f, BULLET_SPEED, 4.0f));
	_player->addGun(new Gun("MP5",     2,  1,  0.5f, BULLET_SPEED, 20.0f));
} 

// Main game loop for the program 
void MainGame::gameLoop()
{
	PandaEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(6000.0f);

	const float CAMERA_SCALE = 1.0f / 4.0f;
	_camera.setScale(CAMERA_SCALE);

	while (_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();
		
		checkWinCondition();

		_camera.setPosition(_player->getPosition());

		processInput();

		updateAgents();

		updateBullets();

		_camera.Update();	

		drawGame();

		_fps = fpsLimiter.end();

		std::cout << _fps << std::endl;
	}

	SDL_Quit();
}

void MainGame::updateAgents()
{
	// Update Player
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(),_humans,_zombies);
	}

	// Update the zombie

	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}

	// Update zombie Collision
	for (int i = 0; i < _zombies.size(); i++)
	{
		// collied with other zombie
		for (int j = i + 1; j < _zombies.size(); j++)
		{
			_humans[i]->collidewithAgent(_zombies[j]);
		}
		// collied with human
		for (int j = 1; j < _humans.size(); j++) //j = 0 repersent player
		{
			if (_zombies[i]->collidewithAgent(_humans[j]))
			{
				// Add new Zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());

				// Delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
		
		// collied with player
		/*if (_zombies[i]->collidewithAgent(_player))
		{
			PandaEngine::fatalError("You LOSE");
		}*/
	}



	// Update human Collision
	for (int i = 0; i < _humans.size(); i++)
	{
		// collied with other human
		for (int j = i + 1; j < _humans.size(); j++)
		{
			_humans[i]->collidewithAgent(_humans[j]);
		}
	}

	
}

void MainGame::updateBullets()
{
	// update and collied with bullet
	for (int i = 0; i < _bullets.size();)
	{
		//if update return true,the bullet collided with the wall
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData()))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			i++;
		}

	}

	bool wasBulletRemoved;

	// colliding with human and zombies
	for (int i = 0; i < _bullets.size(); i++)
	{
		wasBulletRemoved = false;
		// loop through zombies
		for (int j = 0; j < _zombies.size();)
		{
			// checking collision
			if (_bullets[i].colliedWithAgent(_zombies[j]))
			{   
				// Damage zombie, and kill it if its out of health
				if (_zombies[j]->applyDamage(_bullets[i].getDamage()))
				{
					// if zombie died, remove it
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
					_numZombieKilled++;
				}
				else
				{
					j++;
				}
				// Remove the bullet
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				i--; // make sure we don't skip a bullet
				// Since the bullets died, no need to loop throught any more zombies
				break;
			}
			else
			{
				j++;
			}
		}
		if (wasBulletRemoved == false)
		{
			// loop through humans
			for (int j = 1; j < _humans.size();)
			{
				// checking collision
				if (_bullets[i].colliedWithAgent(_humans[j]))
				{
					// Damage human, and kill it if its out of health
					if (_humans[j]->applyDamage(_bullets[i].getDamage()))
					{
						// if human died, remove it
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
						_numHumanKilled++;
					}
					else
					{
						j++;
					}
					// Remove the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					i--; // make sure we don't skip a bullet
					// Since the bullets died, no need to loop throught any more zombies
					break;
				}
				else
				{
					j++;
				}
			}
		}
	}
}

void MainGame::checkWinCondition()
{
	//TODO:: support for multiple level!
	// _currentLevel++; 

	// if all zombies are died 
	if (_zombies.empty())
	{
		std::printf("***** You win! ***** \n You killed %d humans and %d zombies. There are %d/%d civilians remaining",
			_numHumanKilled,_numZombieKilled,_humans.size() - 1,_levels[_currentLevel]->getNumberHuman());
		// we win
		PandaEngine::fatalError("");
		_gameState = GameState::EXIT;
	}
}

// Handles input processing
void MainGame::processInput()
{
	SDL_Event SdlEvent;

	while (SDL_PollEvent(&SdlEvent))
	{
		switch (SdlEvent.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoord(SdlEvent.motion.x, SdlEvent.motion.y);
			break;

		case SDL_KEYDOWN:
			_inputManager.pressKey(SdlEvent.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_inputManager.releaseKey(SdlEvent.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(SdlEvent.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(SdlEvent.button.button);
			break;
		}

	}


}

// Renders the game
void MainGame::drawGame()
{

	// set the depth to 1.0f;
	glClearDepth(1.0f);

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Code here

	_textureProgram.use();
	//Active the texture
	glActiveTexture(GL_TEXTURE0);
	_textureProgram.SetInteger("image", 0, GL_FALSE);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	_textureProgram.SetMatrix4("p", projectionMatrix, GL_FALSE);

	// Draw the level
	_levels[_currentLevel]->draw();

	//Begin sprite batch human
	_agentSpriteBatch.begin();

	// draw the humans and player
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}
	// draw the zombie
	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_agentSpriteBatch);
	}

	// draw the bullets
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();

	_agentSpriteBatch.renderbatch();

	// Swap the buffer and draw everything to the screen
	_windows.swapBuffer();

}
