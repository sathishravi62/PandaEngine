#ifndef  WINDOW_H
#define  WINDOW_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace PandaEngine {

	enum  WindowFlag
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:

		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlag);
		void swapBuffer();

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }


	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};
}
#endif // ! WINDOW_H


