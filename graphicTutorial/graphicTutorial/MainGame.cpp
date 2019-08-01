#include "MainGame.h"
#include <iostream>
#include <string>
#include <PandaEngine/Error.h>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_maxFps(60.0f)
{
	_camera.init(_screenWidth,_screenHeight);
}


MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystem();

	//_sprites.push_back( new PandaEngine::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, _screenWidth/ 2, _screenWidth / 2, "texture/Ball.png", GL_TRUE);
	//
	//_sprites.push_back(new PandaEngine::Sprite());
	//_sprites.back()->init(_screenWidth / 2,0.0f, _screenWidth / 2, _screenWidth / 2, "texture/Ball.png", GL_TRUE);

	/*_sprites.push_back(new PandaEngine::Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "texture/Ball.png", GL_TRUE);*/

	gameLoop();
}

void MainGame::initSystem()
{
	PandaEngine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShader();

	_spriteBatch.init();
	_fpsLimiter.init(_maxFps);
}

void MainGame::initShader()
{
	_colorShader.loadShaderFromFile("VertexShader.vert", "FragmentShader.frag");
}

void MainGame::gameLoop()
{
	

	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();

		processInput();
		
		_camera.Update();

		drawGame();		

		_fps = _fpsLimiter.end();

		// print only once every 10 frames
		static int frameCounter = 0;

		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		
	}

	SDL_Quit();
}

void MainGame::processInput()
{

	const float CAMERA_SPEED = 2.0f;
	const float SCALE = 0.1f;

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;

		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}

	}

	
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
		
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + SCALE);
	}

	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - SCALE);
	}


}

void MainGame::drawGame()
{
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorShader.use();

	glActiveTexture(GL_TEXTURE0);
	_colorShader.SetInteger("image", 0, GL_TRUE);

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	_colorShader.SetMatrix4("p", cameraMatrix, GL_FALSE);

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static PandaEngine::Texture texture = PandaEngine::ResourceManager::getTexture("texture/block.png", GL_FALSE);
	PandaEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	
	_spriteBatch.draw(pos, uv, texture.ID, 0.0f, color);
	_spriteBatch.draw(pos + glm::vec4(50,0,0,0), uv, texture.ID, 0.0f, color);

	_spriteBatch.end();

	_spriteBatch.renderbatch();

	_window.swapBuffer();
}
