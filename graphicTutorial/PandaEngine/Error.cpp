#include "Error.h"
#include<iostream>
#include<SDL/SDL.h>

namespace PandaEngine {
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit....." << std::endl;
		SDL_Quit();
	}
}