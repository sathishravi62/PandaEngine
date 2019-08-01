#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include<map>
#include"Texture.h"
#include<GL/glew.h>
namespace PandaEngine {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		Texture getTexture(std::string texturePath, GLboolean alpha);

	private:
		std::map<std::string, Texture> _textureMap;

	};
}
#endif // !TEXTURECACHE_H

