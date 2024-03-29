#ifndef MAINGAME_H
#define MAINGAME_H

#include <PandaEngine/PandaEngine.h>
#include <PandaEngine/Window.h>
#include <PandaEngine/Shader.h>
#include <PandaEngine/InputManager.h>
#include <PandaEngine/Camera2D.h>
#include <PandaEngine/ResourceManager.h>
#include <PandaEngine/Timing.h>
#include <PandaEngine/SpriteBatch.h>
#include <PandaEngine/Error.h>
#include <SDL/SDL.h>

#include "Gun.h"
#include "Player.h"
#include "Level.h"
#include <vector>
#include "Bullet.h"

class Zombie;

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	// Run the game
	void run();

private:
	// Initializes the core system
	void initSystem();

	// Initializes the Shader
	void initShader();

	// Initializes the Level
	void initLevel();

	// Main game loop for the program 
	void gameLoop();

	// Update all the agents
	void updateAgents(float deltaTime); 

	// Update bullets
	void updateBullets(float deltaTime);

	void checkWinCondition(); // check the win condition

	// Handles input processing
	void processInput();

	// Renders the game
	void drawGame();

	// Member Variables
	PandaEngine::Window _windows; // The game window

	PandaEngine::Shader _textureProgram; // The Shader program

	PandaEngine::InputManager _inputManager; // Handles Input

	PandaEngine::Camera2D _camera; // Main Camera	

	PandaEngine::SpriteBatch _agentSpriteBatch; //  draw all agents

	std::vector<Level*> _levels; // vector of all levels

	Player* _player;

	std::vector<Human*> _humans; // vector of all human

	std::vector<Zombie*> _zombies; // vector of all zombies

	std::vector<Bullet> _bullets; // vector of all Bullets

	int _screenWidth, _screenHeight, _currentLevel;

	int _numHumanKilled;  // Human killed by player
	int _numZombieKilled; // Zombie killed by player
	 
	float _fps;	

	GameState _gameState;

};

#endif // !MAINGAME_H



