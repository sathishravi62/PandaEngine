#include "TextureCache.h"
#include<iostream>

namespace PandaEngine {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::getTexture(std::string texturePath, GLboolean alpha)
	{
		//std::map<std::string,Texture>::iterator mit
		auto mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end())
		{
			const GLchar* Path = texturePath.c_str();
			Texture newTexture;
			newTexture.LoadTexture(Path, alpha);

			_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
		return mit->second;
	}
}