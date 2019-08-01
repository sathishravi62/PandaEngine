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
		 
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int  keyID);
		void setMouseCoord(float x, float y);

		bool isKeyPressed(unsigned int keyID);
		
		// Getter function
		glm::vec2 getMouseCoord() const { return _mouseCoords; }
	private:

		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;	
	};
}
#endif // !INPUTMANAGER_H



