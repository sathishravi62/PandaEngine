#ifndef MAINGAME_H
#define MAINGAME_H

#include <PandaEngine/PandaEngine.h>
#include <PandaEngine/Window.h>
#include <PandaEngine/Shader.h>
#include <PandaEngine/InputManager.h>
#include <PandaEngine/Camera2D.h>
#include <PandaEngine/ResourceManager.h>
#include <SDL/SDL.h>
#include <PandaEngine/Timing.h>

#include "Level.h"
#include <vector>

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

	// Main game loop for the program 
	void gameLoop();

	// Handles input processing
	void processInput();

	// Renders the game
	void drawGame();

	// Member Variables
	PandaEngine::Window _windows; // The game window

	PandaEngine::Shader _textureProgram; // The Shader program

	PandaEngine::InputManager _inputManager; // Handles Input

	PandaEngine::Camera2D _camera; // Main Camera

	std::vector<Level*> _levels; // vertor of all levels;

	int _screenWidth, _screenHeight,_fps;

	GameState _gameState;
};

#endif // !MAINGAME_H



