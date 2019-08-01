#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

namespace PandaEngine {

	class InputManager
	{
	public:

		InputManager();
		~InputManager();
		 
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int  keyID);

		bool isKeyPressed(unsigned int keyID);

	private:

		std::unordered_map<unsigned int, bool> _keyMap;
	};
}
#endif // !INPUTMANAGER_H



