#include "MainGame.h"
#include <iostream>
#include "Zombie.h"

MainGame::MainGame():
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_fps(0.0f),
	_player(nullptr)
{
}


MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
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
	_player->init(1.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);

	_humans.push_back(_player);
}

// Main game loop for the program 
void MainGame::gameLoop()
{
	PandaEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);
	while (_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		_camera.setPosition(_player->getPosition());

		processInput();

		updateAgents();

		_camera.Update();	

		drawGame();

		_fps = fpsLimiter.end();
	}
}

void MainGame::updateAgents()
{
	// Update Player
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(),_humans,_zombies);
	}

	// Update the zombie
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
			 // Exit the game here
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

	_agentSpriteBatch.end();

	_agentSpriteBatch.renderbatch();

	// Swap the buffer and draw everything to the screen
	_windows.swapBuffer();

}
