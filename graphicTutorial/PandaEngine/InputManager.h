// Input Manager Store a key Map that map SDL_Keys to booleans
// If the value in the key map is true, then the key is pressed
// otherwise, it is released

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <GLM/glm.hpp>

namespace PandaEngine {

	class InputManager
	{
	public:

		InputManager();
		~InputManager();
		 
		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int  keyID);
		void setMouseCoord(float x, float y);

		// Return true if the key is held down
		bool isKeyDown(unsigned int keyID);

		//retun true if the key was just pressed
		bool isKeyPressed(unsigned int keyID);
		
		// Getter function
		glm::vec2 getMouseCoord() const { return _mouseCoords; }
	private:

		//retun true if the key was just pressed
		bool wasKeyPressed(unsigned int keyID);

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoords;	
	};
}
#endif // !INPUTMANAGER_H



