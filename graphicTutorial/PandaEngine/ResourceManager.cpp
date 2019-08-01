#include "ResourceManager.h"

namespace PandaEngine {

	TextureCache ResourceManager::_textureCache;

	Texture ResourceManager::getTexture(std::string texturePath, GLboolean alpha)
	{

		return _textureCache.getTexture(texturePath, alpha);
	}
}
