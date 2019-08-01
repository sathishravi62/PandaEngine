#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <PandaEngine/PandaEngine.h>
#include <PandaEngine/Sprite.h>
#include <PandaEngine/Shader.h>
#include <PandaEngine/Texture.h>
#include <PandaEngine/Window.h>
#include <PandaEngine/Camera2D.h>
#include <PandaEngine/SpriteBatch.h>
#include <PandaEngine/ResourceManager.h>
#include <PandaEngine/Vertex.h>
#include <PandaEngine/InputManager.h>
#include <PandaEngine/Timing.h>

#include <vector>

enum  GameState 
{
	PLAY, EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystem();
	void initShader();
	void gameLoop();
	void processInput();
	void drawGame();

	PandaEngine::Window _window;
	int _screenWidth,_screenHeight;
	GameState _gameState;
	

	PandaEngine::Shader _colorShader;
	PandaEngine::Camera2D _camera;
	PandaEngine::SpriteBatch _spriteBatch;
	PandaEngine::InputManager _inputManager;
	PandaEngine::FpsLimiter _fpsLimiter;

	
	float _fps, _maxFps;
};

#endif // !MAINGAME_H


