#include "SpriteBatch.h"
#include <algorithm>

namespace PandaEngine {

	SpriteBatch::SpriteBatch(): _vao(0),_vbo(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}
	void SpriteBatch::init()
	{
		createvertexArray();
	}
	void SpriteBatch::begin(GlyphSortType sortType)
	{
		_sortType = sortType;
		_renderbatchs.clear();
		_glyphs.clear();

	}
	void SpriteBatch::end()
	{
		_glyphPointer.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++)
		{
			_glyphPointer[i] = &_glyphs[i];
		}
		sortGlyphs();
		createRenderBatchs();
	}

	/* Draw Function it will create a new glyph and add it to the _glyphs vector*/
	void SpriteBatch::draw(const glm::vec4 & dectRect, const glm::vec4 & uvRect, GLuint textureId, float depth, const ColorRGBA8 & color)
	{
		_glyphs.emplace_back(dectRect,uvRect,textureId,depth,color);
	}

	void SpriteBatch::renderbatch()
	{
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderbatchs.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderbatchs[i].textureId);

			glDrawArrays(GL_TRIANGLES, _renderbatchs[i].offset, _renderbatchs[i].numVertices);
		}
	}
	void SpriteBatch::createRenderBatchs()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);
		if (_glyphs.empty())
		{
			return;
		}

		int offset = 0;
		int cv = 0; // current vertex

		_renderbatchs.emplace_back(offset, 6, _glyphPointer[0]->textureId);
		vertices[cv++] = _glyphPointer[0]->topLeft;
		vertices[cv++] = _glyphPointer[0]->bottomLeft;
		vertices[cv++] = _glyphPointer[0]->bottomRight;
		vertices[cv++] = _glyphPointer[0]->bottomRight;
		vertices[cv++] = _glyphPointer[0]->topRight;
		vertices[cv++] = _glyphPointer[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphPointer[cg]->textureId != _glyphPointer[cg - 1]->textureId)
			{
				_renderbatchs.emplace_back(offset, 6, _glyphPointer[cg]->textureId);
			}
			else
			{
				_renderbatchs.back().numVertices += 6;
			}
			
			vertices[cv++] = _glyphPointer[cg]->topLeft;
			vertices[cv++] = _glyphPointer[cg]->bottomLeft;
			vertices[cv++] = _glyphPointer[cg]->bottomRight;
			vertices[cv++] = _glyphPointer[cg]->bottomRight;
			vertices[cv++] = _glyphPointer[cg]->topRight;
			vertices[cv++] = _glyphPointer[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the Data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	void SpriteBatch::createvertexArray()
	{
		if(_vao == 0)
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		if (_vbo == 0)
		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER,_vbo);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs()
	{
		switch (_sortType)
		{
		case PandaEngine::GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(), compareFrontToBack);
			break;
		case PandaEngine::GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(),compareBackToFront);
			break;
		case PandaEngine::GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(),compareTexture);
			break;
		}
		
	}
	bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph * a, Glyph * b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph * a, Glyph * b)
	{
		return (a->textureId < b->textureId);
	}
}
