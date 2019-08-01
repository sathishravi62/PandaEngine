#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace PandaEngine {


	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph
	{
		GLuint textureId;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint TextureId) :offset(Offset), numVertices(NumVertices), textureId(TextureId)
		{

		}
		
		GLuint offset;
		GLuint numVertices;
		GLuint textureId;

	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		void end();

		void draw(const glm::vec4& dectRect, const glm::vec4& uvRect, GLuint textureId, float depth, const Color& color);

		void renderbatch();

	private:

		void createRenderBatchs();
		void createvertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;
		
		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;

		std::vector<RenderBatch> _renderbatchs;
	};
}
#endif // !SPRITEBATCH_H

