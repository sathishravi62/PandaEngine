#include "InputManager.h"

namespace PandaEngine {

	InputManager::InputManager() : _mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		// loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
		for (auto& it : _keyMap)
		{
			_previousKeyMap[it.first] = it.second;
		}
	}
	void InputManager::pressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;
	}
	void InputManager::releaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}
	void InputManager::setMouseCoord(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y; 
	}
	bool InputManager::isKeyDown(unsigned int keyID)
	{
		// we dont want to use the associative array approach here
		// because we don't want to create a key if it does'nt exist
		// so we do it manually

		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
		{
			// Found the key
			return it->second;
		}
		else
		{
			//Didn't find the key
			return false;
		}
	}
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		// checking weather the KeyID is presed in previous frame
		if (isKeyDown(keyID) && !wasKeyPressed(keyID))
		{
			return true;
		}
		return false;
	}
	bool InputManager::wasKeyPressed(unsigned int keyID)
	{
		// we dont want to use the associative array approach here
		// because we don't want to create a key if it does'nt exist
		// so we do it manually

		auto it = _previousKeyMap.find(keyID);
		if (it != _previousKeyMap.end())
		{
			// Found the key
			return it->second;
		}
		else
		{
			//Didn't find the key
			return false;
		}
	}
}