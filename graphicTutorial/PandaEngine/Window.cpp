#include "Window.h"
#include"Error.h"

namespace PandaEngine {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlag)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlag & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlag & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlag & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		// Open an SDL Window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		if (_sdlWindow == nullptr)
		{
			fatalError("SDL Window could not be created....");

		}
		// Set up our OpenGL context
		SDL_GLContext glContex = SDL_GL_CreateContext(_sdlWindow);
		if (glContex == nullptr)
		{
			fatalError("SDL_GL context could not be created");
		}

		//Set up Glew (Optional but Recommanded)

		glewExperimental = true;
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize glew!..");
		}

		// Check the OpenGL version
		std::printf("*** OpenGL Version:  %s  ***\n", glGetString(GL_VERSION));

		// Set the Background Color to Blue
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(1);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);

	}
}

