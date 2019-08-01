#include "MainGame.h"
#include <iostream>
#include <string>
#include <PandaEngine/Error.h>

MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY),
	_time(0),
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
}

void MainGame::initShader()
{
	_colorShader.loadShaderFromFile("VertexShader.vert", "FragmentShader.frag");
}

void MainGame::gameLoop()
{
	

	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();
		processInput();
		_time += 0.001f;

		_camera.Update();

		drawGame();
		fpsCalculate();

		// print only once every 10 frame
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		// Limit the FPS

		if (1000.0f / _maxFps > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFps - frameTicks);
		}
	}

	SDL_Quit();
}

void MainGame::processInput()
{

	const float CAMERA_SPEED = 20.0f;
	const float SCALE = 0.5f;

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

			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f,CAMERA_SPEED));
				break;

			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;

			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED,0.0f));
				break;

			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;

			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE);
				break;

			case SDLK_e:
				_camera.setScale(_camera.getScale() - SCALE);
				break;
			}
			break;
		}

		
	}
}

void MainGame::drawGame()
{
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorShader.use();
	_colorShader.SetFloat("time", _time, GL_FALSE);

	glActiveTexture(GL_TEXTURE0);
	_colorShader.SetInteger("image", 0, GL_TRUE);

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	_colorShader.SetMatrix4("p", cameraMatrix, GL_FALSE);

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static PandaEngine::Texture texture = PandaEngine::ResourceManager::getTexture("texture/Ball.png", GL_TRUE);
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

void MainGame::fpsCalculate()
{
	static const int NUM_SAMPLE = 10;
	static float frameTime[NUM_SAMPLE];
	static int currentFame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;

	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTime[currentFame % NUM_SAMPLE] = _frameTime;
	prevTicks = currentFame;

	int count;

	if (currentFame < NUM_SAMPLE)
	{
		count = currentFame;
	}
	else
	{
		count = NUM_SAMPLE;
	}

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTime[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;

	}
	else
	{
		_fps = 60.0f;
	}
	currentFame++;

}
