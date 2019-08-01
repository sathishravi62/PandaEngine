#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"
#include <GL/glew.h>

namespace PandaEngine {

	class ResourceManager
	{
	public:
		static Texture getTexture(std::string texturePath, GLboolean alpha);
	private:
		static TextureCache _textureCache;
	};
}
#endif // !RESOURCEMANAGER_H



