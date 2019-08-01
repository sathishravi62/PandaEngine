#include "Sprite.h"
#include <cstddef>

namespace PandaEngine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath, bool alpha)
	{

		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath, alpha);

		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}
		if (_vaoID == 0)
			glGenVertexArrays(1, &_vaoID);

		Vertex	verticesData[6];


		verticesData[0].setPosition(x + width, y + height);
		verticesData[0].setUV(1.0f, 1.0f);

		verticesData[1].setPosition(x , y + height);
		verticesData[1].setUV(0.0f, 1.0f);

		verticesData[2].setPosition(x, y);
		verticesData[2].setUV(0.0f, 0.0f);

		verticesData[3].setPosition(x, y);
		verticesData[3].setUV(0.0f, 0.0f);

		verticesData[4].setPosition(x + width, y);
		verticesData[4].setUV(1.0f, 0.0f);

		verticesData[5].setPosition(x + width, y + height);
		verticesData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			verticesData[i].setColor(0, 255, 0, 255);

		}

		glGenVertexArrays(1, &_vaoID);
		glGenBuffers(1, &_vboID);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*) offsetof(Vertex,position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


	}

	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, this->_texture.ID);

		glBindVertexArray(_vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}