#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::run() 
{

}

void MainGame::initSystem()
{

}

// Initializes the Shader
void MainGame::initShader()
{
	_textureProgram.compileShader("Shader/VertexShader.vert", "Shader/FragmentShader.frag");
}

// Main game loop for the program 
void MainGame::gameLoop()
{

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


	// Swap the buffer and draw everything to the screen
	_windows.swapBuffer();

}
