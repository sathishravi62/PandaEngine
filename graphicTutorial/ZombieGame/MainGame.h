#ifndef MAINGAME_H
#define MAINGAME_H

#include <PandaEngine/Window.h>
#include <PandaEngine/Shader.h>
#include <PandaEngine/InputManager.h>
#include <PandaEngine/Camera2D.h>

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

};

#endif // !MAINGAME_H



