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
		for (int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i]; 
		}
		_glyphs.clear();

	}
	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatchs();
	}

	void SpriteBatch::draw(const glm::vec4 & dectRect, const glm::vec4 & uvRect, GLuint textureId, float depth, const ColorRGBA8 & color)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->textureId = textureId;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(dectRect.x,dectRect.y + dectRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(dectRect.x, dectRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(dectRect.x + dectRect.z, dectRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(dectRect.x + dectRect.z, dectRect.y + dectRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
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

		_renderbatchs.emplace_back(offset, 6, _glyphs[0]->textureId);
		vertices[cv++] = _glyphs[0]->topLeft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->textureId != _glyphs[cg - 1]->textureId)
			{
				_renderbatchs.emplace_back(offset, 6, _glyphs[cg]->textureId);
			}
			else
			{
				_renderbatchs.back().numVertices += 6;
			}
			
			vertices[cv++] = _glyphs[cg]->topLeft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
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
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case PandaEngine::GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(),compareBackToFront);
			break;
		case PandaEngine::GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(),compareTexture);
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
