#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <string>
#include "Texture.h"
#include "ResourceManager.h"
#include  "Vertex.h"

namespace PandaEngine {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath, bool alpha);
		void draw();

	private:
		float _x, _y, _width, _height;
		GLuint _vboID, _vaoID;
		Texture _texture;
	};
}
#endif // !SPRITE_H



